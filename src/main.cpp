#include <GL/glew.h>

#include <SFML/Window.hpp>

#include <thread>
#include <chrono>
#include <memory>
#include <cmath>
#include <iostream>

#include "SimpleRenderer.hpp"
#include "Mesh.hpp"

int main(int, char const**)
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.majorVersion = 4;
    settings.minorVersion = 1;
    settings.attributeFlags = sf::ContextSettings::Core;
    
    sf::Window window(sf::VideoMode(1024, 800, 32), "OpenGL", sf::Style::Titlebar | sf::Style::Close, settings);
    window.setVerticalSyncEnabled(true);
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    auto triangle = std::make_shared<Mesh, std::initializer_list<float>>({
        0.0f,  0.5f,
        0.5f, -0.5f,
        -0.5f, -0.5f
    });
    triangle->bind();
    
    std::vector<std::shared_ptr<Mesh>> objects;
    objects.push_back(triangle);
    
    // Create and initialize the scene renderer
    SimpleRenderer renderer;
    renderer.init(objects);
    
    bool running = true;
    while (running)
    {
        sf::Event windowEvent;
        while (window.pollEvent(windowEvent))
        {
            switch (windowEvent.type)
            {
                case sf::Event::Closed:
                    running = false;
                    break;
                case sf::Event::KeyPressed:
                    switch (windowEvent.key.code) {
                        case sf::Keyboard::Escape:
                            running = false;
                            break;
                        case sf::Keyboard::RBracket:
                            triangle->scale(1.25, 1.25, 1.0);
                            break;
                        case sf::Keyboard::LBracket:
                            triangle->scale(0.8, 0.8, 1.0);
                            break;
                        default:
                            break;
                    }
                    break;
                case sf::Event::MouseWheelScrolled:
                    if (windowEvent.mouseWheelScroll.delta > 0.0f) {
                        triangle->scale(1.0f + windowEvent.mouseWheelScroll.delta/10.0f,
                                        1.0f + windowEvent.mouseWheelScroll.delta/10.0f,
                                        1.0f);
                    } else if (windowEvent.mouseWheelScroll.delta < -0.0f) {
                        triangle->scale(1.0f / (1.0f + -windowEvent.mouseWheelScroll.delta/10.0f),
                                        1.0f / (1.0f + -windowEvent.mouseWheelScroll.delta/10.0f),
                                        1.0f);
                    }
                    break;
                default:
                    break;
            }
        }
        
        // Draw the scene
        renderer.draw();
        
        // Swap buffers
        window.display();
    }
    
    window.close();

    return EXIT_SUCCESS;
}
