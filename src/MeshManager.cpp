#include "MeshManager.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "GameObjectManager.hpp"
#include "Transform.hpp"

#include "util.hpp"

using namespace warp;

void MeshManager::setActive(Mesh::ID id)
{
//    if (activeID == id) return;
    activeID = id;
}