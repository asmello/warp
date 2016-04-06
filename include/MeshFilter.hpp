#ifndef MeshFilter_hpp
#define MeshFilter_hpp

#include "Mesh.hpp"

#include <memory>

namespace warp
{
    class MeshFilter : public Component
    {
    private:
        std::shared_ptr<Mesh> mesh;
        
    public:
        MeshFilter(std::shared_ptr<Mesh> mesh);
        void setMesh(std::shared_ptr<Mesh> mesh);
        std::shared_ptr<Mesh> getMesh();
    };
}

#endif /* MeshFilter_hpp */
