#ifndef Scene_hpp
#define Scene_hpp

#include "Object.hpp"

#include <vector>
#include <memory>
#include <typeinfo>
#include <algorithm>
#include <unordered_map>
#include <functional>

namespace warp
{
    class Transform;
    class Component;
    class Scene;
    
    class GameObject : public Object<GameObject>, public std::enable_shared_from_this<GameObject>
    {
        friend class Scene;
        
    public:
        // These constructors should not be used directly
        GameObject();
        GameObject(std::shared_ptr<Transform> transform);
        
        template <class T, typename... Args> std::shared_ptr<T> newComponent(Args&&... args);
        template <class T> std::shared_ptr<T> getComponent();
        template <class T> std::vector<std::shared_ptr<T>> getComponents();
        template <class T> void forEach(std::function<void(T)> mapper);
        
        std::shared_ptr<Transform> getTransform();
        bool isRoot() const;
        
    protected:
        std::unordered_multimap<std::size_t, std::shared_ptr<Component>> components;
        std::shared_ptr<Transform> transform;
        
        std::shared_ptr<Scene> getScene();
    };
    
    class Scene : public GameObject
    {
        friend class GameObject;
        
    private:
        template <class T> void addComponent(std::shared_ptr<T> component)
        {
            components.insert(std::pair<std::size_t, std::shared_ptr<Component>>(component->type_code, component));
        }
        
    public:
        std::shared_ptr<GameObject> newGameObject();
        
        static std::shared_ptr<Scene> newScene();

		void Behaviour_Start();
		void Behaviour_Update();
    };
    
    template <class T, typename... Args>
    std::shared_ptr<T> GameObject::newComponent(Args&&... args)
    {
        std::shared_ptr<T> component = std::make_shared<T>(args...);
        component->gameObject = shared_from_this();
        std::size_t type_code = typeid(T).hash_code();
        component->type_code = type_code;
        components.insert(std::pair<std::size_t, std::shared_ptr<Component>>(type_code, component));
        if (typeid(this) != typeid(Scene))
        {
            std::shared_ptr<Scene> scene = getScene();
            scene->components.insert(std::pair<std::size_t, std::shared_ptr<Component>>(type_code, component));
        }
        return component;
    }
    
    template <class T>
    std::shared_ptr<T> GameObject::getComponent()
    {
        std::size_t type_code = typeid(T).hash_code();
        return std::static_pointer_cast<T>(components.find(type_code)->second);
    }
    
    template <class T>
    std::vector<std::shared_ptr<T>> GameObject::getComponents()
    {
        std::size_t type_code = typeid(T).hash_code();
        std::vector<std::shared_ptr<T>> filtered_components;
        auto range = components.equal_range(type_code);
        filtered_components.reserve(std::distance(range.first, range.second));
        for (auto it = range.first; it != range.second; ++it)
        {
            filtered_components.push_back(std::static_pointer_cast<T>((*it).second));
        }
        return filtered_components;
    }
    
    template <class T>
    void GameObject::forEach(std::function<void(T)> mapper)
    {
        std::size_t type_code = typeid(T).hash_code();
        auto range = components.equal_range(type_code);
        std::for_each(range.first, range.second,
                      [&mapper](std::pair<std::size_t, std::shared_ptr<Component>> element) {
                          mapper(element.second);
                      });
    }
    
}

#endif /* Scene_hpp */
