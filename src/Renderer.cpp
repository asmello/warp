#include "Renderer.hpp"

using namespace warp;

Renderer::Renderer() : active(false)
{
    
}

void Renderer::activate()
{
    active = true;
}