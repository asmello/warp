#ifndef Behaviour10_hpp
#define Behaviour10_hpp

#include "Behaviour.hpp"
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/System/Vector2.hpp>

#include "util.hpp"
#include "Camera.hpp"

class Behaviour10 : public warp::Behaviour
{

private:
	const float speed = 5.0 * 0.01666f;
	const float rotationSpeed = 0.1* 0.03f;

	sf::Vector2i prevMousePos;

public:

	Behaviour10()
	{
	}

	virtual void Start()
	{
		prevMousePos = sf::Mouse::getPosition();
	}

	virtual void Update()
	{
		auto transform = this->getGameObject()->getTransform();
		auto parent = transform->getParent();

		// Walk
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			parent->setPosition(parent->getPosition() + parent->forward() * speed);
			this->getGameObject()->getComponent<warp::Camera>()->update();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			parent->setPosition(parent->getPosition() - parent->right() * speed);
			this->getGameObject()->getComponent<warp::Camera>()->update();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			parent->setPosition(parent->getPosition() - parent->forward() * speed);
			this->getGameObject()->getComponent<warp::Camera>()->update();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			parent->setPosition(parent->getPosition() + parent->right() * speed);
			this->getGameObject()->getComponent<warp::Camera>()->update();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			parent->setPosition(parent->getPosition() + parent->up() * speed);
			this->getGameObject()->getComponent<warp::Camera>()->update();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			parent->setPosition(parent->getPosition() - parent->up() * speed);
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