#include "MaterialManager.hpp"

using namespace warp;

void MaterialManager::setActive(Material::ID id)
{
    if (activeID == id) return;
    materials.at(static_cast<size_t>(id))->bind();
    activeID = id;
}

Material::ID MaterialManager::add(std::shared_ptr<Material> material)
{
    materials.push_back(material);
    return Material::ID(materials.size()-1);
}

Material::ID MaterialManager::create(Texture::ID textureID, Shader::ID shaderID)
{
    materials.push_back(std::make_shared<Material>(textureID, shaderID));
    return Material::ID(materials.size()-1);
}

std::shared_ptr<Material> MaterialManager::get(Material::ID id)
{
    return materials.at(static_cast<size_t>(id));
}