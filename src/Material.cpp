#include "Material.hpp"
#include "MaterialManager.hpp"

#include "ShaderManager.hpp"
#include "TextureManager.hpp"

using namespace warp;

template<> ResourceManager<Material> * Object<Material>::manager = MaterialManager::getInstance();

Material::Material(Texture::ID texture, Shader::ID shader)
: shaderID(shader), speed(0.0f)
{
    textureIDs.push_back(texture);
}

Material::Material(std::vector<Texture::ID> textures, Shader::ID shader)
: shaderID(shader), textureIDs(textures), speed(0.0f)
{
    
}

Material::Material(std::initializer_list<Texture::ID> textures, Shader::ID shader)
: shaderID(shader), textureIDs(textures), speed(0.0f)
{
    
}

void Material::bind()
{
    ShaderManager::getInstance()->setActive(shaderID);
    for (size_t i = 0; i < textureIDs.size(); ++i)
    {
        TextureManager::getInstance()->setActive(textureIDs[i], i);
        // Send speed to shader
        if (std::shared_ptr<Shader> activeShader = ShaderManager::getInstance()->getActive()) {
            glUniform1f(activeShader->getUniformLocation("u_speed"), speed);
        }
    }
}

void Material::setSpeed(float speed_)
{
    speed = speed_;
}