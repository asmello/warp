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

#include "SceneInitializer.hpp"



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

	// Create the scene object
	std::shared_ptr<warp::Scene> scene = warp::Scene::newScene();
	std::shared_ptr<warp::SceneRenderer> sRenderer = scene->newComponent<warp::SceneRenderer>();
    


	// These are resource managers
	auto shaderManager = warp::ShaderManager::getInstance();
	auto textureManager = warp::TextureManager::getInstance();
	auto materialManager = warp::MaterialManager::getInstance();
	auto meshManager = warp::MeshManager::getInstance();

	// Create a camera object
	std::shared_ptr<warp::GameObject> go1 = scene->newGameObject();
	std::shared_ptr<warp::Camera> camera = go1->newComponent<warp::Camera>();
	camera->setPosition(glm::vec3(0, 0, 5));
	camera->lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	camera.reset();

	// Populating scene
	SceneInitializer::Init(scene);




    // Initialize rendering context
    sRenderer->init();
    
    // The scene renderer will listen to window events
    windowInput.addListener(sRenderer);
    
	// TODO [scene.start]

    // This is the main loop
    auto loop = std::make_shared<warp::GameLoop>(
    [&windowInput, sRenderer, window]()
    {
        // Process window events
        windowInput.flush();
        
		// TODO [scene.update]

        // Handle continuous input
        sRenderer->processInput(); // TODO [Tirar isso daqui... quem recebe inputs são os behaviours]
        
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

