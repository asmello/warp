#include "SimpleRenderer.hpp"
#include "Mesh.hpp"
#include "util.hpp"

using namespace warp;

SimpleRenderer::SimpleRenderer(const std::vector<std::shared_ptr<warp::GameObject>>& objs) :
Renderer(objs), t_total(0.0)
{
    
}

SimpleRenderer::SimpleRenderer(const std::shared_ptr<warp::Camera> camera,
                               const std::vector<std::shared_ptr<warp::GameObject>>& objs) :
Renderer(camera, objs), t_total(0.0)
{
    
}

void SimpleRenderer::init(const std::shared_ptr<const Shader> shader)
{
    Renderer::init(shader); // Parent initializer
    
    for (auto obj : objects) obj->init(shader);
    
    // Set the background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    // Start counting time
    t_last = std::chrono::high_resolution_clock::now();
    
    // Set geometry shader settings
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
}

void SimpleRenderer::draw()
{
    // Clear the screen to black
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Get current time
    auto t_now = std::chrono::high_resolution_clock::now();
    
    // Update total elapsed time (if not paused)
    if (!paused) {
        t_total += std::chrono::duration_cast<std::chrono::duration<double>>(t_now - t_last).count();
    }
    
    // Update last tick
    t_last = t_now;
    
    // Update the camera
    camera->update();
    
    // Draw the objects
    for (auto obj : objects) obj->draw();
}

