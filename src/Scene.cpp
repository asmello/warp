#include "Scene.hpp"

#include "Transform.hpp"

using namespace warp;

GameObject::GameObject()
{
    
}

GameObject::GameObject(std::shared_ptr<Transform> transform_) : transform(transform_)
{
    
}

bool GameObject::isRoot() const
{
    return transform->isRoot();
}

std::shared_ptr<Transform> GameObject::getTransform()
{
    return transform;
}

std::shared_ptr<Scene> GameObject::getScene()
{
    return std::static_pointer_cast<Scene>(transform->getRoot()->getGameObject());
}

std::shared_ptr<GameObject> Scene::newGameObject()
{
    return std::make_shared<GameObject>(getTransform()->newChild());
}
