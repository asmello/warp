#ifndef SimpleRenderer_hpp
#define SimpleRenderer_hpp

#include "InputListener.hpp"
#include "GameObject.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"

#include <GL/glew.h>

#include <vector>
#include <chrono>

namespace warp {
    class SimpleRenderer : public Renderer, public InputListener {
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> t_last;
        int activeIndex;
        double t_total;
        
        std::shared_ptr<GameObject> getActiveObject();
        
    public:
        SimpleRenderer(const std::shared_ptr<Camera> camera,
                       const std::vector<std::shared_ptr<GameObject>>& objects);
        SimpleRenderer(const std::vector<std::shared_ptr<GameObject>>& objects);
        void init(const std::shared_ptr<const Shader> shader);
        void draw();
        void onKeyDown(Input::Key type);
        void onMouseScrolled(float delta);
        void onResized(int width, int height);
        void processInput();
    };
}

#endif /* SimpleRenderer_hpp */
