#include "MeshRenderer.hpp"

#include "GameObjectManager.hpp"
#include "MaterialManager.hpp"
#include "CameraManager.hpp"
#include "MeshManager.hpp"

using namespace warp;

MeshRenderer::MeshRenderer(GameObject::ID gameObject,
                           Material::ID material,
                           Mesh::ID mesh) :
Renderer(gameObject, material), meshID(mesh)
{
    
}

MeshRenderer::MeshRenderer(Material::ID material,
                           Mesh::ID mesh) :
Renderer(GameObjectManager::getInstance()->create(), material), meshID(mesh)
{
    
}

void MeshRenderer::render(Camera::ID cameraID)
{
    MaterialManager::getInstance()->setActive(materialID);
    CameraManager::getInstance()->setActive(cameraID);
    MeshManager::getInstance()->setActive(meshID);
    GameObjectManager::getInstance()->setActive(gameObjectID);
    
    if (std::shared_ptr<Mesh> mesh = MeshManager::getInstance()->get(meshID))
    {
        mesh->draw();
    }
}

