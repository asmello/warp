#ifndef Component_hpp
#define Component_hpp

#include "Object.hpp"

#include <memory>
#include <typeinfo>

namespace warp
{
	class GameObject;

    class Component : public Object<Component>
    {
        friend class GameObject;
        friend class Scene;
    public:
        Component();
        std::shared_ptr<GameObject> getGameObject() const;
        Object<GameObject>::ID getGameObjectID() const;
        
    protected:
        std::weak_ptr<GameObject> gameObject;
    };
    
    template <class T>
    class ComponentImplementation : public Component
    {
    public:
        const std::size_t type_code = typeid(T).hash_code();
    };
}

#endif /* Component_hpp */
