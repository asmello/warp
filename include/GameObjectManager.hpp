#ifndef GameObjectManager_hpp
#define GameObjectManager_hpp

#include "ResourceManager.hpp"

#include <memory>

namespace warp
{
    class GameObject;

    class GameObjectManager : public ResourceManager<GameObject>
    {
    public:
        void setActive(Object<GameObject>::ID id);
        std::shared_ptr<GameObject> getNew();

    private:
        Object<GameObject>::ID activeID;
    };
}

#endif /* GameObjectManager_hpp */
