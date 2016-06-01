#include "MeshRenderer.hpp"

#include "GameObject.hpp"
#include "Material.hpp"
#include "MaterialManager.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Mesh.hpp"
#include "MeshManager.hpp"

using namespace warp;

MeshRenderer::MeshRenderer(Material::ID material, Mesh::ID mesh) : Renderer(), materialID(material), meshID(mesh)
{
    
}

void MeshRenderer::activate()
{
    Renderer::activate();
    MaterialManager::getInstance()->setActive(materialID);
    MeshManager::getInstance()->setActive(meshID);
}

void MeshRenderer::render()
{
    if (std::shared_ptr<Mesh> mesh = MeshManager::getInstance()->get(meshID))
    {
        glBindVertexArray(mesh->vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh->elements.size()), GL_UNSIGNED_INT, 0);
    }
}

