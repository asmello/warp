#include "TextureManager.hpp"

using namespace warp;

void TextureManager::setActive(TextureManager::ID id)
{
    if (activeID == id) return;
    textures.at(id)->bind();
    activeID = id;
}

std::shared_ptr<Texture> TextureManager::get(TextureManager::ID id)
{
    return textures.at(id);
}

TextureManager::ID TextureManager::add(std::shared_ptr<Texture> shader)
{
    textures.push_back(shader);
    return textures.size()-1;
}

TextureManager::ID TextureManager::createFromFile(const std::string& textureFile)
{
    auto texture = std::make_shared<Texture>(GL_TEXTURE_2D);
    texture->loadFromFile(textureFile);
    textures.push_back(texture);
    return textures.size()-1;
}