#ifndef DirectionalLight_hpp
#define DirectionalLight_hpp

#include "Light.hpp"

namespace warp
{
    class DirectionalLight : public Light
    {
    public:
        
        void bind();
        void setDirection(glm::vec3 direction);
        void setColor(glm::vec3 color);
        void setIntensity(float intensity);
        
    private:
        glm::vec3 direction;
        glm::vec3 color;
        float intensity;
    };
}

#endif /* DirectionalLight_hpp */
