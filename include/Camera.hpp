#ifndef Camera_hpp
#define Camera_hpp

#include "Shader.hpp"
#include "GameObject.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <memory>

namespace warp
{
    class Camera : public Component
    {
    private:
        glm::mat4 proj;
        float fieldOfView, aspectRatio, nearField, farField;
        void updateShader();
        void buildProjection();
        bool viewChanged, projectionChanged, initialized;
        
    public:
        Camera();
        void init();
        void lookAt(glm::vec3 point);
        void reshape(int width, int height);
        void setPosition(glm::vec3 position);
        void setOrientation(glm::vec3 upVector);
        void setNear(float distance);
        void setFar(float distance);
        void setFOV(float angle);
        void update();
        void render();
    };
}

#endif /* Camera_hpp */
