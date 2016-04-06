#ifndef GameObject_hpp
#define GameObject_hpp

#include "Shader.hpp"
#include "Transform.hpp"

#include <vector>
#include <memory>

namespace warp
{
    class Component;
    
    class GameObject
    {
        friend class GameObjectManager;
        
    protected:
        std::shared_ptr<Transform> transform;
        std::vector<std::shared_ptr<Component>> components;
        
    public:
        // These constructors should not be used directly
        GameObject();
        GameObject(std::unique_ptr<Transform> transform);
        
        void addComponent(std::shared_ptr<Component> component);
        template <class T, typename... Args> void createComponent(Args&&... args);
        template <class T> std::vector<std::shared_ptr<T>> getComponents();
        std::shared_ptr<Transform> getTransform();
    };
}

#include "Component.hpp"

#endif /* GameObject_hpp */
