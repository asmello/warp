#include "CameraManager.hpp"

using namespace warp;

void CameraManager::setActive(Camera::ID id)
{
    if (activeID == id) return;
    cameras.at(static_cast<size_t>(id))->bind();
    activeID = id;
}

std::shared_ptr<Camera> CameraManager::get(Camera::ID id)
{
    return cameras.at(static_cast<size_t>(id));
}

Camera::ID CameraManager::add(std::shared_ptr<Camera> camera)
{
    cameras.push_back(camera);
    return Camera::ID(cameras.size()-1);
}

Camera::ID CameraManager::create()
{
    cameras.push_back(std::make_shared<Camera>());
    return Camera::ID(cameras.size()-1);
}