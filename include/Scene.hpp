#ifndef Scene_hpp
#define Scene_hpp

#include "GameObject.hpp"

#include <vector>
#include <memory>

namespace warp
{
    class Scene : public GameObject, public std::enable_shared_from_this<Scene>
    {
        friend class GameObject;
        
    private:
        template <class T> void addComponent(std::shared_ptr<T> component)
        {
            components.insert(component->type_code, component);
        }
        
    protected:
        std::shared_ptr<Scene> getScene();
        
    public:
        
        
    };
}

#endif /* Scene_hpp */
