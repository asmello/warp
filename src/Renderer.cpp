#include "Renderer.hpp"

using namespace warp;

Renderer::Renderer(GameObjectID gameObject, MaterialID material)
: Component(gameObject), materialID(material)
{
    
}

Renderer::Renderer(MaterialID material)
: Component(), materialID(material)
{
    
}

GameObjectID Renderer::getGameObject()
{
    return gameObject;
}