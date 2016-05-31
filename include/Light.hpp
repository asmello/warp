#ifndef Light_hpp
#define Light_hpp

#include "Component.hpp"

#include <glm/glm.hpp>

namespace warp
{
    class Light : public Component
    {
    
    public:
        
    private:
        glm::vec4 color, vector, decay;
    };
}

#endif /* Light_hpp */
