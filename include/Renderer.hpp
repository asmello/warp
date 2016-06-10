#ifndef Renderer_hpp
#define Renderer_hpp

#include "Object.hpp"
#include "Component.hpp"

#include <vector>
#include <memory>
#include <typeinfo>

namespace warp
{
    class Renderer : public ComponentImplementation<Renderer>
    {
    public:
        Renderer();
        virtual void activate();
        virtual void render() = 0;
        
    protected:
        bool active;
    };
}

#endif /* Renderer_hpp */
