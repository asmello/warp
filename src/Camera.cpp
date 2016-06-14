#include "Camera.hpp"

#include "Shader.hpp"
#include "ShaderManager.hpp"
#include "WindowManager.hpp"
#include "Scene.hpp"
#include "Transform.hpp"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace warp;

Camera::Camera() :
fieldOfView(45.0f), aspectRatio(1.0f), nearField(0.1f), farField(1000.0f),
viewChanged(true), projectionChanged(false)
{
    if (auto window = WindowManager::getInstance()->getActive())
    {
        glm::vec2 size = window->getSize();
        aspectRatio = size.x/size.y;
    }
    proj = glm::perspective(fieldOfView, aspectRatio, nearField, farField);
}

bool Camera::update()
{
    if (projectionChanged)
    {
        proj = glm::perspective(fieldOfView, aspectRatio, nearField, farField);
        projectionChanged = false;
        return true;
    }
    return viewChanged;
}

glm::mat4 Camera::getViewProjection() const
{
    return proj * glm::inverse(getGameObject()->getTransform()->getTransformation());
}

glm::mat4 Camera::getView() const
{
    return glm::inverse(getGameObject()->getTransform()->getTransformation());
}

glm::mat4 Camera::getProjection() const
{
    return proj;
}

void Camera::setPosition(glm::vec3 position)
{
    getGameObject()->getTransform()->setPosition(position);
    viewChanged = true;
}

void Camera::lookAt(glm::vec3 point, glm::vec3 up)
{
    getGameObject()->getTransform()->lookAt(point, up);
    viewChanged = true;
}

void Camera::setFOV(float angle)
{
    fieldOfView = angle;
    projectionChanged = true;
}

void Camera::reshape(int width, int height)
{
    aspectRatio = static_cast<float>(width)/static_cast<float>(height);
    projectionChanged = true;
}

void Camera::setNear(float distance)
{
    nearField = distance;
    projectionChanged = true;
}

void Camera::setFar(float distance)
{
    farField = distance;
    projectionChanged = true;
}

void Camera::rotate(float angle, float x, float y, float z)
{
    getGameObject()->getTransform()->rotate(angle, x, y, z);
    viewChanged = true;
}