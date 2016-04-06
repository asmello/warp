#include "Renderer.hpp"

using namespace warp;

Renderer::Renderer(GameObjectManager::ID gameObject, MaterialManager::ID material)
: gameObjectID(gameObject), materialID(material)
{
    
}

Renderer::Renderer(MaterialManager::ID material)
: gameObjectID(GameObjectManager::getInstance()->create()), materialID(material)
{
    
}

GameObjectManager::ID Renderer::getGameObject()
{
    return gameObjectID;
}