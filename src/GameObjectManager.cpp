#include "GameObjectManager.hpp"

using namespace warp;

void GameObjectManager::setActive(GameObject::ID id)
{
    if (activeID == id) return;
    gameObjects.at(static_cast<size_t>(id))->getTransform()->bind();
    activeID = id;
}

std::shared_ptr<GameObject> GameObjectManager::get(GameObject::ID id)
{
    return gameObjects.at(static_cast<size_t>(id));
}

GameObject::ID GameObjectManager::add(std::shared_ptr<GameObject> gameObject)
{
    gameObjects.push_back(gameObject);
    return GameObject::ID(gameObjects.size()-1);
}

GameObject::ID GameObjectManager::create()
{
    gameObjects.push_back(std::make_shared<GameObject>());
    return GameObject::ID(gameObjects.size()-1);
}