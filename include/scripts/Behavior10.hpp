#ifndef Behavior10_hpp
#define Behavior10_hpp

#include "WindowManager.hpp"
#include "Behavior.hpp"
#include "Camera.hpp"
#include "Input.hpp"

#include <glm/glm.hpp>

using namespace warp;

class Behavior10 : public Behavior, public InputListener
{

private:
	const float speed = 15.0 * 0.01666f;
	const float rotationSpeed = 0.1 * 0.03f;
    glm::vec2 prevMousePos;

public:
	virtual void start()
	{
        if (auto window = WindowManager::getInstance()->getActive())
        {
            prevMousePos = window->getCenter();
            window->setMouseVisible(false);
        }
        Input::setMousePos(prevMousePos);
	}

	virtual void update()
	{
		auto transform = this->getGameObject()->getTransform();
		auto parent = transform->getParent();

		// Walk
        if (Input::isKeyPressed(Input::Key::W))
		{
			parent->setPosition(parent->getPosition() + parent->forward() * speed);
		}
        if (Input::isKeyPressed(Input::Key::A))
		{
			parent->setPosition(parent->getPosition() - parent->right() * speed);
		}
        if (Input::isKeyPressed(Input::Key::S))
		{
			parent->setPosition(parent->getPosition() - parent->forward() * speed);
		}
        if (Input::isKeyPressed(Input::Key::D))
		{
			parent->setPosition(parent->getPosition() + parent->right() * speed);
		}
        if (Input::isKeyPressed(Input::Key::Space))
		{
			parent->setPosition(parent->getPosition() + parent->up() * speed);
		}
        if (Input::isKeyPressed(Input::Key::LShift))
		{
			parent->setPosition(parent->getPosition() - parent->up() * speed);
		}
        
        glm::vec2 deltaPos = Input::getMousePos() - prevMousePos;

		// rotate
        if (prevMousePos != deltaPos)
		{
			transform->rotate(-rotationSpeed * deltaPos.y, 1, 0, 0);
			parent->rotate(-rotationSpeed * deltaPos.x, 0, 1, 0);
			Input::setMousePos(prevMousePos);
		}
	}
    
    virtual void onResized(int width, int height)
    {
        getGameObject()->getComponent<warp::Camera>()->reshape(width, height);
    }
};
#endif