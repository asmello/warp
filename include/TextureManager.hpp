#ifndef TextureManager_hpp
#define TextureManager_hpp

#include "Singleton.hpp"
#include "Texture.hpp"

#include <vector>
#include <memory>
#include <string>

namespace warp
{
    class TextureManager : public Singleton<TextureManager>
    {
    public:
        void setActive(Texture::ID id);
        std::shared_ptr<Texture> get(Texture::ID id);
        Texture::ID add(std::shared_ptr<Texture> texture);
        Texture::ID createFromFile(const std::string& textureFile);
        
    private:
        std::vector<std::shared_ptr<Texture>> textures;
        Texture::ID activeID;
    };
}

#endif /* TextureManager_hpp */
