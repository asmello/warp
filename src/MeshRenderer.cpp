#include "MeshRenderer.hpp"

#include "Scene.hpp"
#include "Material.hpp"
#include "MaterialManager.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Mesh.hpp"
#include "MeshManager.hpp"

#include <iostream>

#include "Scene.hpp"
#include "Transform.hpp"


using namespace warp;

MeshRenderer::MeshRenderer(Material::ID material, Mesh::ID mesh) : Renderer(), materialID(material), meshID(mesh)
{
    
}

void MeshRenderer::render()
{
    MaterialManager::getInstance()->setActive(materialID);
    this->getGameObject()->getTransform()->bind();
    MeshManager::getInstance()->setActive(meshID);
    
    if (std::shared_ptr<Mesh> mesh = MeshManager::getInstance()->get(meshID))
    {
        glBindVertexArray(mesh->vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh->elements.size()), GL_UNSIGNED_INT, 0);
    }
}

