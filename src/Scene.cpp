#include "Scene.hpp"
#include "SceneRenderer.hpp"

#include "Transform.hpp"
#include "Behavior.hpp"

using namespace warp;

GameObject::GameObject() : transform(std::make_shared<Transform>())
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
    auto gameObject = std::make_shared<GameObject>(getTransform()->newChild());
    gameObject->transform->gameObject = gameObject;
	gameObjectList.push_back(gameObject);
    return gameObject;
}

std::shared_ptr<Scene> Scene::newScene()
{
    auto scene = std::make_shared<Scene>();
    scene->transform->gameObject = scene;
    return scene;
}

void Scene::start()
{
    auto behaviors = getComponents<Behavior>();
    for (auto behavior : behaviors)
    {
        behavior->start();
    }
}
void Scene::update()
{
    for (auto behavior : getComponents<Behavior>())
    {
        behavior->update();
    }
    if (auto renderer = getComponent<SceneRenderer>())
    {
        renderer->render();
    }
}