#ifndef MaterialManager_hpp
#define MaterialManager_hpp

#include "Singleton.hpp"
#include "ResourceManager.hpp"

namespace warp
{
    class Material;

    class MaterialManager : public ResourceManager<Material>, public Singleton<MaterialManager>
    {
    public:
        void setActive(Object<Material>::ID id);

    private:
        Object<Material>::ID activeID;
    };
}

#endif /* MaterialManager_hpp */
