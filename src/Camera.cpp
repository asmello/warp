#include "Camera.hpp"
using namespace warp;

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() :
position(glm::vec3(0.0f, 0.0f, 5.0f)),
pointOfInterest(glm::vec3(0.0f, 0.0f, 0.0f)),
upVector(glm::vec3(0.0f, 1.0f, 0.0f)),
fieldOfView(45.0f), aspectRatio(1.0f), nearField(1.0f), farField(10.0f),
viewChanged(true), projectionChanged(true), initialized(false)
{
    
}

void Camera::init(const std::shared_ptr<const Shader> shader)
{
    if (initialized) return;
    uniViewProj = shader->getUniformLocation("u_ViewProj");
    update();
    initialized = true;
}

void Camera::update()
{
    if (viewChanged) buildView();
    if (projectionChanged) buildProjection();
    if (viewChanged || projectionChanged) updateShader();
}

void Camera::buildView()
{
    view = glm::lookAt(position, pointOfInterest, upVector);
    viewChanged = false;
}

void Camera::buildProjection()
{
    proj = glm::perspective(fieldOfView, aspectRatio, nearField, farField);
    projectionChanged = false;
}

void Camera::updateShader()
{
    glm::mat4 viewProj = proj * view;
    glUniformMatrix4fv(uniViewProj, 1, GL_FALSE, glm::value_ptr(viewProj));
}

void Camera::setPosition(glm::vec3 position)
{
    this->position = position;
    viewChanged = true;
}

void Camera::lookAt(glm::vec3 point)
{
    pointOfInterest = point;
    viewChanged = true;
}

void Camera::setOrientation(glm::vec3 upVector)
{
    this->upVector = upVector;
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