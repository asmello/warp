#ifndef MeshManager_hpp
#define MeshManager_hpp

#include "Singleton.hpp"
#include "ResourceManager.hpp"

namespace warp
{
    class Mesh;

    class MeshManager : public ResourceManager<Mesh>, public Singleton<MeshManager>
    {
    public:
        void setActive(Object<Mesh>::ID id);

    private:
        Object<Mesh>::ID activeID;
    };
}

#endif /* MeshManager_hpp */
