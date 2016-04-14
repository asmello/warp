#include "Camera.hpp"

#include "Shader.hpp"
#include "ShaderManager.hpp"
#include "GameObject.hpp"
#include "GameObjectManager.hpp"
#include "Transform.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "util.hpp"

using namespace warp;

Camera::Camera() : Component(GameObjectManager::getInstance()->create()),
fieldOfView(45.0f), aspectRatio(1.0f), nearField(0.1f), farField(100.0f),
viewChanged(true), projectionChanged(false)
{
    proj = glm::perspective(fieldOfView, aspectRatio, nearField, farField);
}

void Camera::update()
{
    if (projectionChanged)
    {
        proj = glm::perspective(fieldOfView, aspectRatio, nearField, farField);
        projectionChanged = false;
    }
}

void Camera::bind()
{
    update();
    if (std::shared_ptr<Shader> activeShader = ShaderManager::getInstance()->getActive()) {
        glm::mat4 viewProj = proj * glm::inverse(getGameObject()->getTransform()->getTransformation());
        glUniformMatrix4fv(activeShader->getUniformLocation("u_ViewProj"), 1, GL_FALSE, glm::value_ptr(viewProj));
    }
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