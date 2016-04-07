#ifndef TextureManager_hpp
#define TextureManager_hpp

#include "Identifier.hpp"
#include "Singleton.hpp"
#include "Texture.hpp"

#include <vector>
#include <memory>
#include <string>

namespace warp
{
    struct texture_tag{}; // Magic strong typedefness
    typedef Identifier<texture_tag, int, -1> TextureID;
    
    class TextureManager : public Singleton<TextureManager>
    {
    public:
        void setActive(TextureID id);
        std::shared_ptr<Texture> get(TextureID id);
        TextureID add(std::shared_ptr<Texture> texture);
        TextureID createFromFile(const std::string& textureFile);
        
    private:
        std::vector<std::shared_ptr<Texture>> textures;
        TextureID activeID;
    };
}

#endif /* TextureManager_hpp */
