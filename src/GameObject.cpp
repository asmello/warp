#include "GameObject.hpp"

#include "Transform.hpp"

using namespace warp;

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