#ifndef MeshManager_hpp
#define MeshManager_hpp

#include "Singleton.hpp"
#include "ResourceManager.hpp"

#include <assimp/scene.h>

namespace warp
{
    class Mesh;

    class MeshManager : public ResourceManager<Mesh>, public Singleton<MeshManager>
    {
    public:
        void setActive(Object<Mesh>::ID id);
        Object<Mesh>::ID loadFromFile(const std::string& filename);

    private:
        Object<Mesh>::ID activeID;
        void initFromScene(const aiScene *scene, std::shared_ptr<Mesh> mesh);
    };
}

#endif /* MeshManager_hpp */
