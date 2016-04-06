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
        MeshRenderer(GameObjectManager::ID object,
                     MaterialManager::ID materialID,
                     MeshManager::ID meshID);
        MeshRenderer(MaterialManager::ID materialID,
                     MeshManager::ID meshID);
        void render(CameraManager::ID cameraID);
        
    private:
        MeshManager::ID meshID;
    };
}

#endif /* GameObject_hpp */
