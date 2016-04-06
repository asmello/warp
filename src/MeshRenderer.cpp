#include "MeshRenderer.hpp"

using namespace warp;

MeshRenderer::MeshRenderer(GameObjectManager::ID gameObject,
                           MaterialManager::ID material,
                           MeshManager::ID mesh) :
Renderer(gameObject, material), meshID(mesh)
{
    
}

MeshRenderer::MeshRenderer(MaterialManager::ID material,
                           MeshManager::ID mesh) :
Renderer(material), meshID(mesh)
{
    
}

void MeshRenderer::render(CameraManager::ID cameraID)
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

