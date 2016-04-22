#ifndef Renderer_hpp
#define Renderer_hpp

#include "Object.hpp"
#include "Component.hpp"

#include <vector>
#include <memory>

namespace warp
{
    class Light;
    class Camera;
    class Material;
    class GameObject;
    
    class Renderer : public Component, public Object<Renderer>
    {
    public:
        Renderer(Object<GameObject>::ID gameObject, Object<Material>::ID material);
        Renderer(Object<Material>::ID material);
		Object<GameObject>::ID getGameObjectID() const;
        virtual void render(Object<Camera>::ID cameraID, std::vector<Object<Light>::ID> lights) = 0;
        
    protected:
        Object<Material>::ID materialID;
        bool active;
    };
}

#endif /* Renderer_hpp */
