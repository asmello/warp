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
        GLuint fbo, ftxo, frbo, vbo, vao, uboLights, uboCamera;
        Object<Shader>::ID screenShaderID;
        
        void updateCamera(const std::shared_ptr<Camera> camera);
        
    public:
        ~SceneRenderer();
        void init();
        void render();
    };
}

#endif /* SimpleRenderer_hpp */
