#include "LightManager.hpp"
#include "Light.hpp"

using namespace warp;

void LightManager::setActive(Light::ID lightID)
{
    resources.at(static_cast<size_t>(lightID))->bind();
}