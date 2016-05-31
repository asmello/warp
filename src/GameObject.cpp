#include "GameObject.hpp"

#include "Transform.hpp"

using namespace warp;

GameObject::GameObject()
{
    
}

std::shared_ptr<Transform> GameObject::getTransform()
{
    return transform;
}

std::shared_ptr<Scene> GameObject::getScene()
{
    return transform->getRoot()->getGameObject()->getScene();
}