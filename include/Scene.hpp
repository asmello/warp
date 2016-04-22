#ifndef Scene_hpp
#define Scene_hpp

#include "CameraManager.hpp"
#include "Renderer.hpp"

#include <vector>
#include <memory>

namespace warp
{
    class Light;
    class Camera;
    
    class Scene : public Object<Scene>
    {
        friend class SceneManager;
    private:
        std::vector<Object<Camera>::ID> cameras;
        std::vector<std::shared_ptr<Renderer>> renderers;
        std::vector<Object<Light>::ID> lights;
        
    public:
        std::vector<Object<Camera>::ID> getCameras();
        std::vector<Object<Light>::ID> getLights();
        std::vector<std::shared_ptr<Renderer>> getRenderers();
        void addCamera(Object<Camera>::ID camera);
        void addLight(Object<Light>::ID light);
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
