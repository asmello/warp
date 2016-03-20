#include "Transform.hpp"
using namespace warp;

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

Transform::Transform() : position(glm::vec3(0, 0, 0)), scaleFactors(glm::vec3(1, 1, 1)), initialized(false)
{
    
}

void Transform::init(const std::shared_ptr<const warp::Shader> shader)
{
    if (initialized) return;
    uniTrans = shader->getUniformLocation("u_Model");
    initialized = true;
}

void Transform::bind()
{
    // Update the transformation matrix
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(getTransformation()));
}

void Transform::scale(float xfactor, float yfactor, float zfactor)
{
    scaleFactors *= glm::vec3(xfactor, yfactor, zfactor);
}

void Transform::scale(float factor)
{
    scaleFactors *= glm::vec3(factor, factor, factor);
}

void Transform::scale(glm::vec3 factors)
{
    scaleFactors *= factors;
}

void Transform::rotate(float angle, glm::vec3 axis)
{
    rotation = glm::rotate(rotation, angle, axis);
}

void Transform::rotate(float angle, float x, float y, float z)
{
    rotation = glm::rotate(rotation, angle, glm::vec3(x, y, z));
}

void Transform::rotateX(float angle)
{
    rotation = glm::rotate(rotation, angle, glm::vec3(1, 0, 0));
}

void Transform::rotateY(float angle)
{
    rotation = glm::rotate(rotation, angle, glm::vec3(0, 1, 0));
}

void Transform::rotateZ(float angle)
{
    rotation = glm::rotate(rotation, angle, glm::vec3(0, 0, 1));
}

void Transform::translate(float x, float y, float z)
{
    position += glm::vec3(x, y, z);
}

void Transform::translate(glm::vec3 delta)
{
    position += delta;
}

glm::mat4 Transform::getTransformation()
{
    glm::mat4 trans;
    trans = glm::translate(trans, position);
    trans *= rotation;
    trans = glm::scale(trans, scaleFactors);
    return trans;
}
