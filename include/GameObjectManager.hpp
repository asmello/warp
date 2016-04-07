#ifndef GameObjectManager_hpp
#define GameObjectManager_hpp

#include "Singleton.hpp"
#include "GameObject.hpp"

#include <vector>
#include <memory>

namespace warp
{
    class GameObject;
    
    class GameObjectManager : public Singleton<GameObjectManager>
    {
    public:
        void setActive(GameObject::ID id);
        std::shared_ptr<GameObject> get(GameObject::ID id);
        GameObject::ID add(std::shared_ptr<GameObject> gameObject);
        GameObject::ID create();
        
    private:
        std::vector<std::shared_ptr<GameObject>> gameObjects;
        GameObject::ID activeID;
    };
}

#endif /* GameObjectManager_hpp */
