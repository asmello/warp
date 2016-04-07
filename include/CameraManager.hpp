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
        void setActive(Camera::ID id);
        std::shared_ptr<Camera> get(Camera::ID id);
        Camera::ID add(std::shared_ptr<Camera> camera);
        Camera::ID create();

		template <typename... Args>
		Camera::ID create(Args&&... args)
		{
			cameras.push_back(std::make_shared<Camera>(args...));
			return Camera::ID(cameras.size() - 1);
		}
        
    private:
        std::vector<std::shared_ptr<Camera>> cameras;
        Camera::ID activeID;
    };
}

#endif /* CameraManager_hpp */
