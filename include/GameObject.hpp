#ifndef GameObject_hpp
#define GameObject_hpp

#include "Object.hpp"

#include <vector>
#include <memory>

namespace warp
{
    class Component;
    class Transform;
    
    class GameObject : public Object<GameObject>
    {
        friend class GameObjectManager;
        
    public:
        // These constructors should not be used directly
        GameObject();
        GameObject(std::shared_ptr<Transform> transform);
        
        void addComponent(std::shared_ptr<Component> component);
        template <class T, typename... Args> void createComponent(Args&&... args);
        template <class T> std::vector<std::shared_ptr<T>> getComponents();
        std::shared_ptr<Transform> getTransform();
        
    protected:
        std::vector<std::shared_ptr<Component>> components;
        std::shared_ptr<Transform> transform;
    };
}

#endif /* GameObject_hpp */
