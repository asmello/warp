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
		std::shared_ptr<Scene> createFromFile(const std::string &filename, Object<Material>::ID material);
		std::shared_ptr<GameObject> createFromFile(const std::string &filename, Object<Material>::ID material, std::shared_ptr<Scene> scene);
        
    private:
        void loadNodeMeshes(const aiNode * pNode,
                            const aiScene * pScene,
                            std::shared_ptr<GameObject> node,
                            Object<Material>::ID materialID);
		std::shared_ptr<GameObject> loadHierarchy(const aiNode *pNode,
												   const aiScene *pScene,
												   std::shared_ptr<GameObject> node,
												   std::shared_ptr<Scene> scene,
												   Object<Material>::ID materialID);
    };
}

#endif /* SceneManager_hpp */
