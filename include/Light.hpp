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
        enum Type {
            Point,
            Directional
        };
        Light(Type type);
        
        static const GLuint MAX_LIGHTS = 8;
        GLubyte *getData() const;
        void setColor(glm::vec3 rgb);
        void setType(Type type);
        void setVector(glm::vec3 vector);
        void setAttenuation(glm::vec4 factors);
        
    private:
        glm::vec4 color, vector, attenuation;
    };
}

#endif /* Light_hpp */
