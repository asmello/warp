#ifndef Camera_hpp
#define Camera_hpp

#include <glm/glm.hpp>

class Camera {
private:
    glm::mat4 view, proj;
public:
    void lookAt(glm::vec3 point);
    void setPosition(glm::vec3 position);
    void setAspectRatio(float ratio);
    void setOrientation(glm::vec3 upVector);
    void setNear(float distance);
    void setFar(float distance);
    void setFOV(float angle);
};

#endif /* Camera_hpp */
