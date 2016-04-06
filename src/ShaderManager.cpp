#include "ShaderManager.hpp"

using namespace warp;

void ShaderManager::setActive(ID id)
{
    if (activeID == id) return;
    shaders.at(id)->bind();
    activeID = id;
}

std::shared_ptr<Shader> ShaderManager::getActive()
{
    return shaders.at(activeID);
}

std::shared_ptr<Shader> ShaderManager::get(ID id)
{
    return shaders.at(id);
}

ShaderManager::ID ShaderManager::add(std::shared_ptr<Shader> shader)
{
    shaders.push_back(shader);
    return shaders.size()-1;
}

ShaderManager::ID ShaderManager::createFromFile(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
{
    auto shader = std::make_shared<Shader>();
    shader->loadFromFile(vertexShaderFile, fragmentShaderFile);
    shaders.push_back(shader);
    return shaders.size()-1;
}