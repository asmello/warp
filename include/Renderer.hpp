#ifndef Renderer_hpp
#define Renderer_hpp

#include "GameObjectManager.hpp"
#include "MaterialManager.hpp"
#include "CameraManager.hpp"

#include <memory>

namespace warp
{
    class Renderer : public Component
    {
    public:
        Renderer(GameObjectManager::ID gameObject, MaterialManager::ID material);
        Renderer(MaterialManager::ID material);
        GameObjectManager::ID getGameObject();
        virtual void render(CameraManager::ID cameraID) = 0;
        
    protected:
        GameObjectManager::ID gameObjectID;
        MaterialManager::ID materialID;
    };
}

#endif /* Renderer_hpp */
