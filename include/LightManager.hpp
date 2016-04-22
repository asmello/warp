#ifndef LightManager_hpp
#define LightManager_hpp

#include "Object.hpp"
#include "Singleton.hpp"
#include "ResourceManager.hpp"

namespace warp
{
    class Light;
    
    class LightManager : public ResourceManager<Light>, public Singleton<LightManager>
    {
    public:
        template <class T, typename... Args>
        typename Object<Light>::ID create(Args&&... args)
        {
            auto resource = std::make_shared<T>(args...);
            resources.push_back(resource);
            return resource->setID(resources.size() - 1);
        }
        
        void setActive(Object<Light>::ID id);
    };
}

#endif /* LightManager_hpp */
