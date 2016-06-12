#include "WindowManager.hpp"

using namespace warp;

std::shared_ptr<Window> WindowManager::getActive()
{
    for (auto window : resources)
    {
        if (window->window->hasFocus())
        {
            return window;
        }
    }
    return nullptr;
}