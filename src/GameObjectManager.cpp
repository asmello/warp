#include "GameObjectManager.hpp"

using namespace warp;

void GameObjectManager::setActive(GameObjectManager::ID id)
{
    if (activeID == id) return;
    gameObjects.at(id)->getTransform()->bind();
    activeID = id;
}

std::shared_ptr<GameObject> GameObjectManager::get(GameObjectManager::ID id)
{
    return gameObjects.at(id);
}

GameObjectManager::ID GameObjectManager::add(std::shared_ptr<GameObject> gameObject)
{
    gameObjects.push_back(gameObject);
    return gameObjects.size()-1;
}

GameObjectManager::ID GameObjectManager::create()
{
    gameObjects.push_back(std::make_shared<GameObject>());
    return gameObjects.size()-1;
}