#include "DirectionalLight.hpp"

#include "Shader.hpp"
#include "ShaderManager.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace warp;

void DirectionalLight::bind()
{
    if (std::shared_ptr<Shader> activeShader = ShaderManager::getInstance()->getActive()) {
        glUniform3f(activeShader->getUniformLocation("u_sun.color"), color.x, color.y, color.z);
        glUniform3f(activeShader->getUniformLocation("u_sun.direction"), direction.x, direction.y, direction.z);
        glUniform1f(activeShader->getUniformLocation("u_sun.intensity"), intensity);
    }
}

void DirectionalLight::setColor(glm::vec3 color_)
{
    color = color_;
}

void DirectionalLight::setDirection(glm::vec3 direction_)
{
    direction = direction_;
}

void DirectionalLight::setIntensity(float intensity_)
{
    intensity = intensity_;
}