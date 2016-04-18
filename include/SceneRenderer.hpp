#ifndef SceneRenderer_hpp
#define SceneRenderer_hpp

#include "Camera.hpp"
#include "Renderer.hpp"
#include "InputListener.hpp"

#include <GL/glew.h>

#include <vector>
#include <chrono>
#include <initializer_list>

namespace warp
{
    class Scene;
    
    class SceneRenderer : public InputListener
    {
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> t_last;
        std::shared_ptr<Scene> scene;
        GameObject::ID activeGameObjectID;
        Camera::ID activeCameraID;
        double t_total;
        bool paused;
        
    public:
        SceneRenderer(Object<Scene>::ID scene);
        SceneRenderer(std::initializer_list<Object<Scene>::ID> scenes);
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
