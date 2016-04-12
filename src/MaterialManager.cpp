#include "MaterialManager.hpp"
#include "Material.hpp"

using namespace warp;

void MaterialManager::setActive(Material::ID id)
{
//    if (activeID == id) return;
    resources.at(static_cast<size_t>(id))->bind();
    activeID = id;
}
