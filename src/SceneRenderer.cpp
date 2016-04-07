#include "SceneRenderer.hpp"
#include "Mesh.hpp"
#include "util.hpp"

#include <SFML/Window.hpp>

using namespace warp;

SceneRenderer::SceneRenderer(std::shared_ptr<Scene> scene_)
: scene(scene_), activeGameObjectID(0), activeCameraID(0), t_total(0.0), paused(false)
{
    
}

void SceneRenderer::pause()
{
    paused = !paused;
}

bool SceneRenderer::isPaused() const
{
    return paused;
}

void SceneRenderer::init()
{
    // Set the background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    // Start counting time
    t_last = std::chrono::high_resolution_clock::now();
    
    // Set geometry shader settings
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
}

void SceneRenderer::render()
{
    // Clear the screen to black
    glClear(GL_COLOR_BUFFER_BIT);
    
    auto t_now = std::chrono::high_resolution_clock::now();
    
    // Update total elapsed time (if not paused)
    if (!paused) {
        t_total += std::chrono::duration_cast<std::chrono::duration<double>>(t_now - t_last).count();
    }
    t_last = t_now; // Update last tick
    
    // For each camera in the scene
    for (CameraID cameraID : scene->getCameras())
    {
        // Render visible objects
        for (std::shared_ptr<Renderer>& renderer : scene->getRenderers()) renderer->render(cameraID);
    }
}

void SceneRenderer::onKeyDown(Input::Key type)
{
    switch (type) {
        case Input::Key::LBracket:
            getActiveGameObject()->getTransform()->scale(1.25f, 1.25f, 1.25f);
            break;
        case Input::Key::RBracket:
            getActiveGameObject()->getTransform()->scale(0.8f, 0.8f, 0.8f);
            break;
        case Input::Key::Space:
            pause();
            break;
        default:
            break;
    }
}

void SceneRenderer::onMouseScrolled(float delta)
{
    float scaleFactor;
    if (delta >= 0.0f) {
        scaleFactor = 1.0f + delta/10.0f;
    } else {
        scaleFactor = 1.0f / (1.0f + -delta/10.0f);
    }
    getActiveGameObject()->getTransform()->scale(scaleFactor);
}

void SceneRenderer::onResized(int width, int height)
{
    if (std::shared_ptr<Camera> camera = CameraManager::getInstance()->get(activeCameraID))
    {
        camera->reshape(width, height);
    }
}

std::shared_ptr<GameObject> SceneRenderer::getActiveGameObject()
{
    return GameObjectManager::getInstance()->get(activeGameObjectID);
}

void SceneRenderer::processInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        getActiveGameObject()->getTransform()->rotateZ(0.025f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
        getActiveGameObject()->getTransform()->rotateZ(-0.025f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        getActiveGameObject()->getTransform()->translate(-.01f, .0f, .0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        getActiveGameObject()->getTransform()->translate(.0f, -.01f, .0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        getActiveGameObject()->getTransform()->translate(.01f, .0f, .0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        getActiveGameObject()->getTransform()->translate(.0f, .01f, .0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        getActiveGameObject()->getTransform()->rotateX(0.025f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        getActiveGameObject()->getTransform()->rotateX(-0.025f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        getActiveGameObject()->getTransform()->rotateY(-0.025f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        getActiveGameObject()->getTransform()->rotateY(0.025f);
    }
}

