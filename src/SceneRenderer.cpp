#include "SceneRenderer.hpp"

#include "Scene.hpp"
#include "SceneManager.hpp"

#include "WindowManager.hpp"
#include "Shader.hpp"
#include "ShaderManager.hpp"
#include "Transform.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Mesh.hpp"
#include "util.hpp"

#include "MeshRenderer.hpp"

#include <SFML/Window.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <algorithm>
#include <typeinfo>
#include <stdexcept>

using namespace warp;

SceneRenderer::~SceneRenderer()
{
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &uboLights);
    glDeleteBuffers(1, &uboCamera);
    glDeleteTextures(1, &ftxo);
    glDeleteRenderbuffers(1, &frbo);
    glDeleteFramebuffers(1, &fbo);
    glDeleteVertexArrays(1, &vao);
}

// requires shaders ready
void SceneRenderer::init()
{
    std::shared_ptr<Scene> scene = std::static_pointer_cast<Scene>(gameObject.lock());
    
    // Set the background color
    glClearColor (0.1f, 0.06f, 0.15f, 1.0f);
    
    // Set geometry shader settings
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    
    // Create Light Uniform Buffer (LUB)
    glGenBuffers(1, &uboLights);
    glBindBuffer(GL_UNIFORM_BUFFER, uboLights);
    glBufferData(GL_UNIFORM_BUFFER, Light::MAX_LIGHTS * 3 * sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
    
    // Get all light sources
    std::vector<std::shared_ptr<Light>> lights = scene->getComponents<Light>();
    
    // Upload light data to LUB
    for (GLint i = 0; i < Light::MAX_LIGHTS && i < lights.size(); ++i)
    {
        glBufferSubData(GL_UNIFORM_BUFFER, i*3*sizeof(glm::vec4), 3*sizeof(glm::vec4), lights[i]->getData());
    }
    
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
    // Two-way bind the LUB to shader binding point
    ShaderManager::getInstance()->setUniformBlockBinding("lightsBlock", 10);
    
    glBindBufferBase(GL_UNIFORM_BUFFER, 10, uboLights);
    
    // Create Matrix Uniform Buffer (MUB)
    glGenBuffers(1, &uboCamera);
    glBindBuffer(GL_UNIFORM_BUFFER, uboCamera);
    glBufferData(GL_UNIFORM_BUFFER, 2*sizeof(glm::mat4)+sizeof(glm::vec3), NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
    // Two-way bind the MUB to shader binding point
    ShaderManager::getInstance()->setUniformBlockBinding("cameraBlock", 11);
    
    glBindBufferBase(GL_UNIFORM_BUFFER, 11, uboCamera);
    
    // Create HDR framebuffer
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    
    // Get screen size
    glm::vec2 size(800, 600);
    if (auto window = WindowManager::getInstance()->getActive())
    {
        size = window->getSize();
    }
    else
    {
        fprintf(stderr, "WARN: using default framebuffer resolution");
    }
    
    // Create a texture of the same size as the screen
    glGenTextures(1, &ftxo);
    glBindTexture(GL_TEXTURE_2D, ftxo);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, size.x, size.y, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // Bind this texture to the framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ftxo, 0);
    
    // Create a renderbuffer to store depth (and stencil)
    glGenRenderbuffers(1, &frbo);
    glBindRenderbuffer(GL_RENDERBUFFER, frbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    
    // Bind this renderbuffer to the framebuffer
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, frbo);
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        throw new std::runtime_error("ERROR: Framebuffer is not complete");
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // All set for offscreen rendering
    
    // Create the screen tonemapping shader
    screenShaderID = ShaderManager::getInstance()->createFromFile(util::resourcePath() + "screen_v.glsl", util::resourcePath() + "screen_f.glsl");
    
    // Create a simple quad
    GLfloat vertices[] = {
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
        1.0f, -1.0f,  1.0f, 0.0f,
        
        -1.0f,  1.0f,  0.0f, 1.0f,
        1.0f, -1.0f,  1.0f, 0.0f,
        1.0f,  1.0f,  1.0f, 1.0f
    };
    
    // Create Vertex Array Object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    // Create a Vertex Buffer Object and copy the vertex data to it
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // Set up shader inputs
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(2 * sizeof(GLfloat)));
    
    glBindVertexArray(0);
}

void SceneRenderer::updateCamera(const std::shared_ptr<Camera> camera)
{
    if (camera->update())
    {
        glBindBuffer(GL_UNIFORM_BUFFER, uboCamera);
        glBufferSubData(GL_UNIFORM_BUFFER,
                        0, sizeof(glm::mat4),
                        glm::value_ptr(camera->getView()));
        glBufferSubData(GL_UNIFORM_BUFFER,
                        sizeof(glm::mat4), sizeof(glm::mat4),
                        glm::value_ptr(camera->getProjection()));
        glBufferSubData(GL_UNIFORM_BUFFER,
                        2*sizeof(glm::mat4), sizeof(glm::vec3),
                        glm::value_ptr(camera->getGameObject()->getTransform()->getGlobalPosition()));
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }
}

void SceneRenderer::render()
{
    std::shared_ptr<Scene> scene = std::static_pointer_cast<Scene>(gameObject.lock());
    
    // Use the offscreen render target
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    
    // Clear the screen to black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // (Re)enable depth test
    glEnable(GL_DEPTH_TEST);
    
    std::vector<std::shared_ptr<Renderer>> renderers = scene->getComponents<Renderer>();
    
    // Sort renderers
    Renderer::sort(renderers);
    
    // For each camera in the scene
    for (const std::shared_ptr<Camera>& camera : scene->getComponents<Camera>())
    {
        updateCamera(camera);
        
        // Render visible objects
        for (const std::shared_ptr<Renderer>& renderer : renderers)
        {
            if (renderer->isActive()) renderer->render();
        }
    }
    
    // Use the screen render target
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    // Clear the screen to black
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Temporarily disable depth test
    glDisable(GL_DEPTH_TEST);
    
    // Use the tonemapping shader
    ShaderManager::getInstance()->setActive(screenShaderID);
    
    // Setup the screen texture to render
    if (std::shared_ptr<Shader> activeShader = ShaderManager::getInstance()->getActive()) {
        glUniform1i(activeShader->getUniformLocation("u_sampler0"), 0);
        glUniform1f(activeShader->getUniformLocation("exposure"), 1.0f);
    }
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ftxo);
    
    // Draw a quad to screen
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
