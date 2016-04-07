#include "TextureManager.hpp"

using namespace warp;

void TextureManager::setActive(TextureID id)
{
    if (activeID == id) return;
    textures.at(static_cast<int>(id))->bind();
    activeID = id;
}

std::shared_ptr<Texture> TextureManager::get(TextureID id)
{
    return textures.at(static_cast<int>(id));
}

TextureID TextureManager::add(std::shared_ptr<Texture> shader)
{
    textures.push_back(shader);
    return TextureID(textures.size()-1);
}

TextureID TextureManager::createFromFile(const std::string& textureFile)
{
    auto texture = std::make_shared<Texture>(GL_TEXTURE_2D);
    texture->loadFromFile(textureFile);
    textures.push_back(texture);
    return TextureID(textures.size()-1);
}