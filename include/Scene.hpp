#ifndef Scene_hpp
#define Scene_hpp

#include "Camera.hpp"
#include "CameraManager.hpp"
#include "Renderer.hpp"

#include <vector>
#include <memory>

namespace warp
{
    class Scene
    {
    private:
        std::vector<Camera::ID> cameras;
        std::vector<std::shared_ptr<Renderer>> renderers;
    public:
        std::vector<Camera::ID> getCameras();
        std::vector<std::shared_ptr<Renderer>> getRenderers();
        void addCamera(Camera::ID camera);
        void createCamera();
        template <typename... Args>
        void createCamera(Args&&... args)
        {
            cameras.push_back(CameraManager::getInstance()->create(args...));
        }
        void addRenderer(std::shared_ptr<Renderer> renderer);
        template <class T, typename... Args> void createRenderer(Args&&... args)
        {
            renderers.push_back(std::make_shared<T>(args...));
        }
    };
}

#endif /* Scene_hpp */
