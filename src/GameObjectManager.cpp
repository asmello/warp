#include "GameObjectManager.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"

using namespace warp;

void GameObjectManager::setActive(GameObject::ID id)
{
//    if (activeID == id) return;
    resources.at(static_cast<size_t>(id))->getTransform()->bind();
    activeID = id;
}
