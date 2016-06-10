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

using namespace warp;

SceneRenderer::SceneRenderer() : activeGameObjectID(0), activeCameraID(0), t_total(0.0), paused(false)
{
    
}

void SceneRenderer::pause()
{
    paused = !paused;
}

bool SceneRenderer::isPaused() const
{
    return paused;
}

// requires shaders ready
void SceneRenderer::init()
{
    std::shared_ptr<Scene> scene = std::static_pointer_cast<Scene>(gameObject.lock());
    
    // Set the background color
    glClearColor (0.1f, 0.06f, 0.15f, 1.0f);
    
    // Start counting time
    t_last = std::chrono::high_resolution_clock::now();
    
    // Set geometry shader settings
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    
//    GLuint uboTestBlock;
//    glGenBuffers(1, &uboTestBlock);
//    glBindBuffer(GL_UNIFORM_BUFFER, uboTestBlock);
//    glBufferData(GL_UNIFORM_BUFFER, 4*sizeof(GLfloat), NULL, GL_STATIC_DRAW);
//    glBindBuffer(GL_UNIFORM_BUFFER, 0);
//    
//    auto shader = ShaderManager::getInstance()->get(Shader::ID(0));
//    GLint shader_program = shader->getNativeHandle();
//    
//    GLuint test_index = glGetUniformBlockIndex(shader_program, "test");
//    glUniformBlockBinding(shader_program, test_index, 0);
//    glBindBufferBase(GL_UNIFORM_BUFFER, 0, uboTestBlock);
//    
//    GLfloat color[] = { 1.0, 0.0, 1.0, 1.0 };
//    glBindBuffer(GL_UNIFORM_BUFFER, uboTestBlock);
//    glBufferSubData(GL_UNIFORM_BUFFER, 0, 4*sizeof(GLfloat), color);
    
    // Create Light Uniform Buffer (LUB)
    glGenBuffers(1, &uboLights);
    glBindBuffer(GL_UNIFORM_BUFFER, uboLights);
    glBufferData(GL_UNIFORM_BUFFER, Light::MAX_LIGHTS * 3 * sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
    
    // Get all light sources
    std::vector<std::shared_ptr<Light>> lights = scene->getComponents<Light>();
    
    // Upload light data to LUB
    for (GLint i = 0; i < Light::MAX_LIGHTS && i < lights.size(); ++i)
    {
        glBufferSubData(GL_UNIFORM_BUFFER,
                        i*3*sizeof(glm::vec4),
                        3*sizeof(glm::vec4),
                        lights[i]->getData());
    }
    
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
    auto shader = ShaderManager::getInstance()->get(Shader::ID(0));
    GLint shader_program = shader->getNativeHandle();
    
    // Two-way bind the LUB to shader binding point
    // ShaderManager::getInstance()->setUniformBlockBinding("lightsBlock", 0); // !! DOES NOT WORK
    
    // WORKAROUND
    GLuint index = glGetUniformBlockIndex(shader_program, "lightsBlock");
    glUniformBlockBinding(shader_program, index, 10);
    // WORKAROUND
    
    glBindBufferBase(GL_UNIFORM_BUFFER, 10, uboLights);
    
    // Create Matrix Uniform Buffer (MUB)
    glGenBuffers(1, &uboCamera);
    glBindBuffer(GL_UNIFORM_BUFFER, uboCamera);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4)+sizeof(glm::vec3), NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
    // Two-way bind the MUB to shader binding point
    // ShaderManager::getInstance()->setUniformBlockBinding("uboCamera", 1); // !! DOES NOT WORK
    
    // WORKAROUND
    index = glGetUniformBlockIndex(shader_program, "cameraBlock");
    glUniformBlockBinding(shader_program, index, 11);
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
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    
    auto t_now = std::chrono::high_resolution_clock::now();
    
    // Update total elapsed time (if not paused)
    if (!paused) {
        t_total += std::chrono::duration_cast<std::chrono::duration<double>>(t_now - t_last).count();
    }
    t_last = t_now; // Update last tick
    
    // For each camera in the scene
//	std::cout << "Number of Cameras: " << scene->getComponentsInChildren<Camera>().size() <<"\n";
    for (const std::shared_ptr<Camera>& camera : scene->getComponentsInChildren<Camera>())
    {
        updateCamera(camera);
        
        // Render visible objects
//		std::cout << "Number of Renderers: " << scene->getComponentsInChildren<MeshRenderer>().size() << " Camera obj: " << "\n";
        for (std::shared_ptr<MeshRenderer>& renderer : scene->getComponentsInChildren<MeshRenderer>()) // TODO [Should be mesh renderer... but get components does not work with inherited components]
        {
			renderer->activate();
            renderer->render();
        }
    }
}

