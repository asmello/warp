#include "MeshRenderer.hpp"

using namespace warp;

MeshRenderer::MeshRenderer(const std::shared_ptr<GameObject> gameObject,
                           MaterialManager::ID material,
                           MeshManager::ID mesh) :
Renderer(gameObject, material), mesh(MeshManager::getInstance()->get(mesh))
{
    
}

MeshRenderer::MeshRenderer(MaterialManager::ID material,
                           MeshManager::ID mesh) :
Renderer(material), mesh(MeshManager::getInstance()->get(mesh))
{
    
}

void MeshRenderer::init()
{
    mesh->init();
}

void MeshRenderer::render()
{
    gameObject->getTransform()->bind();
    material->bind();
    mesh->bind();
    mesh->draw();
}

