#include "SceneRenderer.hpp"

#include "Scene.hpp"
#include "SceneManager.hpp"

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

#include <typeinfo>

using namespace warp;

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
    
    auto shader = ShaderManager::getInstance()->get(Shader::ID(0));
    GLint shader_program = shader->getNativeHandle();
    
    // Two-way bind the LUB to shader binding point
    ShaderManager::getInstance()->setUniformBlockBinding("lightsBlock", 10); // !! DOES NOT WORK
    
    // WORKAROUND
    //GLuint index = glGetUniformBlockIndex(shader_program, "lightsBlock");
    //glUniformBlockBinding(shader_program, index, 10);
    // WORKAROUND
    
    glBindBufferBase(GL_UNIFORM_BUFFER, 10, uboLights);
    
    // Create Matrix Uniform Buffer (MUB)
    glGenBuffers(1, &uboCamera);
    glBindBuffer(GL_UNIFORM_BUFFER, uboCamera);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4)+sizeof(glm::vec3), NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
    // Two-way bind the MUB to shader binding point
    ShaderManager::getInstance()->setUniformBlockBinding("cameraBlock", 11); // !! DOES NOT WORK
    
    // WORKAROUND
    //index = glGetUniformBlockIndex(shader_program, "cameraBlock");
    //glUniformBlockBinding(shader_program, index, 11);
    // WORKAROUND
    
    glBindBufferBase(GL_UNIFORM_BUFFER, 11, uboCamera);
}

void SceneRenderer::updateCamera(const std::shared_ptr<Camera> camera)
{
    if (camera->update())
    {
        glBindBuffer(GL_UNIFORM_BUFFER, uboCamera);
        glBufferSubData(GL_UNIFORM_BUFFER,
                        0, sizeof(glm::mat4),
                        glm::value_ptr(camera->getViewProjection()));
        glBufferSubData(GL_UNIFORM_BUFFER,
                        sizeof(glm::mat4), sizeof(glm::vec3),
                        glm::value_ptr(camera->getGameObject()->getTransform()->getGlobalPosition()));
        glBindBuffer(GL_UNIFORM_BUFFER, 0);  
    }
}

void SceneRenderer::render()
{
    std::shared_ptr<Scene> scene = std::static_pointer_cast<Scene>(gameObject.lock());
    
    // Clear the screen to black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    std::vector<std::shared_ptr<Renderer>> renderers = scene->getComponents<Renderer>();
    
    // For each camera in the scene
    for (const std::shared_ptr<Camera>& camera : scene->getComponents<Camera>())
    {
        updateCamera(camera);
        
        // Render visible objects
        for (const std::shared_ptr<Renderer>& renderer : renderers)
        {
			renderer->activate(); //TODO: render only active renderers (instead of activating all of them)
            renderer->render();
        }
    }
}
