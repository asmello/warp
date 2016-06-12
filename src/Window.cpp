#include "Window.hpp"

using namespace warp;

Window::Window(std::shared_ptr<sf::Window> _window) : window(_window)
{
    
}

glm::vec2 Window::getSize() const
{
    sf::Vector2u size = window->getSize();
    return glm::vec2(size.x, size.y);
}

glm::vec2 Window::getCenter() const
{
    sf::Vector2u size = window->getSize();
    sf::Vector2i pos = window->getPosition();
    return glm::vec2(pos.x + size.x/2, -pos.y);
}

void Window::setMouseVisible(bool visible)
{
    window->setMouseCursorVisible(visible);
}