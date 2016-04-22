#ifndef Light_hpp
#define Light_hpp

#include "Component.hpp"

#include <glm/glm.hpp>

namespace warp
{
    class Light : public Component, public Object<Light>
    {
        friend class LightManager;
    public:
        virtual void bind() = 0;
    };
}

#endif /* Light_hpp */
