#include "Component.hpp"

using namespace warp;

std::shared_ptr<GameObject> Component::getGameObject()
{
    return gameObject.lock();
}