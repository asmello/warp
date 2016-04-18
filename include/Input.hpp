#ifndef InputHandler_hpp
#define InputHandler_hpp

#include <SFML/Window.hpp>

#include <memory>

namespace warp
{
    class InputListener;
    
    class Input {
    public:
        
        using Key = sf::Keyboard::Key;
        
        Input(std::shared_ptr<sf::Window> window);
        void addListener(std::shared_ptr<InputListener> listener);
        void flush();
        
    private:
        std::shared_ptr<sf::Window> window;
        std::vector<std::shared_ptr<InputListener>> listeners;
        void notifyMouseScrolled(float delta);
        void notifyKeyDown(Key type);
        void notifyResized(int width, int height);
        void notifyClosed();
    };
}

#include "InputListener.hpp"

#endif /* InputHandler_hpp */
