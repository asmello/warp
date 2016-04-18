#include "TextureManager.hpp"
#include "Texture.hpp"

#include "Shader.hpp"
#include "ShaderManager.hpp"

using namespace warp;

void TextureManager::setActive(Texture::ID id, int slot)
{
//    if (activeID == id) return;
    
    std::shared_ptr<Texture> texture = resources.at(static_cast<size_t>(id));
    
    if (std::shared_ptr<Shader> activeShader = ShaderManager::getInstance()->getActive()) {
        glUniform1i(activeShader->getUniformLocation("u_sampler" + std::to_string(slot)), slot);
    }
    
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(texture->target, texture->txo);
    
    activeID = id;
}

// TODO: handle case when file does not exist
Texture::ID TextureManager::createFromFile(const std::string& textureFile)
{
    auto texture = std::make_shared<Texture>(GL_TEXTURE_2D);
    texture->loadFromFile(textureFile);
    resources.push_back(texture);
    return texture->setID(resources.size()-1);
}
