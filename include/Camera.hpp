#ifndef Camera_hpp
#define Camera_hpp

#include "Object.hpp"
#include "Component.hpp"

#include <glm/glm.hpp>

#include <memory>

namespace warp
{
    class Camera : public ComponentImplementation<Camera>
    {
    public:
        // These constructors should not be used directly
        Camera();
        
        void lookAt(glm::vec3 point, glm::vec3 up);
        void reshape(int width, int height);
        void setPosition(glm::vec3 position);
        void setNear(float distance);
        void setFar(float distance);
        void setFOV(float angle);
        bool update();
        
        glm::mat4 getProjection() const;
        glm::mat4 getViewProjection() const;
        glm::mat4 getView() const;
        
    private:
        glm::mat4 proj;
        float fieldOfView, aspectRatio, nearField, farField;
        bool viewChanged, projectionChanged;
    };
}

#endif /* Camera_hpp */
