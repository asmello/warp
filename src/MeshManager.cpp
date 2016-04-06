#include "MeshManager.hpp"

using namespace warp;

MeshManager::ID MeshManager::create()
{
    meshes.push_back(std::make_shared<Mesh>());
    return meshes.size()-1;
}

MeshManager::ID MeshManager::add(std::shared_ptr<Mesh> mesh)
{
    meshes.push_back(mesh);
    return meshes.size()-1;
}

std::shared_ptr<Mesh> MeshManager::get(ID id)
{
    return meshes.at(id);
}

void MeshManager::setActive(ID id)
{
    if (activeID == id) return;
    meshes.at(id)->bind();
    activeID = id;
}