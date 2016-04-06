#include "Material.hpp"

using namespace warp;

Material::Material(TextureManager::ID texture, ShaderManager::ID shader)
: textureID(texture), shaderID(shader)
{
    
}

void Material::bind()
{
    ShaderManager::getInstance()->setActive(shaderID);
    TextureManager::getInstance()->setActive(textureID);
}