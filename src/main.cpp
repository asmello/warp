#include <GL/glew.h>

#include <SFML/Window.hpp>

#include <memory>

#include "GameObjectManager.hpp"
#include "MaterialManager.hpp"
#include "TextureManager.hpp"
#include "ShaderManager.hpp"
#include "SceneRenderer.hpp"
#include "MeshRenderer.hpp"
#include "MeshManager.hpp"
#include "GameObject.hpp"
#include "GameLoop.hpp"
#include "Input.hpp"
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
    
    auto shaderManager = warp::ShaderManager::getInstance();
    auto textureManager = warp::TextureManager::getInstance();
    auto materialManager = warp::MaterialManager::getInstance();
    auto meshManager = warp::MeshManager::getInstance();
    auto cameraManager = warp::CameraManager::getInstance();
    
    // Create the assets
    auto shaderID = shaderManager->createFromFile(util::resourcePath() + "vertex.glsl", util::resourcePath() + "frag.glsl");
    auto textureID = textureManager->createFromFile(util::resourcePath() + "test.png");
    auto materialID = materialManager->create(textureID, shaderID);
    auto pyramidID = meshManager->create();
    if (std::shared_ptr<warp::Mesh> pyramidMesh = meshManager->get(pyramidID))
    {
        pyramidMesh->setVertices({
            -1.0f, -1.0f,  0.57730f,  0.0f, 0.0f,
            0.0f, -1.0f, -1.15475f,  0.5f, 0.0f,
            1.0f, -1.0f,  0.57730f,  1.0f, 0.0f,
            0.0f,  1.0f,  0.00000f,  0.5f, 1.0f
        });
        pyramidMesh->setElementBuffer({
            0, 3, 1,
            1, 3, 2,
            2, 3, 0,
            1, 2, 0
        });
        pyramidMesh->init();
    }
    auto squareID = meshManager->create();
    if (std::shared_ptr<warp::Mesh> squareMesh = meshManager->get(squareID))
    {
        squareMesh->setVertices({
            -0.8f, 0.8f, 0.0f,  0.0f, 0.0f,
            -0.4f, 0.8f, 0.0f,  1.0f, 0.0f,
            -0.8f, 0.4f, 0.0f,  0.0f, 1.0f,
            -0.4f, 0.4f, 0.0f,  1.0f, 1.0f
        });
        squareMesh->setElementBuffer({
            0, 2, 1,
            2, 3, 1
        });
        squareMesh->init();
    }
    
    // Create the scene object
    auto scene = std::make_shared<warp::Scene>();

    auto cameraID = cameraManager->create();
    if (std::shared_ptr<warp::Camera> camera = cameraManager->get(cameraID))
    {
        camera->setPosition(glm::vec3(0, 0, 5));
        camera->lookAt(glm::vec3(0,0,0), glm::vec3(0,1,0));
    }
    scene->addCamera(cameraID);
    
    auto pyramidRenderer = std::make_shared<warp::MeshRenderer>(materialID, pyramidID);
    scene->addRenderer(pyramidRenderer);
    auto squareRenderer = std::make_shared<warp::MeshRenderer>(materialID, squareID);
    scene->addRenderer(squareRenderer);
    
//    scene->createRenderer<warp::MeshRenderer>(materialID, pyramidID); // Default pose
//    scene->createRenderer<warp::MeshRenderer>(materialID, squareID); // Default pose
    
    // Create and initialize the scene renderer
    auto sceneRenderer = std::make_shared<warp::SceneRenderer>(scene);
    sceneRenderer->init();
    
    // The scene renderer will listen to window events
    windowInput.addListener(sceneRenderer);
    
    if (std::shared_ptr<warp::Shader> shader = shaderManager->get(shaderID))
    {
        shader->validate(); // Check if shader is ok
    }
    
    // This is the main loop
    auto loop = std::make_shared<warp::GameLoop>(
    [&windowInput, sceneRenderer, window]()
    {
        // Process window events
        windowInput.flush();
        
        // Handle continuous input
        sceneRenderer->processInput();
        
        // Draw the scene
        sceneRenderer->render();
        
        // Swap buffers
        window->display();
    });
    windowInput.addListener(loop);
    
    loop->run();
    
    window->close();

    return EXIT_SUCCESS;
}

