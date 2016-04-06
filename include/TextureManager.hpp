#ifndef TextureManager_hpp
#define TextureManager_hpp

#include "Singleton.hpp"
#include "Texture.hpp"

#include <string>
#include <memory>

namespace warp
{
    class TextureManager : public Singleton<TextureManager>
    {
    public:
        using ID = int;
        
        std::weak_ptr<Texture> get(ID id);
        ID add(std::shared_ptr<Texture> shader);
        ID createFromFile(const std::string& textureFile);
    };
}

#endif /* TextureManager_hpp */
