#include <GL/glew.h>

#include <SFML/Window.hpp>

#include <memory>

#include "MaterialManager.hpp"
#include "TextureManager.hpp"
#include "ShaderManager.hpp"
#include "SceneRenderer.hpp"
#include "MeshRenderer.hpp"
#include "MeshManager.hpp"
#include "Transform.hpp"
#include "GameLoop.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "Input.hpp"
#include "Scene.hpp"
#include "Light.hpp"
#include "Mesh.hpp"
#include "util.hpp"

int main(int, char const**)
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.majorVersion = 4;
    settings.minorVersion = 1;
    settings.antialiasingLevel = 4;
    settings.attributeFlags = sf::ContextSettings::Core;
    
    auto window = std::make_shared<sf::Window>(sf::VideoMode(800, 800, 32), "Warp",
                                               sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize,
                                               settings);
    window->setVerticalSyncEnabled(true);
    
    warp::Input windowInput(window);
    
    glewExperimental = GL_TRUE;
    glewInit();
    glGetError(); // Discard error 500
    
    // These are resource managers
    auto shaderManager = warp::ShaderManager::getInstance();
    auto textureManager = warp::TextureManager::getInstance();
    auto materialManager = warp::MaterialManager::getInstance();
    auto meshManager = warp::MeshManager::getInstance();
    
    // Load a shader from file
    auto shaderID = shaderManager->createFromFile(util::resourcePath() + "vertex.glsl",
                                                  util::resourcePath() + "frag.glsl");
    // Load a texture from file
    auto textureID = textureManager->createFromFile(util::resourcePath() + "test.png");
    
    // Create a material from shader and texture
    auto materialID = materialManager->create(textureID, shaderID);
    
    // Create a mesh representation
    auto squareID = meshManager->create();
    if (std::shared_ptr<warp::Mesh> squareMesh = meshManager->get(squareID))
    {
        squareMesh->setVertices({
            -0.8f, 0.8f, 0.0f,   0.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
            -0.4f, 0.8f, 0.0f,   0.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
            -0.8f, 0.4f, 0.0f,   0.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
            -0.4f, 0.4f, 0.0f,   0.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f
        });
        squareMesh->setElements({
            0, 2, 1,
            2, 3, 1
        });
        squareMesh->load();
    }
    
    // Create the scene object
    std::shared_ptr<warp::Scene> scene = warp::Scene::newScene();
    std::shared_ptr<warp::SceneRenderer> sRenderer = scene->newComponent<warp::SceneRenderer>();
    
    // Create a camera object
    std::shared_ptr<warp::GameObject> go1 = scene->newGameObject();
    std::shared_ptr<warp::Camera> camera = go1->newComponent<warp::Camera>();
    camera->setPosition(glm::vec3(0, 0, 5));
    camera->lookAt(glm::vec3(0,0,0), glm::vec3(0,1,0));
    camera.reset();
    
    // Create a directional light object
    auto go2 = scene->newGameObject();
    std::shared_ptr<warp::Light> light = go2->newComponent<warp::Light>(warp::Light::Type::Directional);
    light->setVector(glm::vec3(-0.15f, -0.1f, -0.9f));
    light->setColor(glm::vec3(1.0f, 1.0f, 0.93f));
    light.reset();
    
    // Create a mesh object
    auto go3 = scene->newGameObject();
    go3->newComponent<warp::MeshRenderer>(materialID, squareID);
    
    // Initialize rendering context
    sRenderer->init();
    
    // The scene renderer will listen to window events
    windowInput.addListener(sRenderer);
    
    // This is the main loop
    auto loop = std::make_shared<warp::GameLoop>(
    [&windowInput, sRenderer, window]()
    {
        // Process window events
        windowInput.flush();
        
        // Handle continuous input
        sRenderer->processInput();
        
        // Draw the scene
        sRenderer->render();
        
        // Swap buffers
        window->display();
    });
    windowInput.addListener(loop);
    
    loop->run();
    
    window->close();

    return EXIT_SUCCESS;
}

