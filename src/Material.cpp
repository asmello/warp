#include "Material.hpp"

using namespace warp;

Material::Material(TextureID texture, ShaderID shader)
: textureID(texture), shaderID(shader)
{
    
}

void Material::bind()
{
    ShaderManager::getInstance()->setActive(shaderID);
    TextureManager::getInstance()->setActive(textureID);
}