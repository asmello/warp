#include "Window.hpp"

#include "Input.hpp"

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
    return glm::vec2(size.x/2, size.y/2);
}

void Window::setMouseVisible(bool visible)
{
    window->setMouseCursorVisible(visible);
}