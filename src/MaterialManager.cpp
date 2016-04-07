#include "MaterialManager.hpp"

using namespace warp;

void MaterialManager::setActive(MaterialID id)
{
    if (activeID == id) return;
    materials.at(static_cast<int>(id))->bind();
    activeID = id;
}

MaterialID MaterialManager::add(std::shared_ptr<Material> material)
{
    materials.push_back(material);
    return MaterialID(materials.size()-1);
}

MaterialID MaterialManager::create(TextureID textureID, ShaderID shaderID)
{
    materials.push_back(std::make_shared<Material>(textureID, shaderID));
    return MaterialID(materials.size()-1);
}

std::shared_ptr<Material> MaterialManager::get(MaterialID id)
{
    return materials.at(static_cast<int>(id));
}