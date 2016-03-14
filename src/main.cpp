#include <GL/glew.h>

#include <SFML/Window.hpp>

#include <thread>
#include <chrono>
#include <memory>
#include <cmath>
#include <iostream>

#include "SimpleRenderer.hpp"
#include "Mesh.hpp"

bool processInput(sf::Window& window, Renderer& renderer, std::shared_ptr<Mesh> activeObject)
{
    sf::Event windowEvent;
    
    // Process user input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        activeObject->rotateZ(0.025);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
        activeObject->rotateZ(-0.025);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        activeObject->translate(-.01f, .0f, .0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        activeObject->translate(.0f, -.01f, .0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        activeObject->translate(.01f, .0f, .0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        activeObject->translate(.0f, .01f, .0f);
    }
    
    // Process window events
    while (window.pollEvent(windowEvent))
    {
        switch (windowEvent.type)
        {
            case sf::Event::Closed:
                return false;
                break;
            case sf::Event::KeyPressed:
                switch (windowEvent.key.code) {
                    case sf::Keyboard::Escape:
                        return false;
                        break;
                    case sf::Keyboard::RBracket:
                        activeObject->scale(1.25, 1.25, 1.0);
                        break;
                    case sf::Keyboard::LBracket:
                        activeObject->scale(0.8, 0.8, 1.0);
                        break;
                    case sf::Keyboard::Space:
                        renderer.pause();
                        break;
                    default:
                        break;
                }
                break;
            case sf::Event::MouseWheelScrolled:
                if (windowEvent.mouseWheelScroll.delta > 0.0f) {
                    activeObject->scale(1.0f + windowEvent.mouseWheelScroll.delta/10.0f,
                                        1.0f + windowEvent.mouseWheelScroll.delta/10.0f,
                                        1.0f);
                } else if (windowEvent.mouseWheelScroll.delta < -0.0f) {
                    activeObject->scale(1.0f / (1.0f + -windowEvent.mouseWheelScroll.delta/10.0f),
                                        1.0f / (1.0f + -windowEvent.mouseWheelScroll.delta/10.0f),
                                        1.0f);
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
    
    sf::Window window(sf::VideoMode(1024, 1024, 32), "OpenGL", sf::Style::Titlebar | sf::Style::Close, settings);
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
    SimpleRenderer renderer(objects);
    renderer.init();
    
    bool running = true;
    while (running)
    {
        // Process user input
        running = processInput(window, renderer, triangle);
        
        // Draw the scene
        renderer.draw();
        
        // Swap buffers
        window.display();
    }
    
    window.close();

    return EXIT_SUCCESS;
}
