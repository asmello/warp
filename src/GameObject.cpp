#include "GameObject.hpp"

using namespace warp;

GameObject::GameObject()
: transform(std::make_shared<Transform>())
{
    
}

std::shared_ptr<Transform> GameObject::getTransform()
{
    return transform;
}