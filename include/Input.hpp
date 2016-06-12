#ifndef InputHandler_hpp
#define InputHandler_hpp

#include <SFML/Window.hpp>
#include <glm/glm.hpp>

#include <memory>

#include "Singleton.hpp"

namespace warp
{
    class InputListener;
    
    class Input : public Singleton<Input>
    {
    public:
        
        using Key = sf::Keyboard::Key;
        
        static void addListener(std::shared_ptr<InputListener> listener);
        static void flush();
        
        static glm::vec2 getMousePos();
        static void setMousePos(glm::vec2 pos);
        static bool isKeyPressed(Key key);
        
    private:
        std::vector<std::shared_ptr<InputListener>> listeners;
        void notifyMouseScrolled(float delta);
        void notifyKeyDown(Key type);
        void notifyResized(int width, int height);
        void notifyClosed();
    };
}

#include "InputListener.hpp"

#endif /* InputHandler_hpp */
