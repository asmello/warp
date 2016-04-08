#ifndef Component_hpp
#define Component_hpp

#include "Object.hpp"

#include <memory>

namespace warp
{
	class GameObject;

    class Component
    {
    public:
        Component();
        Component(Object<GameObject>::ID gameObject);
        Object<GameObject>::ID getGameObjectID() const;
        std::shared_ptr<GameObject> getGameObject() const;
        
    protected:
        Object<GameObject>::ID gameObjectID;
    };
}

#endif /* Component_hpp */
