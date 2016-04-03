#ifndef SceneRenderer_hpp
#define SceneRenderer_hpp

#include "Renderer.hpp"
#include "GameObject.hpp"
#include "InputListener.hpp"

#include <GL/glew.h>

#include <vector>
#include <chrono>

namespace warp
{
    class SceneRenderer : public Renderer, public InputListener
    {
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> t_last;
        std::vector<std::shared_ptr<Renderer>> renderers;
        double t_total;
        bool paused;
        
    public:
        SceneRenderer(const std::vector<std::shared_ptr<Renderer>>& renderers);
        void init();
        void draw();
        void pause();
        bool isPaused() const;
        void onKeyDown(Input::Key type);
        void onMouseScrolled(float delta);
        void onResized(int width, int height);
        void processInput();
    };
}

#endif /* SimpleRenderer_hpp */
