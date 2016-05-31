#include "Component.hpp"

using namespace warp;

Component::Component()
{
    
}

std::shared_ptr<GameObject> Component::getGameObject() const
{
    return gameObject.lock(); // defaults?
}