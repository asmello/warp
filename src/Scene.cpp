#include "Scene.hpp"

using namespace warp;

Scene::Scene()
{
    
}

std::shared_ptr<Scene> Scene::getScene()
{
    return std::make_shared<Scene>(this);
}