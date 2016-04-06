#ifndef SceneRenderer_hpp
#define SceneRenderer_hpp

#include "Camera.hpp"
#include "Renderer.hpp"
#include "Scene.hpp"
#include "InputListener.hpp"

#include <GL/glew.h>

#include <vector>
#include <chrono>

namespace warp
{
    class SceneRenderer : public InputListener
    {
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> t_last;
        std::shared_ptr<Scene> scene;
        int activeObjectIndex;
        int activeCameraIndex;
        double t_total;
        bool paused;
        
    public:
        SceneRenderer(std::shared_ptr<Scene> scene);
        void init();
        void render();
        void pause();
        bool isPaused() const;
        void onKeyDown(Input::Key type);
        void onMouseScrolled(float delta);
        void onResized(int width, int height);
        void processInput();
        std::shared_ptr<GameObject> getActiveObject();
    };
}

#endif /* SimpleRenderer_hpp */
