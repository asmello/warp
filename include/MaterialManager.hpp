#ifndef MaterialManager_hpp
#define MaterialManager_hpp

#include "Singleton.hpp"
#include "ResourceManager.hpp"
#include "Material.hpp"

namespace warp
{
    class MaterialManager : public ResourceManager<Material>, public Singleton<MaterialManager>
    {
    public:
        void setActive(Material::ID id);

    private:
        Material::ID activeID;
    };
}

#endif /* MaterialManager_hpp */
