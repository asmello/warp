#include "ShaderManager.hpp"

using namespace warp;

void ShaderManager::setActive(ShaderID id)
{
    if (activeID == id) return;
    shaders.at(static_cast<int>(id))->bind();
    activeID = id;
}

std::shared_ptr<Shader> ShaderManager::getActive()
{
    return shaders.at(static_cast<int>(activeID));
}

std::shared_ptr<Shader> ShaderManager::get(ShaderID id)
{
    return shaders.at(static_cast<int>(id));
}

ShaderID ShaderManager::add(std::shared_ptr<Shader> shader)
{
    shaders.push_back(shader);
    return ShaderID(shaders.size()-1);
}

ShaderID ShaderManager::createFromFile(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
{
    auto shader = std::make_shared<Shader>();
    shader->loadFromFile(vertexShaderFile, fragmentShaderFile);
    shaders.push_back(shader);
    return ShaderID(shaders.size()-1);
}