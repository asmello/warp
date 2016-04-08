#ifndef CameraManager_hpp
#define CameraManager_hpp

#include "ResourceManager.hpp"

namespace warp
{
    class Camera;

    class CameraManager : public ResourceManager<Camera>
    {
    public:
        void setActive(Object<Camera>::ID id);

    private:
        Object<Camera>::ID activeID;
    };
}

#endif /* CameraManager_hpp */
