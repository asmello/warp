#include "TextureManager.hpp"
#include "Texture.hpp"

using namespace warp;

void TextureManager::setActive(Texture::ID id)
{
    if (activeID == id) return;
    resources.at(static_cast<size_t>(id))->bind();
    activeID = id;
}

Texture::ID TextureManager::createFromFile(const std::string& textureFile)
{
    auto texture = std::make_shared<Texture>(GL_TEXTURE_2D);
    texture->loadFromFile(textureFile);
    resources.push_back(texture);
    return (texture->id = Texture::ID(resources.size()-1));
}
