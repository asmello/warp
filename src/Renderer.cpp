#include "Renderer.hpp"

using namespace warp;

Renderer::Renderer(GameObjectID gameObject, MaterialID material)
: gameObjectID(gameObject), materialID(material)
{
    
}

Renderer::Renderer(MaterialID material)
: gameObjectID(GameObjectManager::getInstance()->create()), materialID(material)
{
    
}

GameObjectID Renderer::getGameObject()
{
    return gameObjectID;
}