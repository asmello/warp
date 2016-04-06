#include "MeshRenderer.hpp"

using namespace warp;

MeshRenderer::MeshRenderer(const std::shared_ptr<GameObject> gameObject_,
                           const std::shared_ptr<Material> material_,
                           const std::shared_ptr<Mesh> mesh_) :
Renderer(gameObject_, material_), mesh(mesh_)
{
    
}

MeshRenderer::MeshRenderer(const std::shared_ptr<Material> material_,
                           const std::shared_ptr<Mesh> mesh_) :
Renderer(material_), mesh(mesh_)
{
    
}

void MeshRenderer::init()
{
    material->bind();
    mesh->init(material->getShader());
}

void MeshRenderer::render()
{
    gameObject->getTransform()->bind();
    material->bind();
    mesh->bind();
    mesh->draw();
}

