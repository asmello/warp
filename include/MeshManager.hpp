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
        Mesh::ID create();
        void setActive(MeshID id);
        Mesh::ID add(std::shared_ptr<Mesh> mesh);
        std::shared_ptr<Mesh> get(Mesh::ID id);
        
    private:
        std::vector<std::shared_ptr<Mesh>> meshes;
        Mesh::ID activeID;
    };
}

#endif /* MeshManager_hpp */
