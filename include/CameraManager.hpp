#ifndef CameraManager_hpp
#define CameraManager_hpp

#include "Singleton.hpp"
#include "Camera.hpp"

#include <vector>
#include <memory>

namespace warp
{
    class CameraManager : public Singleton<CameraManager>
    {
    public:
        using ID = int;
        
        void setActive(ID id);
        std::shared_ptr<Camera> get(ID id);
        ID add(std::shared_ptr<Camera> camera);
        ID create();
        template <typename... Args> ID create(Args&&... args);
        
    private:
        std::vector<std::shared_ptr<Camera>> cameras;
        ID activeID;
    };
}

#endif /* CameraManager_hpp */
