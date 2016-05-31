#ifndef SceneRenderer_hpp
#define SceneRenderer_hpp

#include "Renderer.hpp"
#include "InputListener.hpp"

#include <GL/glew.h>

#include <vector>
#include <chrono>
#include <initializer_list>

namespace warp
{
    class Scene;
    class Camera;
    
    class SceneRenderer : public InputListener, public Renderer
    {
    private:
        std::shared_ptr<Scene> scene;
        Object<GameObject>::ID activeGameObjectID;
        Object<Camera>::ID activeCameraID;
        double t_total;
        bool paused;
        
    public:
        SceneRenderer();
        void init();
        void render();
        void pause();
        bool isPaused() const;
        void onKeyDown(Input::Key type);
        void onMouseScrolled(float delta);
        void onResized(int width, int height);
        void processInput();
        std::shared_ptr<GameObject> getActiveGameObject();
    };
}

#endif /* SimpleRenderer_hpp */
