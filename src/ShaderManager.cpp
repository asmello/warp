#include "ShaderManager.hpp"

using namespace warp;

void ShaderManager::setActive(Shader::ID id)
{
    if (activeID == id) return;
    shaders.at(static_cast<long>(id))->bind();
    activeID = id;
}

std::shared_ptr<Shader> ShaderManager::getActive()
{
    return shaders.at(static_cast<long>(activeID));
}

std::shared_ptr<Shader> ShaderManager::get(Shader::ID id)
{
    return shaders.at(static_cast<long>(id));
}

Shader::ID ShaderManager::add(std::shared_ptr<Shader> shader)
{
    shaders.push_back(shader);
    return Shader::ID(shaders.size()-1);
}

Shader::ID ShaderManager::createFromFile(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
{
    auto shader = std::make_shared<Shader>();
    shader->loadFromFile(vertexShaderFile, fragmentShaderFile);
    shaders.push_back(shader);
    return Shader::ID(shaders.size()-1);
}