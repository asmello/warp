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
        void loadSceneNode(const aiNode *pNode, const aiScene* pScene);

    private:
        Object<Mesh>::ID activeID;
    };
}

#endif /* MeshManager_hpp */
