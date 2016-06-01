#include "Component.hpp"
#include "Scene.hpp"

using namespace warp;

Component::Component()
{
    
}

std::shared_ptr<GameObject> Component::getGameObject() const
{
    return gameObject.lock(); // defaults?
}

GameObject::ID Component::getGameObjectID() const
{
    if (std::shared_ptr<GameObject> go = gameObject.lock())
    {
        return go->getID();
    }
    else // defaults?
    {
        return GameObject::ID(-1);
    }
}