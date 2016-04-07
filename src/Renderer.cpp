#include "Renderer.hpp"

using namespace warp;

Renderer::Renderer(GameObject::ID gameObject, Material::ID material)
: Component(gameObject), materialID(material)
{
    
}

Renderer::Renderer(Material::ID material)
: Component(), materialID(material)
{
    
}

GameObject::ID Renderer::getGameObjectID() const
{
	return gameObjectID;
}