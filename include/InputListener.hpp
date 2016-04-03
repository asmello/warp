#ifndef InputListener_hpp
#define InputListener_hpp

#include "Input.hpp"

namespace warp
{
    class InputListener
    {
    public:
        virtual void onClosed() {}
        virtual void onKeyDown(Input::Key type) {}
        virtual void onKeyUp(Input::Key type) {}
        virtual void onMouseScrolled(float delta) {}
        virtual void onMouseClicked() {}
        virtual void onResized(int width, int height) {}
    };
}

#endif /* InputListener_hpp */
