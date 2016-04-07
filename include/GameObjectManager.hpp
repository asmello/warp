#ifndef GameObjectManager_hpp
#define GameObjectManager_hpp

#include "Singleton.hpp"
#include "GameObject.hpp"
#include "Identifier.hpp"

#include <vector>
#include <memory>

namespace warp
{
    struct gameobject_tag{}; // Magic strong typedefness
    typedef Identifier<gameobject_tag, int, -1> GameObjectID;
    
    class GameObjectManager : public Singleton<GameObjectManager>
    {
    public:
        void setActive(GameObjectID id);
        std::shared_ptr<GameObject> get(GameObjectID id);
        GameObjectID add(std::shared_ptr<GameObject> gameObject);
        GameObjectID create();
        
    private:
        std::vector<std::shared_ptr<GameObject>> gameObjects;
        GameObjectID activeID;
    };
}

#endif /* GameObjectManager_hpp */
