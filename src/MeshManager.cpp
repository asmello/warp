#include "MeshManager.hpp"
#include "Mesh.hpp"

using namespace warp;

void MeshManager::setActive(Mesh::ID id)
{
//    if (activeID == id) return;
    resources.at(static_cast<size_t>(id))->bind();
    activeID = id;
}
