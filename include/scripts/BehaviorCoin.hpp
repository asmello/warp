#ifndef BehaviorCoin_hpp
#define BehaviorCoin_hpp

#include "WindowManager.hpp"
#include "Behavior.hpp"
#include "Camera.hpp"
#include "Input.hpp"

#include <glm/glm.hpp>

using namespace warp;

class BehaviorCoin : public Behavior
{
    
private:
    const float rotationSpeed = 0.01666666666 * 0.111111f;
    
public:
    virtual void start()
    {
        
    }
    
    virtual void update()
    {
        auto transform = this->getGameObject()->getTransform();
        transform->rotateZ(rotationSpeed);
    }
};
#endif