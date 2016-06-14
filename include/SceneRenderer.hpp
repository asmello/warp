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
    class Shader;
    class Light;
    
    class SceneRenderer : public ComponentImplementation<SceneRenderer>
    {
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> t_last;
        GLuint fbo[3], ftxo[4], frbo, vbo, vao, uboLights, uboCamera;
        Object<Shader>::ID screenShaderID, blurShaderID;
        double t_total;
        bool paused;
        
        void updateCamera(const std::shared_ptr<Camera> camera);
        
    public:
        SceneRenderer() : t_total(0.0), paused(false) {}
        ~SceneRenderer();
        void init();
        void render();
        void pause();
        bool isPaused() const;
    };
}

#endif /* SimpleRenderer_hpp */
