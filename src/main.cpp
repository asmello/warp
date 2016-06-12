#include <GL/glew.h>
#include <SFML/Window.hpp>

#include <memory>

#include "GameLoop.hpp"
#include "Input.hpp"
#include "Scene.hpp"

#include "scripts/Behavior10.hpp"
#include "scripts/SceneInitializer.hpp"

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
                                               sf::Style::Fullscreen, //sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize,
                                               settings);
    window->setVerticalSyncEnabled(true);
    
    warp::WindowManager::getInstance()->create(window);
    
    glewExperimental = GL_TRUE;
    glewInit();
    glGetError(); // Discard error 500

	// Create the scene object
	std::shared_ptr<warp::Scene> scene = warp::Scene::newScene();

	// Populating scene
	SceneInitializer::init(scene);
    
	// Set scene into motion
	scene->start();

    // This is the main loop
    auto loop = std::make_shared<warp::GameLoop>(
    [window, scene]()
    {
        // Process window events
        Input::flush();
        
		// Update scene
        scene->update();
        
        // Swap buffers
        window->display();
    });
    Input::addListener(loop);
    
    loop->run();
    
    window->close();

    return EXIT_SUCCESS;
}

