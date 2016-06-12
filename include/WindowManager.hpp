#ifndef ScreenManager_hpp
#define ScreenManager_hpp

#include "Window.hpp"
#include "Singleton.hpp"
#include "ResourceManager.hpp"

namespace warp {
    class WindowManager : public ResourceManager<Window>, public Singleton<WindowManager>
    {
    public:
        std::shared_ptr<Window> getActive();
    };
}

#endif /* ScreenManager_hpp */
