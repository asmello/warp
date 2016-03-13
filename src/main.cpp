#include <GL/glew.h>

#include <SFML/Window.hpp>

#include "SimpleRenderer.hpp"
#include "Mesh.hpp"

bool processEvents(sf::Window& window)
{
    sf::Event windowEvent;
    while (window.pollEvent(windowEvent))
    {
        switch (windowEvent.type)
        {
            case sf::Event::Closed:
                return false;
                break;
            case sf::Event::KeyPressed:
                if (windowEvent.key.code == sf::Keyboard::Escape) {
                    return false;
                }
                break;
            default:
                break;
        }
    }
    return true;
}

int main(int, char const**)
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.majorVersion = 4;
    settings.minorVersion = 1;
    settings.attributeFlags = sf::ContextSettings::Core;
    
    sf::Window window(sf::VideoMode(1024, 800, 32), "OpenGL", sf::Style::Titlebar | sf::Style::Close, settings);
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    Mesh triangle{
        0.0f,  0.5f,
        0.5f, -0.5f,
        -0.5f, -0.5f
    };
    triangle.bind();
    
    // Create and initialize the scene renderer
    SimpleRenderer renderer;
    renderer.init();
    
    bool running = true;
    while (running)
    {
        running = processEvents(window);
        
        // Draw the scene
        renderer.draw();
        
        // Swap buffers
        window.display();
    }
    
    window.close();

    return EXIT_SUCCESS;
}
