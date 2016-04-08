#include "GameObject.hpp"

#include "Transform.hpp"

using namespace warp;

GameObject::GameObject() :
transform(std::make_shared<Transform>(id))
{
    
}

std::shared_ptr<Transform> GameObject::getTransform()
{
    return transform;
}