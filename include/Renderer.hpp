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
        Renderer(GameObjectID gameObject, MaterialID material);
        Renderer(MaterialID material);
        GameObjectID getGameObject();
        virtual void render(CameraID cameraID) = 0;
        
    protected:
        GameObjectID gameObjectID;
        MaterialID materialID;
    };
}

#endif /* Renderer_hpp */
