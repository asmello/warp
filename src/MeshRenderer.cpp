#include "MeshRenderer.hpp"

using namespace warp;

MeshRenderer::MeshRenderer(GameObjectID gameObject,
                           MaterialID material,
                           MeshID mesh) :
Renderer(gameObject, material), meshID(mesh)
{
    
}

MeshRenderer::MeshRenderer(MaterialID material,
                           MeshID mesh) :
Renderer(material), meshID(mesh)
{
    
}

void MeshRenderer::render(CameraID cameraID)
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

