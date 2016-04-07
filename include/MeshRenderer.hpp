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
    public:
        MeshRenderer(GameObject::ID object,
                     Material::ID materialID,
                     Mesh::ID meshID);
        MeshRenderer(Material::ID materialID,
                     Mesh::ID meshID);
        void render(Camera::ID cameraID);
        
    private:
        Mesh::ID meshID;
    };
}

#endif /* GameObject_hpp */
