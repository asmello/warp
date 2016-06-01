#ifndef GameObject_hpp
#define GameObject_hpp

#include "Object.hpp"
#include "Component.hpp"
#include "Scene.hpp"

#include <memory>
#include <typeinfo>
#include <unordered_map>

namespace warp
{
    class Transform;
    
    class GameObject : public Object<GameObject>
    {
        
    public:
        // These constructors should not be used directly
        GameObject();
        
        template <class T, typename... Args> void newComponent(Args&&... args)
        {
            std::shared_ptr<T> component = std::make_shared<T>(args...);
            std::size_t type_code = typeid(T).hash_code();
            component->type_code = type_code;
            components.insert(type_code, component);
            std::shared_ptr<Scene> scene = getScene();
            scene->addComponent(component);
        }
        
        template <class T> std::shared_ptr<T> getComponent()
        {
            std::size_t type_code = typeid(T).hash_code();
            return components.find(type_code)->second;
        }
        
        template <class T> std::vector<std::shared_ptr<T>> getComponents()
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
        
        template <class T> void forEach(std::function<void(T)> mapper)
        {
            std::size_t type_code = typeid(T).hash_code();
            auto range = components.equal_range(type_code);
            for (auto it = range.first; it != range.second; ++it)
            {
                mapper(it->second);
            }
        }
        
        std::shared_ptr<Transform> getTransform();
        
    protected:
        std::unordered_multimap<std::size_t, std::shared_ptr<Component>> components;
        std::shared_ptr<Transform> transform;
        
        std::shared_ptr<Scene> getScene();
    };
}

#endif /* GameObject_hpp */
