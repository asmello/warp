#include "MaterialManager.hpp"

using namespace warp;

void MaterialManager::setActive(MaterialManager::ID id)
{
    if (activeID == id) return;
    materials.at(id)->bind();
    activeID = id;
}

MaterialManager::ID MaterialManager::add(std::shared_ptr<Material> material)
{
    materials.push_back(material);
    return materials.size()-1;
}

MaterialManager::ID MaterialManager::create(TextureManager::ID textureID, ShaderManager::ID shaderID)
{
    materials.push_back(std::make_shared<Material>(textureID, shaderID));
    return materials.size()-1;
}

std::shared_ptr<Material> MaterialManager::get(ID id)
{
    return materials.at(id);
}