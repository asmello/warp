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

#include "scripts/SceneInitializer.hpp"
#include "SceneManager.hpp"
#include "scripts/Behavior10.hpp"

int main(int, char const**)
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.majorVersion = 4;
    settings.minorVersion = 1;
    settings.antialiasingLevel = 4;
    settings.attributeFlags = sf::ContextSettings::Core;
    
    auto window = std::make_shared<sf::Window>(sf::VideoMode(1024, 1024, 32), "Warp",
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

	// Populating scene
	SceneInitializer::init(scene);

    // Initialize rendering context
    sRenderer->init();
    
    // The scene renderer will listen to window events
    windowInput.addListener(sRenderer);
    
	// Start scene behaviour
	scene->behaviorStart();

    // This is the main loop
    auto loop = std::make_shared<warp::GameLoop>(
    [&windowInput, sRenderer, window, scene]()
    {
        // Process window events
        windowInput.flush();
        
		// Update scene behaviour
		scene->behaviorUpdate();
        
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

