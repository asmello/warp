#include "Scene.hpp"
#include "SceneManager.hpp"

#include "Mesh.hpp"
#include "MeshManager.hpp"
#include "Light.hpp"
#include "LightManager.hpp"
#include "Camera.hpp"
#include "CameraManager.hpp"
#include "GameObject.hpp"
#include "GameObjectManager.hpp"
#include "Transform.hpp"

using namespace warp;

template<> ResourceManager<Scene> * Object<Scene>::manager = SceneManager::getInstance();

std::vector<Camera::ID> Scene::getCameras()
{
    return cameras;
}

std::vector<std::shared_ptr<Renderer>> Scene::getRenderers()
{
    return renderers;
}

std::vector<Light::ID> Scene::getLights()
{
    return lights;
}

void Scene::addCamera(Camera::ID camera)
{
    cameras.push_back(camera);
}

void Scene::addLight(Light::ID light)
{
    lights.push_back(light);
}

void Scene::createCamera()
{
    cameras.push_back(CameraManager::getInstance()->create());
}

void Scene::addRenderer(std::shared_ptr<Renderer> renderer)
{
    renderers.push_back(renderer);
}
