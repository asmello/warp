#ifndef Behavior10_hpp
#define Behavior10_hpp

#include "Behavior.hpp"
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/System/Vector2.hpp>

#include "util.hpp"
#include "Camera.hpp"

class Behavior10 : public warp::Behavior
{

private:
	const float speed = 35.0 * 0.01666f;
	const float rotationSpeed = 0.1* 0.03f;

	sf::Vector2i prevMousePos;

public:

	Behavior10()
	{
	}

	virtual void start()
	{
		prevMousePos = sf::Mouse::getPosition();
	}

	virtual void update()
	{
		auto transform = this->getGameObject()->getTransform();
		auto parent = transform->getParent();

		// Walk
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			parent->setPosition(parent->getLocalPosition() + parent->forward() * speed);
			this->getGameObject()->getComponent<warp::Camera>()->update();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			parent->setPosition(parent->getLocalPosition() - parent->right() * speed);
			this->getGameObject()->getComponent<warp::Camera>()->update();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			parent->setPosition(parent->getLocalPosition() - parent->forward() * speed);
			this->getGameObject()->getComponent<warp::Camera>()->update();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			parent->setPosition(parent->getLocalPosition() + parent->right() * speed);
			this->getGameObject()->getComponent<warp::Camera>()->update();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			parent->setPosition(parent->getLocalPosition() + parent->up() * speed);
			this->getGameObject()->getComponent<warp::Camera>()->update();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			parent->setPosition(parent->getLocalPosition() - parent->up() * speed);
			this->getGameObject()->getComponent<warp::Camera>()->update();
		}

		// rotate
		if (prevMousePos != sf::Mouse::getPosition() - prevMousePos)
		{
			sf::Vector2i deltaPos = sf::Mouse::getPosition() - prevMousePos;
			transform->rotate(-rotationSpeed *deltaPos.y, 1, 0, 0);
			parent->rotate(-rotationSpeed *deltaPos.x, 0, 1, 0);

			sf::Mouse::setPosition(prevMousePos);
		}
	}
};
#endif