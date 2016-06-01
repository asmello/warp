#ifndef Component_hpp
#define Component_hpp

#include "Object.hpp"

#include <memory>

namespace warp
{
	class GameObject;

    class Component : public Object<Component>
    {
        friend class GameObject;
    public:
        Component();
        std::shared_ptr<GameObject> getGameObject() const;
        Object<GameObject>::ID getGameObjectID() const;
        
    protected:
        std::weak_ptr<GameObject> gameObject;
        
    private:
        std::size_t type_code;
    };
}

#endif /* Component_hpp */
