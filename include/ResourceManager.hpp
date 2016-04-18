#ifndef ResourceManager_hpp
#define ResourceManager_hpp

#include "Object.hpp"

#include <vector>
#include <memory>

namespace warp
{
    template <class RType>
    class ResourceManager
    {
    public:
        std::shared_ptr<RType> get(typename Object<RType>::ID id)
        {
            return resources.at(static_cast<size_t>(id));
        }
        
        typename Object<RType>::ID add(std::shared_ptr<RType> resource)
        {
            resources.push_back(resource);
            return resource->setID(resources.size()-1);
        }
        
        template <typename... Args>
        typename Object<RType>::ID create(Args&&... args)
        {
            auto resource = std::make_shared<RType>(args...);
            resources.push_back(resource);
            return resource->setID(resources.size() - 1);
        }
        
        template <typename... Args>
        typename std::shared_ptr<RType> getNew(Args&&... args)
        {
            auto resource = std::make_shared<RType>(args...);
            resources.push_back(resource);
            return resource;
        }
        
    protected:
        std::vector<std::shared_ptr<RType>> resources;
    };
}

#endif /* ResourceManager_hpp */
