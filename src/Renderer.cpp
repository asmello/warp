#include "Renderer.hpp"

#include "GameObjectManager.hpp"

using namespace warp;

Renderer::Renderer(GameObject::ID gameObject, Material::ID material)
: Component(gameObject), materialID(material), active(true)
{
    
}

Renderer::Renderer(Material::ID material)
: Component(GameObjectManager::getInstance()->create()), materialID(material), active(true)
{
    
}

GameObject::ID Renderer::getGameObjectID() const
{
	return gameObjectID;
}