#ifndef CameraManager_hpp
#define CameraManager_hpp

#include "Singleton.hpp"
#include "ResourceManager.hpp"

namespace warp
{
    class Camera;

    class CameraManager : public ResourceManager<Camera>, public Singleton<CameraManager>
    {
    public:
        void setActive(Object<Camera>::ID id);

    private:
        Object<Camera>::ID activeID;
    };
}

#endif /* CameraManager_hpp */
