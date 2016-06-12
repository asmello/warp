#ifndef Window_hpp
#define Window_hpp

#include <SFML/Window.hpp>
#include <glm/glm.hpp>

#include <memory>
#include <vector>

#include "Object.hpp"

namespace warp {
    class Window : public Object<Window>
    {
        friend class WindowManager;
        friend class Input;
        
    public:
        Window(std::shared_ptr<sf::Window> window);
        
        glm::vec2 getSize() const;
        glm::vec2 getCenter() const;
        void setMouseVisible(bool visible);
        
    private:
        std::shared_ptr<sf::Window> window;
    };
}

#endif /* Window_hpp */
