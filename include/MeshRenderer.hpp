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
        MeshRenderer(Object<GameObject>::ID object,
                     Object<Material>::ID materialID,
                     Object<Mesh>::ID meshID);
        MeshRenderer(Object<Material>::ID materialID,
                     Object<Mesh>::ID meshID);
        void render(Object<Camera>::ID cameraID, std::vector<Object<Light>::ID> lights);
        
    private:
        Object<Mesh>::ID meshID;
    };
}

#endif /* GameObject_hpp */
