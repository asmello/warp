#ifndef MeshManager_hpp
#define MeshManager_hpp

#include "Identifier.hpp"
#include "Singleton.hpp"
#include "Mesh.hpp"

#include <vector>
#include <memory>

namespace warp
{
    struct mesh_tag{}; // Magic strong typedefness
    typedef Identifier<mesh_tag, int, -1> MeshID;
    
    class MeshManager : public Singleton<MeshManager>
    {
    public:
        MeshID create();
        void setActive(MeshID id);
        MeshID add(std::shared_ptr<Mesh> mesh);
        std::shared_ptr<Mesh> get(MeshID id);
        
    private:
        std::vector<std::shared_ptr<Mesh>> meshes;
        MeshID activeID;
    };
}

#endif /* MeshManager_hpp */
