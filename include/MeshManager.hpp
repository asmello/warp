#ifndef MeshManager_hpp
#define MeshManager_hpp

#include "Singleton.hpp"
#include "Mesh.hpp"

#include <vector>
#include <memory>

namespace warp
{
    class MeshManager : public Singleton<MeshManager>
    {
    public:
        using ID = int;
        
        ID create();
        void setActive(ID id);
        ID add(std::shared_ptr<Mesh> mesh);
        std::shared_ptr<Mesh> get(ID id);
        
    private:
        std::vector<std::shared_ptr<Mesh>> meshes;
        ID activeID;
    };
}

#endif /* MeshManager_hpp */
