#ifndef Behaviour10_hpp
#define Behaviour10_hpp

#include "Behaviour.hpp"
#include <iostream>
#include <SFML/Window.hpp>

#include "util.hpp"
#include "Camera.hpp"

class Behaviour10 : public warp::Behaviour
{

private:
	const float speed = 5.0 * 0.01666f;
	const float rotationSpeed = 0.03f;

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
			this->getGameObject()->getComponent<warp::Camera>()->update();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			this->getGameObject()->getTransform()->translate(-speed, .0f, .0f);
			this->getGameObject()->getComponent<warp::Camera>()->update();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			this->getGameObject()->getTransform()->translate(.0f, -speed, .0f);
			this->getGameObject()->getComponent<warp::Camera>()->update();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			this->getGameObject()->getTransform()->translate(speed, .0f, .0f);
			this->getGameObject()->getComponent<warp::Camera>()->update();
		}

		// rotate
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			this->getGameObject()->getTransform()->rotateX(rotationSpeed);
			this->getGameObject()->getComponent<warp::Camera>()->update();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			this->getGameObject()->getTransform()->rotateX(-rotationSpeed);
			this->getGameObject()->getComponent<warp::Camera>()->update();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			this->getGameObject()->getTransform()->rotateY(-rotationSpeed);
			this->getGameObject()->getComponent<warp::Camera>()->update();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			this->getGameObject()->getTransform()->rotateY(rotationSpeed);
			this->getGameObject()->getComponent<warp::Camera>()->update();
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