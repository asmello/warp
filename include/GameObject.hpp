#ifndef GameObject_hpp
#define GameObject_hpp

#include "Transform.hpp"

#include <memory>

namespace warp
{
    class GameObject
    {
    protected:
        std::shared_ptr<Transform> transform;
        
    public:
        GameObject();
        GameObject(std::unique_ptr<Transform> transform);
        std::shared_ptr<Transform> getTransform() const;
    };
}

#endif /* GameObject_hpp */
