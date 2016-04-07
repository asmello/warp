#ifndef CameraManager_hpp
#define CameraManager_hpp

#include "Identifier.hpp"
#include "Singleton.hpp"
#include "Camera.hpp"

#include <vector>
#include <memory>

namespace warp
{
    struct camera_tag{}; // Magic strong typedefness
    typedef Identifier<camera_tag, int, -1> CameraID;
    
    class CameraManager : public Singleton<CameraManager>
    {
    public:
        void setActive(CameraID id);
        std::shared_ptr<Camera> get(CameraID id);
        CameraID add(std::shared_ptr<Camera> camera);
        CameraID create();
        template <typename... Args> CameraID create(Args&&... args);
        
    private:
        std::vector<std::shared_ptr<Camera>> cameras;
        CameraID activeID;
    };
}

#endif /* CameraManager_hpp */
