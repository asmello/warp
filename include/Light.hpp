#ifndef Light_hpp
#define Light_hpp

#include "Component.hpp"

#include <glm/glm.hpp>

#include <GL/glew.h>

namespace warp
{
    class Light : public Component
    {
    public:
        static const GLuint MAX_LIGHTS = 8;
        GLubyte *getData() const;
        
    private:
        glm::vec4 color, vector, attenuation;
    };
}

#endif /* Light_hpp */
