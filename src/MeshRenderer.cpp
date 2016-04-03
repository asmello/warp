#include "MeshRenderer.hpp"

using namespace warp;

MeshRenderer::MeshRenderer(const std::shared_ptr<Mesh> mesh_,
                           const std::shared_ptr<Material> material_,
                           const std::shared_ptr<GameObject> gameobject_) :
gameobject(gameobject_), material(material_), mesh(mesh_)
{
    
}

MeshRenderer::MeshRenderer(const std::shared_ptr<Mesh> mesh_,
                           const std::shared_ptr<Material> material_) :
gameobject(std::make_shared<warp::GameObject>()), material(material_), mesh(mesh_)
{
    
}

void MeshRenderer::init()
{
    material->bind();
    mesh->init();
}

void MeshRenderer::draw()
{
    gameobject->getTransform()->bind();
    material->bind();
    mesh->draw();
}

