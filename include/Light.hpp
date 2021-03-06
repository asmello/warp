#ifndef Light_hpp
#define Light_hpp

#include "Component.hpp"

#include <glm/glm.hpp>

#include <GL/glew.h>

namespace warp
{
    class Light : public ComponentImplementation<Light>
    {
    public:
        enum Type {
            Point,
            Directional
        };
        Light(Type type);
        
        static const GLuint MAX_LIGHTS = 8;
        GLfloat *getData() const;
        void setColor(glm::vec3 rgb);
        void setType(Type type);
        void setVector(glm::vec3 vector);
        void setAttenuation(glm::vec4 factors);
        
    private:
        glm::mat4 data;
    };
}

#endif /* Light_hpp */
