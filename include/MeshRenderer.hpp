#ifndef MeshRenderer_hpp
#define MeshRenderer_hpp

#include "Renderer.hpp"
#include "GameObject.hpp"
#include "Material.hpp"
#include "MeshFilter.hpp"

#include <memory>

namespace warp
{
    class MeshRenderer : public Renderer
    {
    private:
        std::shared_ptr<Mesh> mesh;
        
    public:
        MeshRenderer(const std::shared_ptr<GameObject> object,
                     const std::shared_ptr<Material> material,
                     const std::shared_ptr<MeshFilter> mesh);
        MeshRenderer(const std::shared_ptr<Material> material,
                     const std::shared_ptr<MeshFilter> mesh);
        void init();
        void render();
    };
}

#endif /* GameObject_hpp */
