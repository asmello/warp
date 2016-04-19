#include "GameObject.hpp"
#include "GameObjectManager.hpp"

#include "Transform.hpp"

using namespace warp;

template<> ResourceManager<GameObject> * Object<GameObject>::manager = GameObjectManager::getInstance();

GameObject::GameObject() : transform(std::make_shared<Transform>(id))
{
    
}

GameObject::GameObject(std::shared_ptr<Transform> transform_) : transform(transform_)
{
    
}

std::shared_ptr<Transform> GameObject::getTransform()
{
    return transform;
}