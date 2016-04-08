#include "Component.hpp"

#include "GameObjectManager.hpp"
#include "GameObject.hpp"

using namespace warp;

Component::Component()
{
    
}

Component::Component(GameObject::ID gameObject) : gameObjectID(gameObject)
{
    
}

GameObject::ID Component::getGameObjectID() const
{
    return gameObjectID;
}

std::shared_ptr<GameObject> Component::getGameObject() const
{
    return GameObjectManager::getInstance()->get(gameObjectID);
}