void SceneRenderer::onKeyDown(Input::Key type)
{
    switch (type) {
        case Input::Key::LBracket:
            getActiveGameObject()->getTransform()->scale(1.25f, 1.25f, 1.25f);
            break;
        case Input::Key::RBracket:
            getActiveGameObject()->getTransform()->scale(0.8f, 0.8f, 0.8f);
            break;
        case Input::Key::Space:
            pause();
            break;
        case Input::Key::Num0:
            activeGameObjectID = GameObject::ID(0);
            break;
        case Input::Key::Num1:
            activeGameObjectID = GameObject::ID(1);
            break;
        case Input::Key::Num2:
            activeGameObjectID = GameObject::ID(2);
            break;
        case Input::Key::Num3:
            activeGameObjectID = GameObject::ID(3);
            break;
        case Input::Key::Num4:
            activeGameObjectID = GameObject::ID(4);
            break;
        case Input::Key::Num5:
            activeGameObjectID = GameObject::ID(5);
            break;
        case Input::Key::Num6:
            activeGameObjectID = GameObject::ID(6);
            break;
        case Input::Key::Num7:
            activeGameObjectID = GameObject::ID(7);
            break;
        case Input::Key::Num8:
            activeGameObjectID = GameObject::ID(8);
            break;
        case Input::Key::Num9:
            activeGameObjectID = GameObject::ID(9);
            break;
        default:
            break;
    }
}

void SceneRenderer::onMouseScrolled(float delta)
{
    float scaleFactor;
    if (delta >= 0.0f) {
        scaleFactor = 1.0f + delta/10.0f;
    } else {
        scaleFactor = 1.0f / (1.0f + -delta/10.0f);
    }
    getActiveGameObject()->getTransform()->scale(scaleFactor);
}

void SceneRenderer::onResized(int width, int height)
{
    std::shared_ptr<Scene> scene = std::static_pointer_cast<Scene>(gameObject.lock());
    scene->getComponent<Camera>()->reshape(width, height);
}

std::shared_ptr<GameObject> SceneRenderer::getActiveGameObject()
{
    std::shared_ptr<Scene> scene = std::static_pointer_cast<Scene>(gameObject.lock());
    return scene;
}

void SceneRenderer::processInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        getActiveGameObject()->getTransform()->rotateZ(0.025f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
        getActiveGameObject()->getTransform()->rotateZ(-0.025f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        getActiveGameObject()->getTransform()->translate(-.025f, .0f, .0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        getActiveGameObject()->getTransform()->translate(.0f, -.025f, .0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        getActiveGameObject()->getTransform()->translate(.025f, .0f, .0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        getActiveGameObject()->getTransform()->translate(.0f, .025f, .0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        getActiveGameObject()->getTransform()->rotateX(0.025f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        getActiveGameObject()->getTransform()->rotateX(-0.025f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        getActiveGameObject()->getTransform()->rotateY(-0.025f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        getActiveGameObject()->getTransform()->rotateY(0.025f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        getActiveGameObject()->getTransform()->translate(.0f, .0f, -.01f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
    {
        getActiveGameObject()->getTransform()->translate(.0f, .0f, .01f);
    }
}

