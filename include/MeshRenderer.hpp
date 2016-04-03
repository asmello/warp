#ifndef MeshRenderer_hpp
#define MeshRenderer_hpp

#include "Renderer.hpp"
#include "GameObject.hpp"
#include "Material.hpp"
#include "Mesh.hpp"

#include <memory>

namespace warp
{
    class MeshRenderer : public Renderer
    {
    private:
        std::shared_ptr<GameObject> gameobject;
        std::shared_ptr<Material> material;
        std::shared_ptr<Mesh> mesh;
        
    public:
        MeshRenderer(const std::shared_ptr<Mesh> mesh_,
                     const std::shared_ptr<Material> material_,
                     const std::shared_ptr<GameObject> transform_);
        MeshRenderer(const std::shared_ptr<Mesh> mesh_,
                     const std::shared_ptr<Material> material_);
        void init();
        void draw();
    };
}

#endif /* GameObject_hpp */
