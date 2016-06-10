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
    class Light;
    
    class SceneRenderer : public InputListener, public Renderer
    {
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> t_last;
        Object<GameObject>::ID activeGameObjectID;
        Object<Camera>::ID activeCameraID;
        double t_total;
        bool paused;
        GLuint uboLights, uboCamera;
        
        void updateCamera(const std::shared_ptr<Camera> camera);
        
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
        
        static const GLuint NUM_UNIFORM_MATRICES = 1;
    };
}

#endif /* SimpleRenderer_hpp */
