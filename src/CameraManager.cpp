#include "CameraManager.hpp"

using namespace warp;

void CameraManager::setActive(CameraManager::ID id)
{
    if (activeID == id) return;
    cameras.at(id)->bind();
    activeID = id;
}

std::shared_ptr<Camera> CameraManager::get(CameraManager::ID id)
{
    return cameras.at(id);
}

CameraManager::ID CameraManager::add(std::shared_ptr<Camera> camera)
{
    cameras.push_back(camera);
    return cameras.size()-1;
}

CameraManager::ID CameraManager::create()
{
    cameras.push_back(std::make_shared<Camera>());
    return cameras.size()-1;
}

template <typename... Args> CameraManager::ID CameraManager::create(Args&&... args)
{
    cameras.push_back(std::make_shared<Camera>(args...));
    return cameras.size()-1;
}