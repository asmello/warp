#ifndef TextureManager_hpp
#define TextureManager_hpp

#include "Singleton.hpp"
#include "ResourceManager.hpp"

#include <string>

namespace warp
{
    class Texture;

    class TextureManager : public ResourceManager<Texture>, public Singleton<TextureManager>
    {
    public:
        void setActive(Object<Texture>::ID id, int slot);
        Object<Texture>::ID createFromFile(const std::string& textureFile);
        Object<Texture>::ID createCubemapFromFile(const std::string& cubemapFile);
        Object<Texture>::ID createCubemapFromFiles(const std::vector<std::string>& cubemapFiles);

    private:
        Object<Texture>::ID activeID;
    };
}

#endif /* TextureManager_hpp */
