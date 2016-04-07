#include "GameObjectManager.hpp"

using namespace warp;

void GameObjectManager::setActive(GameObjectID id)
{
    if (activeID == id) return;
    gameObjects.at(static_cast<int>(id))->getTransform()->bind();
    activeID = id;
}

std::shared_ptr<GameObject> GameObjectManager::get(GameObjectID id)
{
    return gameObjects.at(static_cast<int>(id));
}

GameObjectID GameObjectManager::add(std::shared_ptr<GameObject> gameObject)
{
    gameObjects.push_back(gameObject);
    return GameObjectID(gameObjects.size()-1);
}

GameObjectID GameObjectManager::create()
{
    gameObjects.push_back(std::make_shared<GameObject>());
    return GameObjectID(gameObjects.size()-1);
}