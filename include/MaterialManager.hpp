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
        void setActive(Material::ID id);
        std::shared_ptr<Material> get(Material::ID id);
        Material::ID add(std::shared_ptr<Material> material);
        Material::ID create(Texture::ID texture, Shader::ID shader);
        
    private:
        std::vector<std::shared_ptr<Material>> materials;
        Material::ID activeID;
    };
}

#endif /* MaterialManager_hpp */
