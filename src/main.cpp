#include <GL/glew.h>

#include <SFML/Window.hpp>

#include <memory>
#include <cstdio>

#include "SceneRenderer.hpp"
#include "MeshRenderer.hpp"
#include "MeshFilter.hpp"
#include "GameObject.hpp"
#include "Texture.hpp"
#include "Material.hpp"
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
    
    // Create a vertex/fragment shader program
    auto shader = std::make_shared<warp::Shader>();
    shader->loadFromFile(util::resourcePath() + "vertex.glsl", util::resourcePath() + "frag.glsl");
    
    // Create a texture
    auto texture = std::make_shared<warp::Texture>(GL_TEXTURE_2D);
    texture->loadFromFile(util::resourcePath() + "test.png");
    
    // Create a material
    auto material = std::make_shared<warp::Material>(shader, texture);
    
    // Create the scene object
    auto scene = std::make_shared<warp::Scene>();
    
    // Add a camera to the scene
    scene->createCamera();
    
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
    
    // Create a renderer for the pyramid, add it to the scene
    scene->createRenderer<warp::MeshRenderer>(material, std::make_shared<warp::MeshFilter>(pyramid));
    
    // Create a square
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
    
    // Create a renderer for the square, add it to the scene
    scene->createRenderer<warp::MeshRenderer>(material, square);
    
    // Create and initialize the scene renderer
    auto sceneRenderer = std::make_shared<warp::SceneRenderer>(scene);
    sceneRenderer->init();
    
    // The scene renderer will listen to window events
    windowInput.addListener(sceneRenderer);
    
    shader->validate(); // Check if shader is ok
    
    auto loop = std::make_shared<warp::GameLoop>([&windowInput, sceneRenderer, window]() {
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

