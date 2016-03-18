#include "SimpleRenderer.hpp"
#include "Mesh.hpp"
#include "util.hpp"

SimpleRenderer::SimpleRenderer(const std::vector<std::shared_ptr<Mesh>>& objects) : t_total(0.0), tex(GL_TEXTURE_2D)
{
    this->objects = objects;
}

void SimpleRenderer::init()
{
    // Set the background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    // Start counting time
    t_last = std::chrono::high_resolution_clock::now();
    
    tex.loadFromFile(util::resourcePath() + "test.png");
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
    
    tex.bind(GL_TEXTURE0);
    
    // Draw the objects
    for (std::shared_ptr<Mesh> obj : objects)
    {
        obj->draw(t_total);
    }
}

void SimpleRenderer::reshape(int width, int height)
{
    for (std::shared_ptr<Mesh> obj : objects)
    {
        obj->reshape(width, height);
    }
}

