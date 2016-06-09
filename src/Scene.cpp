#include "Scene.hpp"

#include "Transform.hpp"

#include "Behaviour1.hpp"
#include "Behaviour2.hpp"
#include "Behaviour3.hpp"
#include "Behaviour4.hpp"
#include "Behaviour5.hpp"
#include "Behaviour6.hpp"
#include "Behaviour7.hpp"
#include "Behaviour8.hpp"
#include "Behaviour9.hpp"
#include "Behaviour10.hpp"

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


void Scene::Behaviour_Start() // TODO [Fix getComponents not being able to get inherited]
{
	{ auto behaviourList = getComponentsInChildren<Behaviour1>();
	for (int i = 0; i < behaviourList.size(); i++) behaviourList[i]->Start(); }
	{ auto behaviourList = getComponentsInChildren<Behaviour2>();
	for (int i = 0; i < behaviourList.size(); i++) behaviourList[i]->Start(); }
	{ auto behaviourList = getComponentsInChildren<Behaviour3>();
	for (int i = 0; i < behaviourList.size(); i++) behaviourList[i]->Start(); }
	{ auto behaviourList = getComponentsInChildren<Behaviour4>();
	for (int i = 0; i < behaviourList.size(); i++) behaviourList[i]->Start(); }
	{ auto behaviourList = getComponentsInChildren<Behaviour5>();
	for (int i = 0; i < behaviourList.size(); i++) behaviourList[i]->Start(); }
	{ auto behaviourList = getComponentsInChildren<Behaviour6>();
	for (int i = 0; i < behaviourList.size(); i++) behaviourList[i]->Start(); }
	{ auto behaviourList = getComponentsInChildren<Behaviour7>();
	for (int i = 0; i < behaviourList.size(); i++) behaviourList[i]->Start(); }
	{ auto behaviourList = getComponentsInChildren<Behaviour8>();
	for (int i = 0; i < behaviourList.size(); i++) behaviourList[i]->Start(); }
	{ auto behaviourList = getComponentsInChildren<Behaviour9>();
	for (int i = 0; i < behaviourList.size(); i++) behaviourList[i]->Start(); }
	{ auto behaviourList = getComponentsInChildren<Behaviour10>();
	for (int i = 0; i < behaviourList.size(); i++) behaviourList[i]->Start(); }
}
void Scene::Behaviour_Update()
{
	{ auto behaviourList = getComponentsInChildren<Behaviour1>();
	for (int i = 0; i < behaviourList.size(); i++) behaviourList[i]->Update(); }
	{ auto behaviourList = getComponentsInChildren<Behaviour2>();
	for (int i = 0; i < behaviourList.size(); i++) behaviourList[i]->Update(); }
	{ auto behaviourList = getComponentsInChildren<Behaviour3>();
	for (int i = 0; i < behaviourList.size(); i++) behaviourList[i]->Update(); }
	{ auto behaviourList = getComponentsInChildren<Behaviour4>();
	for (int i = 0; i < behaviourList.size(); i++) behaviourList[i]->Update(); }
	{ auto behaviourList = getComponentsInChildren<Behaviour5>();
	for (int i = 0; i < behaviourList.size(); i++) behaviourList[i]->Update(); }
	{ auto behaviourList = getComponentsInChildren<Behaviour6>();
	for (int i = 0; i < behaviourList.size(); i++) behaviourList[i]->Update(); }
	{ auto behaviourList = getComponentsInChildren<Behaviour7>();
	for (int i = 0; i < behaviourList.size(); i++) behaviourList[i]->Update(); }
	{ auto behaviourList = getComponentsInChildren<Behaviour8>();
	for (int i = 0; i < behaviourList.size(); i++) behaviourList[i]->Update(); }
	{ auto behaviourList = getComponentsInChildren<Behaviour9>();
	for (int i = 0; i < behaviourList.size(); i++) behaviourList[i]->Update(); }
	{ auto behaviourList = getComponentsInChildren<Behaviour10>();
	for (int i = 0; i < behaviourList.size(); i++) behaviourList[i]->Update(); }
}