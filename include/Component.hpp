#ifndef Component_hpp
#define Component_hpp

#include "Object.hpp"

#include <memory>

namespace warp
{
	class GameObject;

    class Component : public Object<Component>
    {
    private:
        std::weak_ptr<GameObject> gameObject;
        
    public:
        Component();
        Component(Object<GameObject>::ID gameObject);
        Component(std::shared_ptr<GameObject> gameObject);
        std::shared_ptr<GameObject> getGameObject();
    };
}

#endif /* Component_hpp */
