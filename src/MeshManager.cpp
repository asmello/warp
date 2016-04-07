#include "MeshManager.hpp"

using namespace warp;

Mesh::ID MeshManager::create()
{
    meshes.push_back(std::make_shared<Mesh>());
    return Mesh::ID(meshes.size()-1);
}

Mesh::ID MeshManager::add(std::shared_ptr<Mesh> mesh)
{
    meshes.push_back(mesh);
    return Mesh::ID(meshes.size()-1);
}

std::shared_ptr<Mesh> MeshManager::get(Mesh::ID id)
{
    return meshes.at(static_cast<long>(id));
}

void MeshManager::setActive(Mesh::ID id)
{
    if (activeID == id) return;
    meshes.at(static_cast<long>(id))->bind();
    activeID = id;
}