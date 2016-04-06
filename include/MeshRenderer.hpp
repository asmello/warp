#ifndef MeshRenderer_hpp
#define MeshRenderer_hpp

#include "Renderer.hpp"
#include "GameObject.hpp"
#include "MeshManager.hpp"
#include "MaterialManager.hpp"

#include <memory>

namespace warp
{
    class MeshRenderer : public Renderer
    {
    private:
        std::shared_ptr<Mesh> mesh;
        
    public:
        MeshRenderer(const std::shared_ptr<GameObject> object,
                     MaterialManager::ID material,
                     MeshManager::ID mesh);
        MeshRenderer(MaterialManager::ID material,
                     MeshManager::ID mesh);
        void init();
        void render();
    };
}

#endif /* GameObject_hpp */
