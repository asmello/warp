#ifndef Scene_hpp
#define Scene_hpp

#include "Camera.hpp"
#include "Renderer.hpp"

#include <vector>
#include <memory>

namespace warp
{
    class Scene
    {
    private:
        std::vector<std::shared_ptr<Camera>> cameras;
        std::vector<std::shared_ptr<Renderer>> renderers;
    public:
        std::shared_ptr<Camera> getCamera(int index);
        std::vector<std::shared_ptr<Camera>> getCameras();
        std::shared_ptr<Renderer> getRenderer(int index);
        std::vector<std::shared_ptr<Renderer>> getRenderers();
        void addCamera(std::shared_ptr<Camera> camera);
        template <typename... Args> void createCamera(Args&&... args);
        void addRenderer(std::shared_ptr<Renderer> renderer);
        template <class T, typename... Args> void createRenderer(Args&&... args);
    };
}

#endif /* Scene_hpp */
