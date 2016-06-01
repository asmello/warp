#include "MeshManager.hpp"
#include "Mesh.hpp"

using namespace warp;

void MeshManager::setActive(Mesh::ID id)
{
//    if (activeID == id) return;
    activeID = id;
}