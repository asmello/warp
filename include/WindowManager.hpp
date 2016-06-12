#ifndef ScreenManager_hpp
#define ScreenManager_hpp

#include "Window.hpp"
#include "Singleton.hpp"
#include "InputListener.hpp"
#include "ResourceManager.hpp"

namespace warp {
    class WindowManager : public ResourceManager<Window>, public Singleton<WindowManager>, InputListener
    {
    public:
        std::shared_ptr<Window> getActive();
        std::vector<std::shared_ptr<Window>> getAll();
        
        Window::ID create(std::shared_ptr<sf::Window> window)
        {
            auto resource = std::make_shared<Window>(window);
            resources.push_back(resource);
            activeID = resources.size() - 1;
            return resource->setID(activeID);
        }
        
    private:
        std::size_t activeID = 0;
    };
}

#endif /* ScreenManager_hpp */
