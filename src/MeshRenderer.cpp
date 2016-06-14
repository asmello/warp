#include "MeshRenderer.hpp"

#include "Scene.hpp"
#include "Material.hpp"
#include "MaterialManager.hpp"
#include "Mesh.hpp"
#include "MeshManager.hpp"
#include "Transform.hpp"
#include "ShaderManager.hpp"


using namespace warp;

MeshRenderer::MeshRenderer(Material::ID material, Mesh::ID mesh) : Renderer(), materialID(material), meshID(mesh)
{
    
}

void MeshRenderer::render(float time)
{
    MaterialManager::getInstance()->setActive(materialID);
    this->getGameObject()->getTransform()->bind();
    MeshManager::getInstance()->setActive(meshID);
    
    // Send time to shader
    if (std::shared_ptr<Shader> activeShader = ShaderManager::getInstance()->getActive()) {
        glUniform1f(activeShader->getUniformLocation("u_time"), time);
    }
    
    if (std::shared_ptr<Mesh> mesh = MeshManager::getInstance()->get(meshID))
    {
        glBindVertexArray(mesh->vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh->elements.size()), GL_UNSIGNED_INT, 0);
    }
}

