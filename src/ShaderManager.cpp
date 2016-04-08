#include "ShaderManager.hpp"
#include "Shader.hpp"

using namespace warp;

void ShaderManager::setActive(Shader::ID id)
{
    if (activeID == id) return;
    resources.at(static_cast<size_t>(id))->bind();
    activeID = id;
}

std::shared_ptr<Shader> ShaderManager::getActive()
{
    return resources.at(static_cast<size_t>(activeID));
}

Shader::ID ShaderManager::createFromFile(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
{
    auto shader = std::make_shared<Shader>();
    shader->loadFromFile(vertexShaderFile, fragmentShaderFile);
    resources.push_back(shader);
    return (shader->id = Shader::ID(resources.size()-1));
}
