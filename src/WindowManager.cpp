#include "WindowManager.hpp"

using namespace warp;

std::shared_ptr<Window> WindowManager::getActive()
{
    return resources.at(activeID);
}

std::vector<std::shared_ptr<Window>> WindowManager::getAll()
{
    return resources;
}