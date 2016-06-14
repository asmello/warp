#include "Transform.hpp"

#include "Shader.hpp"
#include "ShaderManager.hpp"
#include "Scene.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "util.hpp"

using namespace warp;

Transform::Transform() :
position(glm::vec3(0, 0, 0)), scaleFactors(glm::vec3(1, 1, 1)), parent(nullptr), valid(false)
{
    
}

void Transform::setTransformation(const aiMatrix4x4& aiTransform)
{
    aiVector3D scaling_, position_;
    aiQuaternion rotation_;
    Decompose<float>(aiTransform, scaling_, rotation_, position_);
    position = glm::vec3(position_.x, position_.y, position_.z);
    scaleFactors = glm::vec3(scaling_.x, scaling_.y, scaling_.z);
    rotation = glm::quat(rotation_.w, rotation_.x, rotation_.y, rotation_.z);
}

void Transform::bind()
{
    if (std::shared_ptr<Shader> activeShader = ShaderManager::getInstance()->getActive()) {
        glUniformMatrix4fv(activeShader->getUniformLocation("u_Model"), 1, GL_FALSE, glm::value_ptr(getTransformation()));
    }
}

void Transform::scale(float xfactor, float yfactor, float zfactor)
{
    scaleFactors *= glm::vec3(xfactor, yfactor, zfactor);
    invalidate();
}

void Transform::scale(float factor)
{
    scaleFactors *= glm::vec3(factor, factor, factor);
    invalidate();
}

void Transform::scale(glm::vec3 factors)
{
    scaleFactors *= factors;
    invalidate();
}

void Transform::rotate(float angle, glm::vec3 axis)
{
    rotation = glm::rotate(rotation, angle, axis);
    invalidate();
}

void Transform::rotate(float angle, float x, float y, float z)
{
    rotate(angle, glm::vec3(x, y, z));
}

void Transform::rotateX(float angle)
{
	rotate(angle, glm::vec3(1, 0, 0));
}

void Transform::rotateY(float angle)
{
	rotate(angle, glm::vec3(0, 1, 0));
}

void Transform::rotateZ(float angle)
{
	rotate(angle, glm::vec3(0, 0, 1));
}

void Transform::translate(float x, float y, float z)
{
    position += glm::vec3(x, y, z);
    invalidate();
}

void Transform::translate(glm::vec3 delta)
{
    position += delta;
    invalidate();
}

void Transform::setPosition(glm::vec3 position_)
{
    position = position_;
    invalidate();
}

void Transform::setRotation(glm::quat q)
{
    rotation = q;
    invalidate();
}

void Transform::lookAt(glm::vec3 point, glm::vec3 up)
{
    rotation = glm::toQuat(glm::lookAt(position, point, up));
    invalidate();
}

void Transform::setParent(std::shared_ptr<Transform> parent_)
{
	// TODO [remove from previous parent's children]
    parent = parent_;
    parent->children.push_back(shared_from_this());
    if (!parent->valid)
    {
        invalidate();
    }
}

void Transform::invalidate()
{
    valid = false;
    for (std::weak_ptr<Transform>& childRef : children)
    {
        std::shared_ptr<Transform> child = childRef.lock();
        child->invalidate();
    }
}

void Transform::revalidate()
{
    glm::mat4 trans;
    trans = glm::translate(trans, position);
    trans *= glm::toMat4(rotation);
    trans = glm::scale(trans, scaleFactors);
    if (parent != nullptr)
    {
        trans = parent->getTransformation() * trans;
    }
    cachedTransformation = trans;
    valid = true;
}

glm::mat4 Transform::getTransformation()
{
    if (!valid)
    {
        revalidate();
    }
    return cachedTransformation;
}

std::shared_ptr<Transform> Transform::getParent()
{
    return parent;
}

std::shared_ptr<Transform> Transform::getRoot()
{
    if (isRoot()) return shared_from_this();
    std::shared_ptr<Transform> root = parent;
    while (root->parent)
    {
        root = root->parent;
    }
    return root;
}

bool Transform::isRoot() const
{
    return !parent;
}

std::shared_ptr<Transform> Transform::newChild()
{
    auto child = std::make_shared<Transform>();
    child->setParent(shared_from_this());
    return child;
}

std::vector<std::weak_ptr<Transform>> Transform::getChildren()
{
    return children;
}

glm::vec3 Transform::getGlobalPosition() const
{
    if (isRoot()) return position;
    return glm::vec3 (parent->getTransformation() * glm::vec4 (position, 1.0));
}

glm::vec3 Transform::getPosition() const
{
    return position;
}


