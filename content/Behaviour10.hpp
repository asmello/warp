#ifndef Behaviour10_hpp
#define Behaviour10_hpp

#include "Behaviour.hpp"
#include <iostream>
#include <SFML/Window.hpp>

#include "util.hpp"

class Behaviour10 : public warp::Behaviour
{

private:
	const float speed = 0.01666f;
	const float rotationSpeed = 0.003f;

public:

	virtual void Start()
	{
	}

	virtual void Update()
	{
		// Walk
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			this->getGameObject()->getTransform()->translate(.0f, speed, .0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			this->getGameObject()->getTransform()->translate(-speed, .0f, .0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			this->getGameObject()->getTransform()->translate(.0f, -speed, .0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			this->getGameObject()->getTransform()->translate(speed, .0f, .0f);
		}

		// rotate
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			this->getGameObject()->getTransform()->rotateX(rotationSpeed);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			this->getGameObject()->getTransform()->rotateX(-rotationSpeed);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			this->getGameObject()->getTransform()->rotateY(-rotationSpeed);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			this->getGameObject()->getTransform()->rotateY(rotationSpeed);
		}

	//	util::printMat4(this->getGameObject()->getTransform()->getTransformation());

		/*
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			getActiveGameObject()->getTransform()->rotateZ(0.025f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			getActiveGameObject()->getTransform()->rotateZ(-0.025f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			getActiveGameObject()->getTransform()->translate(.0f, .0f, -.01f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			getActiveGameObject()->getTransform()->translate(.0f, .0f, .01f);
		}*/
	}
};
#endif