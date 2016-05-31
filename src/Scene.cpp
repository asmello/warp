#include "Scene.hpp"

using namespace warp;

std::shared_ptr<Scene> Scene::getScene()
{
    return std::make_shared<Scene>(this);
}