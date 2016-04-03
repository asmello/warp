#ifndef Renderer_hpp
#define Renderer_hpp

#include "GameObject.hpp"

#include <memory>

namespace warp
{
    class Renderer
    {
    protected:
        std::shared_ptr<GameObject> rootObject;
        
    public:
        virtual void draw() = 0;
        void setRootObject(std::shared_ptr<GameObject> rootObject);
        std::shared_ptr<GameObject> getRootObject();
    };
}

#endif /* Renderer_hpp */
