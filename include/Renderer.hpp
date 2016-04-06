#ifndef Renderer_hpp
#define Renderer_hpp

#include "GameObject.hpp"
#include "Material.hpp"

#include <memory>

namespace warp
{
    class Renderer : public Component
    {
    protected:
        std::shared_ptr<GameObject> gameObject;
        std::shared_ptr<Material> material;
        
    public:
        Renderer(std::shared_ptr<GameObject> gameObject, std::shared_ptr<Material> material);
        Renderer(std::shared_ptr<Material> material);
        std::shared_ptr<GameObject> getGameObject();
        virtual void render() = 0;
    };
}

#endif /* Renderer_hpp */
