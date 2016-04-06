#ifndef MaterialManager_hpp
#define MaterialManager_hpp

#include "Singleton.hpp"
#include "Material.hpp"

#include <vector>
#include <memory>

namespace warp
{
    class MaterialManager : public Singleton<MaterialManager>
    {
    public:
        using ID = int;
        
        void setActive(ID id);
        std::shared_ptr<Material> get(ID id);
        ID add(std::shared_ptr<Material> material);
        ID create(TextureManager::ID texture, ShaderManager::ID shader);
        
    private:
        std::vector<std::shared_ptr<Material>> materials;
        ID activeID;
    };
}

#endif /* MaterialManager_hpp */
