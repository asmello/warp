#ifndef GameLoop_hpp
#define GameLoop_hpp

#include "InputListener.hpp"

#include <functional>

namespace warp {
    class GameLoop : public InputListener {
    private:
        bool running;
        std::function<void(void)> body;
        
    public:
        GameLoop(std::function<void(void)> body);
        void run();
        void onClosed();
        void onKeyDown(Input::Key type);
    };
}

#endif /* GameLoop_hpp */
