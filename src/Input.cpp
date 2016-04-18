#include "Input.hpp"

using namespace warp;

Input::Input(std::shared_ptr<sf::Window> window_) : window(window_)
{

}

void Input::addListener(std::shared_ptr<InputListener> listener)
{
    listeners.push_back(listener);
}

void Input::flush()
{
    sf::Event windowEvent;
    while (window->pollEvent(windowEvent))
    {
        switch (windowEvent.type)
        {
            case sf::Event::Closed:
                notifyClosed();
                break;
            case sf::Event::KeyPressed:
                notifyKeyDown(windowEvent.key.code);
                break;
            case sf::Event::MouseWheelScrolled:
                notifyMouseScrolled(windowEvent.mouseWheelScroll.delta);
                break;
            case sf::Event::Resized:
                notifyResized(windowEvent.size.width, windowEvent.size.height);
                break;
            default:
                break;
        }
    }

}

void Input::notifyClosed()
{
    for (const auto listener : listeners) listener->onClosed();
}

void Input::notifyKeyDown(Input::Key type)
{
    for (const auto listener : listeners) listener->onKeyDown(type);
}

void Input::notifyMouseScrolled(float delta)
{
    for (const auto listener : listeners) listener->onMouseScrolled(delta);
}

void Input::notifyResized(int width, int height)
{
    for (const auto listener : listeners) listener->onResized(width, height);
}
