#ifndef MeshManager_hpp
#define MeshManager_hpp

#include "ResourceManager.hpp"

namespace warp
{
    class Mesh;

    class MeshManager : public ResourceManager<Mesh>
    {
    public:
        void setActive(Object<Mesh>::ID id);

    private:
        Object<Mesh>::ID activeID;
    };
}

#endif /* MeshManager_hpp */
