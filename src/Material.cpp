#include "Material.hpp"

#include "ShaderManager.hpp"
#include "TextureManager.hpp"

using namespace warp;

Material::Material(Texture::ID texture, Shader::ID shader)
: textureID(texture), shaderID(shader)
{
    
}

void Material::bind()
{
    ShaderManager::getInstance()->setActive(shaderID);
    TextureManager::getInstance()->setActive(textureID, 0);
}