#ifndef GameObjectManager_hpp
#define GameObjectManager_hpp

#include "Singleton.hpp"
#include "ResourceManager.hpp"

#include <memory>

namespace warp
{
    class GameObject;

    class GameObjectManager : public ResourceManager<GameObject>, public Singleton<GameObjectManager>
    {
    public:
        void setActive(Object<GameObject>::ID id);

    private:
        Object<GameObject>::ID activeID;
    };
}

#endif /* GameObjectManager_hpp */
