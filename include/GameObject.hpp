#ifndef GameObject_hpp
#define GameObject_hpp

#include "Object.hpp"

#include <vector>
#include <memory>
#include <typeinfo>
#include <unordered_map>

namespace warp
{
    class Transform;
    class Component;
    
    class GameObject : public Object<GameObject>
    {
        
    public:
        // These constructors should not be used directly
        GameObject();
        
        template <class T, typename... Args> std::shared_ptr<T> newComponent(Args&&... args);
        template <class T> std::shared_ptr<T> getComponent();
        template <class T> std::vector<std::shared_ptr<T>> getComponents();
        template <class T> void forEach(std::function<void(T)> mapper);
        
        std::shared_ptr<Transform> getTransform();
        
    protected:
        std::unordered_multimap<std::size_t, std::shared_ptr<Component>> components;
        std::shared_ptr<Transform> transform;
        
        std::shared_ptr<Scene> getScene();
    };
    
}

#include "Scene.hpp"

namespace warp
{
    template <class T, typename... Args> std::shared_ptr<T> GameObject::newComponent(Args&&... args)
    {
        std::shared_ptr<T> component = std::make_shared<T>(args...);
        std::size_t type_code = typeid(T).hash_code();
        component->type_code = type_code;
        components.insert(type_code, component);
        std::shared_ptr<Scene> scene = getScene();
        scene->addComponent(component);
        return component;
    }
    
    template <class T> std::shared_ptr<T> GameObject::getComponent()
    {
        std::size_t type_code = typeid(T).hash_code();
        return components.find(type_code)->second;
    }
    
    template <class T> std::vector<std::shared_ptr<T>> GameObject::getComponents()
    {
        std::size_t type_code = typeid(T).hash_code();
        std::vector<std::shared_ptr<T>> filtered_components;
        auto range = components.equal_range(type_code);
        for (auto it = range.first; it != range.second; ++it)
        {
            filtered_components.push_back(it->second);
        }
        return filtered_components;
    }
    
    template <class T> void GameObject::forEach(std::function<void(T)> mapper)
    {
        std::size_t type_code = typeid(T).hash_code();
        auto range = components.equal_range(type_code);
        for (auto it = range.first; it != range.second; ++it)
        {
            mapper(it->second);
        }
    }
}

#endif /* GameObject_hpp */
