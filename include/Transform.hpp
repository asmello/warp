#ifndef Transform_hpp
#define Transform_hpp

#include "Component.hpp"

#include <vector>
#include <memory>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace warp
{
    class Transform : public Component
    {
    private:
        glm::vec3 position, scaleFactors;
        glm::quat rotation;
        std::vector<std::shared_ptr<Transform>> children;
        std::shared_ptr<Transform> parent;
        
    public:
        Transform();
        Transform(Object<GameObject>::ID gameObject);
        
        void bind();
        void scale(float xfactor, float yfactor, float zfactor);
        void scale(glm::vec3 factors);
        void scale(float factor);
        void rotate(float angle, glm::vec3 axis);
        void rotate(float angle, float x, float y, float z);
        void rotateX(float radians);
        void rotateY(float radians);
        void rotateZ(float radians);
        void translate(float x, float y, float z);
        void translate(glm::vec3 delta);
        void lookAt(glm::vec3 point, glm::vec3 up);
        void setPosition(glm::vec3 position);
        void setRotation(glm::quat q);
        glm::mat4 getTransformation();
    };
}

#endif /* Transform_hpp */
