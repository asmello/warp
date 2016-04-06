#ifndef GameObject_hpp
#define GameObject_hpp

#include "Shader.hpp"
#include "Transform.hpp"
#include "Component.hpp"

#include <vector>
#include <memory>

namespace warp
{
    class GameObject
    {
    protected:
        std::shared_ptr<Transform> transform;
        std::vector<std::shared_ptr<Component>> components;
        
    public:
        GameObject();
        GameObject(std::unique_ptr<Transform> transform);
        void init(std::shared_ptr<Shader> shader);
        void addComponent(std::shared_ptr<Component> component);
        template <class T, typename... Args> void createComponent(Args&&... args);
        template <class T> std::vector<std::shared_ptr<T>> getComponents();
        std::shared_ptr<Transform> getTransform();
    };
}

#endif /* GameObject_hpp */
