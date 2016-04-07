#include "TextureManager.hpp"

using namespace warp;

void TextureManager::setActive(Texture::ID id)
{
    if (activeID == id) return;
    textures.at(static_cast<long>(id))->bind();
    activeID = id;
}

std::shared_ptr<Texture> TextureManager::get(Texture::ID id)
{
    return textures.at(static_cast<long>(id));
}

Texture::ID TextureManager::add(std::shared_ptr<Texture> shader)
{
    textures.push_back(shader);
    return Texture::ID(textures.size()-1);
}

Texture::ID TextureManager::createFromFile(const std::string& textureFile)
{
    auto texture = std::make_shared<Texture>(GL_TEXTURE_2D);
    texture->loadFromFile(textureFile);
    textures.push_back(texture);
    return Texture::ID(textures.size()-1);
}