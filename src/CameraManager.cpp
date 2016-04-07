#include "CameraManager.hpp"

using namespace warp;

void CameraManager::setActive(CameraID id)
{
    if (activeID == id) return;
    cameras.at(static_cast<int>(id))->bind();
    activeID = id;
}

std::shared_ptr<Camera> CameraManager::get(CameraID id)
{
    return cameras.at(static_cast<int>(id));
}

CameraID CameraManager::add(std::shared_ptr<Camera> camera)
{
    cameras.push_back(camera);
    return CameraID(cameras.size()-1);
}

CameraID CameraManager::create()
{
    cameras.push_back(std::make_shared<Camera>());
    return CameraID(cameras.size()-1);
}

template <typename... Args> CameraID CameraManager::create(Args&&... args)
{
    cameras.push_back(std::make_shared<Camera>(args...));
    return CameraID(cameras.size()-1);
}