#ifndef SimpleRenderer_hpp
#define SimpleRenderer_hpp

#include "Renderer.hpp"
#include "Mesh.hpp"

#include <GL/glew.h>

#include <vector>
#include <chrono>
#include <memory>

class SimpleRenderer : public Renderer {
private:
    std::vector<std::shared_ptr<Mesh>> objects;
    std::chrono::time_point<std::chrono::high_resolution_clock> t_last;
    double t_total;
    
public:
    SimpleRenderer(const std::vector<std::shared_ptr<Mesh>>& objects);
    void init();
    void draw();
    void reshape(int width, int height);
};

#endif /* SimpleRenderer_hpp */
