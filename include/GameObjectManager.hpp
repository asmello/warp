#ifndef GameObjectManager_hpp
#define GameObjectManager_hpp

#include "Singleton.hpp"
#include "GameObject.hpp"

#include <vector>
#include <memory>

namespace warp
{
    class GameObjectManager : public Singleton<GameObjectManager>
    {
    public:
        using ID = int;
        
        void setActive(ID id);
        std::shared_ptr<GameObject> get(ID id);
        ID add(std::shared_ptr<GameObject> gameObject);
        ID create();
        
    private:
        std::vector<std::shared_ptr<GameObject>> gameObjects;
        ID activeID;
    };
}

#endif /* GameObjectManager_hpp */
