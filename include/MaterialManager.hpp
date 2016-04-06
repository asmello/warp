#ifndef MaterialManager_hpp
#define MaterialManager_hpp

#include "Singleton.hpp"
#include "Material.hpp"

#include <memory>

namespace warp
{
    class MaterialManager : public Singleton<MaterialManager>
    {
    public:
        using ID = int;
        
        std::weak_ptr<Material> get(ID id);
        ID add(std::shared_ptr<Material> material);
        ID create(TextureManager::ID texture, ShaderManager::ID shader);
    };
}

#endif /* MaterialManager_hpp */
