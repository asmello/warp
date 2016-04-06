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
        using ID = int;
        
        void setActive(ID id);
        std::shared_ptr<Texture> get(ID id);
        ID add(std::shared_ptr<Texture> texture);
        ID createFromFile(const std::string& textureFile);
        
    private:
        std::vector<std::shared_ptr<Texture>> textures;
        ID activeID;
    };
}

#endif /* TextureManager_hpp */
