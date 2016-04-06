#ifndef Component_hpp
#define Component_hpp

#include "GameObject.hpp"

#include <memory>

namespace warp
{
    class GameObject;
    
    class Component
    {
    private:
        std::weak_ptr<GameObject> gameObject;
        
    public:
        std::shared_ptr<GameObject> getGameObject();
    };
}

#endif /* Component_hpp */
