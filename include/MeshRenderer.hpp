#ifndef MeshRenderer_hpp
#define MeshRenderer_hpp

#include "Renderer.hpp"

#include <vector>
#include <memory>

namespace warp
{
    class GameObject;
    class Material;
    class Camera;
    class Light;
    class Mesh;
    
    class MeshRenderer : public Renderer
    {
    public:
        MeshRenderer(Object<Material>::ID materialID,
                     Object<Mesh>::ID meshID);
        void render();
        void activate();
        
    private:
        Object<Material>::ID materialID;
        Object<Mesh>::ID meshID;
    };
}

#endif /* GameObject_hpp */
