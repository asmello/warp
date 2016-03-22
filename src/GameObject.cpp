#include "GameObject.hpp"

using namespace warp;

GameObject::GameObject(const std::shared_ptr<Texture> texture_,
                       const std::shared_ptr<Mesh> mesh_,
                       const std::shared_ptr<Transform> transform_) :
transform(transform_), texture(texture_), mesh(mesh_)
{
    
}

GameObject::GameObject(const std::shared_ptr<Texture> texture_,
                       const std::shared_ptr<Mesh> mesh_) :
transform(std::make_shared<warp::Transform>()), texture(texture_), mesh(mesh_)
{
    
}

void GameObject::init(const std::shared_ptr<const Shader> shader)
{
    texture->init(shader);
    transform->init(shader);
    mesh->init(shader);
}

void GameObject::draw()
{
    texture->bind();
    transform->bind();
    mesh->bind();
    mesh->draw();
}

std::shared_ptr<warp::Transform> GameObject::getTransform()
{
    return transform;
}

