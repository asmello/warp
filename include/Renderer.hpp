#ifndef Renderer_hpp
#define Renderer_hpp

#include "Component.hpp"
#include "GameObject.hpp"
#include "Material.hpp"
#include "Camera.hpp"

#include <memory>

namespace warp
{
    class Renderer : public Component
    {
    public:
        Renderer(GameObject::ID gameObject, Material::ID material);
        Renderer(Material::ID material);
        GameObject::ID getGameObject();
        virtual void render(Camera::ID cameraID) = 0;
        
    protected:
        Material::ID materialID;
    };
}

#endif /* Renderer_hpp */
