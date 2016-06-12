#include "Input.hpp"

#include "WindowManager.hpp"

#include <SFML/Window/Mouse.hpp>
#include <SFML/System/Vector2.hpp>

using namespace warp;

void Input::addListener(std::shared_ptr<InputListener> listener)
{
    getInstance()->listeners.push_back(listener);
}

glm::vec2 Input::getMousePos()
{
    sf::Vector2i pos = sf::Mouse::getPosition();
    return glm::vec2(pos.x, pos.y);
}

void Input::setMousePos(glm::vec2 pos)
{
    sf::Vector2i sfPos = sf::Vector2i(pos.x, pos.y);
    sf::Mouse::setPosition(sfPos);
}

bool Input::isKeyPressed(Key key)
{
    return sf::Keyboard::isKeyPressed(key);
}

void Input::flush()
{
    sf::Event windowEvent;
    if (auto window = WindowManager::getInstance()->getActive())
    {
        while (window->window->pollEvent(windowEvent))
        {
            switch (windowEvent.type)
            {
                case sf::Event::Closed:
                    getInstance()->notifyClosed();
                    break;
                case sf::Event::KeyPressed:
                    getInstance()->notifyKeyDown(windowEvent.key.code);
                    break;
                case sf::Event::MouseWheelScrolled:
                    getInstance()->notifyMouseScrolled(windowEvent.mouseWheelScroll.delta);
                    break;
                case sf::Event::Resized:
                    getInstance()->notifyResized(windowEvent.size.width, windowEvent.size.height);
                    break;
                default:
                    break;
            }
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
