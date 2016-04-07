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
    public:
        MeshRenderer(GameObjectID object,
                     MaterialID materialID,
                     MeshID meshID);
        MeshRenderer(MaterialID materialID,
                     MeshID meshID);
        void render(CameraID cameraID);
        
    private:
        MeshID meshID;
    };
}

#endif /* GameObject_hpp */
