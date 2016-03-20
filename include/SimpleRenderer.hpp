#ifndef SimpleRenderer_hpp
#define SimpleRenderer_hpp

#include "Renderer.hpp"

#include "GameObject.hpp"
#include "Camera.hpp"

#include <GL/glew.h>

#include <vector>
#include <chrono>

namespace warp {
    class SimpleRenderer : public Renderer {
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> t_last;
        double t_total;
        
    public:
        SimpleRenderer(const std::shared_ptr<warp::Camera> camera,
                       const std::vector<std::shared_ptr<warp::GameObject>>& objects);
        SimpleRenderer(const std::vector<std::shared_ptr<warp::GameObject>>& objects);
        void init(const std::shared_ptr<const Shader> shader);
        void draw();
        
    };
}

#endif /* SimpleRenderer_hpp */
