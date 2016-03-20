#ifndef Renderer_hpp
#define Renderer_hpp

#include "GameObject.hpp"
#include "Camera.hpp"

#include <memory>

namespace warp {
    class Renderer {
    protected:
        bool paused;
        std::shared_ptr<Camera> camera;
        std::vector<std::shared_ptr<GameObject>> objects;
        
    public:
        Renderer(const std::vector<std::shared_ptr<GameObject>>& objects);
        Renderer(const std::shared_ptr<Camera> camera,
                 const std::vector<std::shared_ptr<GameObject>>& objects);
        
        virtual void draw() = 0;
        void init(const std::shared_ptr<const Shader> shader);
        void pause();
        bool isPaused() const;
        void setCamera(std::shared_ptr<Camera> camera);
        std::shared_ptr<Camera> getCamera();
    };
}

#endif /* Renderer_hpp */
