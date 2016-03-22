#include "SimpleRenderer.hpp"
#include "Mesh.hpp"
#include "util.hpp"

using namespace warp;

SimpleRenderer::SimpleRenderer(const std::vector<std::shared_ptr<warp::GameObject>>& objs) :
Renderer(objs), activeIndex(0), t_total(0.0)
{
    
}

SimpleRenderer::SimpleRenderer(const std::shared_ptr<warp::Camera> camera,
                               const std::vector<std::shared_ptr<warp::GameObject>>& objs) :
Renderer(camera, objs), activeIndex(0), t_total(0.0)
{
    
}

void SimpleRenderer::init(const std::shared_ptr<const Shader> shader)
{
    Renderer::init(shader); // Parent initializer
    
    for (auto obj : objects) obj->init(shader);
    
    // Set the background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    // Start counting time
    t_last = std::chrono::high_resolution_clock::now();
    
    // Set geometry shader settings
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
}

void SimpleRenderer::draw()
{
    // Clear the screen to black
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Get current time
    auto t_now = std::chrono::high_resolution_clock::now();
    
    // Update total elapsed time (if not paused)
    if (!paused) {
        t_total += std::chrono::duration_cast<std::chrono::duration<double>>(t_now - t_last).count();
    }
    
    // Update last tick
    t_last = t_now;
    
    // Update the camera
    camera->update();
    
    // Draw the objects
    for (auto obj : objects) obj->draw();
}

std::shared_ptr<GameObject> SimpleRenderer::getActiveObject()
{
    return objects[activeIndex];
}

void SimpleRenderer::onKeyDown(Input::Key type)
{
    switch (type) {
        case Input::Key::LBracket:
            getActiveObject()->getTransform()->scale(1.25f, 1.25f, 1.25f);
            break;
        case Input::Key::RBracket:
            getActiveObject()->getTransform()->scale(0.8f, 0.8f, 0.8f);
            break;
        case Input::Key::Space:
            pause();
            break;
        default:
            break;
    }
}

void SimpleRenderer::onMouseScrolled(float delta)
{
    float scaleFactor;
    if (delta >= 0.0f) {
        scaleFactor = 1.0f + delta/10.0f;
    } else {
        scaleFactor = 1.0f / (1.0f + -delta/10.0f);
    }
    getActiveObject()->getTransform()->scale(scaleFactor);
}

void SimpleRenderer::onResized(int width, int height)
{
    camera->reshape(width, height);
}

//void processInput(warp::Renderer& renderer, std::shared_ptr<warp::GameObject> activeObject)
//{
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
//    {
//        activeObject->getTransform()->rotateZ(0.025f);
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
//    {
//        activeObject->getTransform()->rotateZ(-0.025f);
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
//    {
//        activeObject->getTransform()->translate(-.01f, .0f, .0f);
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
//    {
//        activeObject->getTransform()->translate(.0f, -.01f, .0f);
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
//    {
//        activeObject->getTransform()->translate(.01f, .0f, .0f);
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
//    {
//        activeObject->getTransform()->translate(.0f, .01f, .0f);
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//    {
//        activeObject->getTransform()->rotateX(0.025f);
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
//    {
//        activeObject->getTransform()->rotateX(-0.025f);
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
//    {
//        activeObject->getTransform()->rotateY(-0.025f);
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//    {
//        activeObject->getTransform()->rotateY(0.025f);
//    }
//}

