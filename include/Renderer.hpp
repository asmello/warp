#ifndef Renderer_hpp
#define Renderer_hpp

#include "Object.hpp"
#include "Component.hpp"

#include <vector>
#include <memory>

namespace warp
{
    class Renderer : public Component
    {
    public:
        Renderer();
        void activate();
        virtual void render() = 0;
        
    protected:
        bool active;
    };
}

#endif /* Renderer_hpp */
