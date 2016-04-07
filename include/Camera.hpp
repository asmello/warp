#ifndef Camera_hpp
#define Camera_hpp

#include "Object.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <memory>

namespace warp
{
    class Camera : public Component
    {
        friend class CameraManager;
        
    public:
        // These constructors should not be used directly
        Camera();
        
        void lookAt(glm::vec3 point);
        void reshape(int width, int height);
        void setPosition(glm::vec3 position);
        void setOrientation(glm::vec3 upVector);
        void setNear(float distance);
        void setFar(float distance);
        void setFOV(float angle);
        void update();
        void bind();
        
    private:
        glm::mat4 proj;
        float fieldOfView, aspectRatio, nearField, farField;
        bool viewChanged, projectionChanged;
    };
}

#endif /* Camera_hpp */
