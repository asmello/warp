#include <GL/glew.h>

#include <SFML/Window.hpp>

#include <memory>
#include <cstdio>

#include "SimpleRenderer.hpp"
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
    auto renderer = std::make_shared<warp::SimpleRenderer>(objects);
    windowInput.addListener(renderer);
    shader->bind(); // Need this before initializing objects
    renderer->init(shader);
    
    shader->validate(); // Check if shader is ok
    
    auto loop = std::make_shared<warp::GameLoop>([&windowInput, renderer, window]() {
        // Process window events
        windowInput.flush();
        
        // Handle continuous input
        renderer->processInput();
        
        // Draw the scene
        renderer->draw();
        
        // Swap buffers
        window->display();
    });
    windowInput.addListener(loop);
    
    loop->run();
    
    window->close();

    return EXIT_SUCCESS;
}

