#ifndef TextureManager_hpp
#define TextureManager_hpp

#include "ResourceManager.hpp"

#include <string>

namespace warp
{
    class Texture;

    class TextureManager : public ResourceManager<Texture>
    {
    public:
        void setActive(Object<Texture>::ID id);
        Object<Texture>::ID createFromFile(const std::string& textureFile);

    private:
        Object<Texture>::ID activeID;
    };
}

#endif /* TextureManager_hpp */
