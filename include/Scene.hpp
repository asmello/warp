#ifndef Scene_hpp
#define Scene_hpp

#include "Object.hpp"
#include "Behavior.hpp"
#include "Transform.hpp"

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
	class Behaviour;
    
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
		template <class T> std::vector<std::shared_ptr<T>> getComponentsInChildren();
        template <class T> void forEach(std::function<void(T)> mapper);
        
        std::shared_ptr<Transform> getTransform();
        bool isRoot() const;
        
    protected:
        std::unordered_multimap<std::size_t, std::shared_ptr<Component>> components;
        std::shared_ptr<Transform> transform;
        
        std::shared_ptr<Scene> getScene();

	private:
		std::vector<std::shared_ptr<GameObject>> gameObjectList; // TODO [Temporary solution for missing gameObject refereces] Weak_ptr expiring when functions exit? (componet references to the GO went missing a lot of times) FIX this
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
        
        void start();
        void update();
    };


    template <class T, typename... Args>
    std::shared_ptr<T> GameObject::newComponent(Args&&... args)
    {
        std::shared_ptr<T> component = std::make_shared<T>(args...);
        component->gameObject = shared_from_this();
        std::size_t type_code = component->type_code;
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
	std::vector<std::shared_ptr<T>> GameObject::getComponentsInChildren()
	{
		std::size_t type_code = typeid(T).hash_code();
		std::vector<std::shared_ptr<T>> filtered_components;
		auto range = components.equal_range(type_code);
		filtered_components.reserve(std::distance(range.first, range.second));
		for (auto it = range.first; it != range.second; ++it)
		{
			filtered_components.push_back(std::static_pointer_cast<T>((*it).second));
		}
        auto children = getTransform()->getChildren();
		for (int i = 0; i < children.size(); i++)
		{
			if (auto tmp1 = children[i].lock())
			{
				auto tmp = tmp1->getGameObject()->getComponentsInChildren<T>();
				for (int j = 0; j<tmp.size(); j++)
                {
                    filtered_components.push_back(tmp[j]);
                }
			}
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
