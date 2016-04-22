#include "MeshRenderer.hpp"

#include "GameObject.hpp"
#include "GameObjectManager.hpp"
#include "Material.hpp"
#include "MaterialManager.hpp"
#include "Camera.hpp"
#include "CameraManager.hpp"
#include "Light.hpp"
#include "LightManager.hpp"
#include "Mesh.hpp"
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

void MeshRenderer::render(Camera::ID cameraID, std::vector<Light::ID> lights)
{
    MaterialManager::getInstance()->setActive(materialID);
    CameraManager::getInstance()->setActive(cameraID);
    MeshManager::getInstance()->setActive(meshID);
    GameObjectManager::getInstance()->setActive(gameObjectID);
    
    LightManager * lightManager = LightManager::getInstance();
    for (Light::ID lightID : lights)
    {
        lightManager->setActive(lightID);
    }
    
    if (std::shared_ptr<Mesh> mesh = MeshManager::getInstance()->get(meshID))
    {
        glBindVertexArray(mesh->vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh->elements.size()), GL_UNSIGNED_INT, 0);
    }
}

