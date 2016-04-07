#include "Component.hpp"

#include "GameObjectManager.hpp"

using namespace warp;

Component::Component()
{
	auto gameObjectManager = GameObjectManager::getInstance();
	auto gameObjectID = gameObjectManager->create();
	gameObject = gameObjectManager->get(gameObjectID);
}

Component::Component(GameObject::ID gameObjectID)
: gameObject(GameObjectManager::getInstance()->get(gameObjectID))
{

}

Component::Component(std::shared_ptr<GameObject> gameObject)
	: gameObject(gameObject)
{

}

std::shared_ptr<GameObject> Component::getGameObject()
{
    return gameObject.lock();
}