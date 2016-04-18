#include "Material.hpp"

#include "ShaderManager.hpp"
#include "TextureManager.hpp"

using namespace warp;

Material::Material(Texture::ID texture, Shader::ID shader)
: shaderID(shader)
{
    textureIDs.push_back(texture);
}

Material::Material(std::vector<Texture::ID> textures, Shader::ID shader)
: shaderID(shader), textureIDs(textures)
{
    
}

Material::Material(std::initializer_list<Texture::ID> textures, Shader::ID shader)
: shaderID(shader), textureIDs(textures)
{
    
}

void Material::bind()
{
    ShaderManager::getInstance()->setActive(shaderID);
    for (size_t i = 0; i < textureIDs.size(); ++i)
    {
        TextureManager::getInstance()->setActive(textureIDs[i], i);
    }
}