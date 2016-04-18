#ifndef SceneManager_hpp
#define SceneManager_hpp

#include "Object.hpp"
#include "Singleton.hpp"
#include "ResourceManager.hpp"

#include <assimp/scene.h>

namespace warp
{
    class Scene;
    class Transform;
    class GameObject;
    class Material;
    
    class SceneManager : public ResourceManager<Scene>, public Singleton<SceneManager>
    {
    public:
        Object<Scene>::ID createFromFile(const std::string &filename);
        
    private:
        void loadNodeMeshes(const aiNode * pNode,
                            const aiScene * pScene,
                            std::shared_ptr<Scene> scene,
                            Object<GameObject>::ID gameObjectID,
                            Object<Material>::ID materialID);
        void loadHierarchy(const aiNode *pNode,
                           const aiScene *pScene,
                           std::shared_ptr<Scene> scene,
                           std::shared_ptr<Transform> parentTransform,
                           Object<Material>::ID materialID);
    };
}

#endif /* SceneManager_hpp */
