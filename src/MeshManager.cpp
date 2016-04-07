#include "MeshManager.hpp"

using namespace warp;

MeshID MeshManager::create()
{
    meshes.push_back(std::make_shared<Mesh>());
    return MeshID(meshes.size()-1);
}

MeshID MeshManager::add(std::shared_ptr<Mesh> mesh)
{
    meshes.push_back(mesh);
    return MeshID(meshes.size()-1);
}

std::shared_ptr<Mesh> MeshManager::get(MeshID id)
{
    return meshes.at(static_cast<int>(id));
}

void MeshManager::setActive(MeshID id)
{
    if (activeID == id) return;
    meshes.at(static_cast<int>(id))->bind();
    activeID = id;
}