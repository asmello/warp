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
        GLint uniViewProj;
        glm::mat4 view, proj;
        glm::vec3 position, pointOfInterest, upVector;
        float fieldOfView, aspectRatio, nearField, farField;
        void updateShader();
        void buildProjection();
        void buildView();
        bool viewChanged, projectionChanged, initialized;
        
    public:
        Camera();
        void init(std::shared_ptr<Shader> shader);
        void lookAt(glm::vec3 point);
        void reshape(int width, int height);
        void setPosition(glm::vec3 position);
        void setOrientation(glm::vec3 upVector);
        void setNear(float distance);
        void setFar(float distance);
        void setFOV(float angle);
        void update();
    };
}

#endif /* Camera_hpp */
