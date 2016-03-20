#include <GL/glew.h>

#include <SFML/Window.hpp>

#include <memory>
#include <cstdio>

#include "SimpleRenderer.hpp"
#include "GameObject.hpp"
#include "Mesh.hpp"
#include "util.hpp"

void processInput(warp::Renderer& renderer, std::shared_ptr<warp::GameObject> activeObject)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        activeObject->getTransform()->rotateZ(0.025f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
        activeObject->getTransform()->rotateZ(-0.025f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        activeObject->getTransform()->translate(-.01f, .0f, .0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        activeObject->getTransform()->translate(.0f, -.01f, .0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        activeObject->getTransform()->translate(.01f, .0f, .0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        activeObject->getTransform()->translate(.0f, .01f, .0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        activeObject->getTransform()->rotateX(0.025f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        activeObject->getTransform()->rotateX(-0.025f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        activeObject->getTransform()->rotateY(-0.025f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        activeObject->getTransform()->rotateY(0.025f);
    }
}

bool processEvents(sf::Window& window, warp::Renderer& renderer, std::shared_ptr<warp::GameObject> activeObject)
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
                switch (windowEvent.key.code) {
                    case sf::Keyboard::Escape:
                        return false;
                        break;
                    case sf::Keyboard::RBracket:
                        activeObject->getTransform()->scale(1.25f, 1.25f, 1.0f);
                        break;
                    case sf::Keyboard::LBracket:
                        activeObject->getTransform()->scale(0.8f, 0.8f, 1.0f);
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
                    activeObject->getTransform()->scale(1.0f + windowEvent.mouseWheelScroll.delta/10.0f,
                                        1.0f + windowEvent.mouseWheelScroll.delta/10.0f,
                                        1.0f);
                } else if (windowEvent.mouseWheelScroll.delta < -0.0f) {
                    activeObject->getTransform()->scale(1.0f / (1.0f + -windowEvent.mouseWheelScroll.delta/10.0f),
                                        1.0f / (1.0f + -windowEvent.mouseWheelScroll.delta/10.0f),
                                        1.0f);
                }
                break;
            case sf::Event::Resized:
                renderer.getCamera()->reshape(windowEvent.size.width, windowEvent.size.height);
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
    settings.antialiasingLevel = 4;
    settings.attributeFlags = sf::ContextSettings::Core;
    
    sf::Window window(sf::VideoMode(800, 800, 32), "Warp",
                      sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize,
                      settings);
    window.setVerticalSyncEnabled(true);
    
    glewExperimental = GL_TRUE;
    glewInit();
    glGetError(); // Discard error 500
    
    // List of active objects
    std::vector<std::shared_ptr<warp::GameObject>> objects;
    
    // Create a vertex/fragment shader program
    auto shader = std::make_shared<warp::Shader>();
    shader->loadFromFile(util::resourcePath() + "vertex.glsl", util::resourcePath() + "frag.glsl");
    
    // Create a texture
    auto texture = std::make_shared<warp::Texture>(GL_TEXTURE_2D);
    texture->loadFromFile(util::resourcePath() + "test.png");
    
    // Create a pyramid
    auto pyramid = std::make_shared<warp::Mesh>();
    pyramid->setVertices({
        -1.0f, -1.0f,  0.57730f,  0.0f, 0.0f,
        0.0f, -1.0f, -1.15475f,  0.5f, 0.0f,
        1.0f, -1.0f,  0.57730f,  1.0f, 0.0f,
        0.0f,  1.0f,  0.00000f,  0.5f, 1.0f
    });
    pyramid->setElementBuffer({
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        1, 2, 0
    });
    objects.push_back(std::make_shared<warp::GameObject>(texture, pyramid));
    
    // Add a square to the scene
    auto square = std::make_shared<warp::Mesh>();
    square->setVertices({
        -0.8f, 0.8f, 0.0f,  0.0f, 0.0f,
        -0.4f, 0.8f, 0.0f,  1.0f, 0.0f,
        -0.8f, 0.4f, 0.0f,  0.0f, 1.0f,
        -0.4f, 0.4f, 0.0f,  1.0f, 1.0f
    });
    square->setElementBuffer({
        0, 2, 1,
        2, 3, 1
    });
    objects.push_back(std::make_shared<warp::GameObject>(texture, square));
    
    // Create and initialize the scene renderer
    warp::SimpleRenderer renderer(objects);
    
    shader->bind(); // Need this before initializing objects
    renderer.init(shader);
    
    bool running = true;
    while (running)
    {
        // Process user input
        processInput(renderer, objects[0]);
        
        // Process window events
        running = processEvents(window, renderer, objects[0]);
        
        // Draw the scene
        renderer.draw();
        
        // Swap buffers
        window.display();
    }
    
    window.close();

    return EXIT_SUCCESS;
}

