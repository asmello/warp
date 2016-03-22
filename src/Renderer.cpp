#include "Renderer.hpp"

using namespace warp;

Renderer::Renderer(const std::vector<std::shared_ptr<GameObject>>& objects_) :
paused(false), camera(std::make_shared<Camera>()), objects(objects_) { }

Renderer::Renderer(std::shared_ptr<Camera> camera_,
                   const std::vector<std::shared_ptr<GameObject>>& objects_) :
paused(false), camera(camera_), objects(objects_) { }

void Renderer::pause()
{
    paused = !paused;
}

bool Renderer::isPaused() const
{
    return paused;
}

void Renderer::setCamera(std::shared_ptr<Camera> camera_)
{
    camera = camera_;
}

std::shared_ptr<Camera> Renderer::getCamera()
{
    return camera;
}

void Renderer::init(const std::shared_ptr<const Shader> shader)
{
    camera->init(shader);
}