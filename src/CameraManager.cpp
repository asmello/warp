#include "CameraManager.hpp"
#include "Camera.hpp"

using namespace warp;

void CameraManager::setActive(Object<Camera>::ID id)
{
//    if (activeID == id) return;
    resources.at(static_cast<size_t>(id))->bind();
    activeID = id;
}
