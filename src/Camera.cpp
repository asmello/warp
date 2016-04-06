#include "Camera.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace warp;

Camera::Camera() :
fieldOfView(45.0f), aspectRatio(1.0f), nearField(1.0f), farField(10.0f),
viewChanged(true), projectionChanged(true), initialized(false)
{
    
}

void Camera::init(std::shared_ptr<Shader> shader)
{
    if (initialized) return;
    uniViewProj = shader->getUniformLocation("u_ViewProj");
    update();
    initialized = true;
}

void Camera::update()
{
    if (viewChanged || projectionChanged) {
        if (viewChanged) viewChanged = false;
        if (projectionChanged) buildProjection();
        updateShader();
    }
}

void Camera::buildProjection()
{
    proj = glm::perspective(fieldOfView, aspectRatio, nearField, farField);
    projectionChanged = false;
}

void Camera::updateShader()
{
    glm::mat4 viewProj = proj * getGameObject()->getTransform()->getTransformation();
    glUniformMatrix4fv(uniViewProj, 1, GL_FALSE, glm::value_ptr(viewProj));
}

void Camera::setPosition(glm::vec3 position)
{
    getGameObject()->getTransform()->setPosition(position);
    viewChanged = true;
}

void Camera::lookAt(glm::vec3 point)
{
    getGameObject()->getTransform()->lookAt(point);
    viewChanged = true;
}

void Camera::setOrientation(glm::vec3 upVector)
{
    getGameObject()->getTransform()->setOrientation(upVector);
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