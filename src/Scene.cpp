#include "Scene.hpp"

#include "CameraManager.hpp"

using namespace warp;

std::vector<Camera::ID> Scene::getCameras()
{
    return cameras;
}

std::vector<std::shared_ptr<Renderer>> Scene::getRenderers()
{
    return renderers;
}

void Scene::addCamera(Camera::ID camera)
{
    cameras.push_back(camera);
}

void Scene::createCamera()
{
    cameras.push_back(CameraManager::getInstance()->create());
}

void Scene::addRenderer(std::shared_ptr<Renderer> renderer)
{
    renderers.push_back(renderer);
}