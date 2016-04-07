#ifndef MaterialManager_hpp
#define MaterialManager_hpp

#include "Singleton.hpp"
#include "Material.hpp"
#include "Identifier.hpp"

#include <vector>
#include <memory>

namespace warp
{
    struct material_tag{}; // Magic strong typedefness
    typedef Identifier<material_tag, int, -1> MaterialID;
    
    class MaterialManager : public Singleton<MaterialManager>
    {
    public:
        void setActive(MaterialID id);
        std::shared_ptr<Material> get(MaterialID id);
        MaterialID add(std::shared_ptr<Material> material);
        MaterialID create(TextureID texture, ShaderID shader);
        
    private:
        std::vector<std::shared_ptr<Material>> materials;
        MaterialID activeID;
    };
}

#endif /* MaterialManager_hpp */
