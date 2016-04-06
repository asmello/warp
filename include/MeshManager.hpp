#ifndef MeshManager_hpp
#define MeshManager_hpp

#include "Singleton.hpp"
#include "Mesh.hpp"

#include <memory>

namespace warp
{
    class MeshManager : public Singleton<MeshManager>
    {
    public:
        using ID = int;
        
        ID create();
        ID add(std::shared_ptr<Mesh> mesh);
        std::weak_ptr<Mesh> get(ID id);
    };
}

#endif /* MeshManager_hpp */
