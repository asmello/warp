#include "SceneManager.hpp"
#include "Scene.hpp"

#include "Mesh.hpp"
#include "MeshManager.hpp"
#include "Texture.hpp"
#include "TextureManager.hpp"
#include "Material.hpp"
#include "MaterialManager.hpp"
#include "Shader.hpp"
#include "ShaderManager.hpp"
#include "GameObject.hpp"
#include "GameObjectManager.hpp"
#include "Transform.hpp"
#include "MeshRenderer.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "util.hpp"

using namespace warp;

void SceneManager::loadNodeMeshes(const aiNode * pNode,
                                  const aiScene * pScene,
                                  std::shared_ptr<Scene> scene,
                                  GameObject::ID gameObjectID,
                                  Material::ID materialID)
{
    MeshManager * meshManager = MeshManager::getInstance();
    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
    
    for (size_t i = 0; i < pNode->mNumMeshes; ++i)
    {
        const aiMesh* paiMesh = pScene->mMeshes[pNode->mMeshes[i]];
        
        Mesh::ID meshID = meshManager->create();
        
        if (std::shared_ptr<Mesh> mesh = meshManager->get(meshID))
        {
            for (size_t j = 0; j < paiMesh->mNumVertices; ++j)
            {
                const aiVector3D& pPos = paiMesh->mVertices[j];
                mesh->vertices.push_back(pPos.x);
                mesh->vertices.push_back(pPos.y);
                mesh->vertices.push_back(pPos.z);
                
                const aiVector3D& pNormal = paiMesh->mNormals[j];
                mesh->vertices.push_back(pNormal.x);
                mesh->vertices.push_back(pNormal.y);
                mesh->vertices.push_back(pNormal.z);
                
                const aiVector3D& pTexCoord = paiMesh->HasTextureCoords(0) ? paiMesh->mTextureCoords[0][i] : Zero3D;
                mesh->vertices.push_back(pTexCoord.x);
                mesh->vertices.push_back(pTexCoord.y);
            }
            
            for (size_t j = 0 ; j < paiMesh->mNumFaces; ++j)
            {
                const aiFace& Face = paiMesh->mFaces[j];
                assert(Face.mNumIndices == 3);
                mesh->elements.push_back(Face.mIndices[0]);
                mesh->elements.push_back(Face.mIndices[1]);
                mesh->elements.push_back(Face.mIndices[2]);
            }
            
            mesh->load();
        }
        
        scene->renderers.push_back(std::make_shared<MeshRenderer>(gameObjectID, materialID, meshID));
    }
}

void SceneManager::loadHierarchy(const aiNode *pNode,
                                 const aiScene *pScene,
                                 std::shared_ptr<Scene> scene,
                                 std::shared_ptr<Transform> parentTransform,
                                 Material::ID materialID)
{
    auto transform = std::make_shared<Transform>(pNode->mTransformation);

    if (parentTransform != nullptr) {
        transform->setParent(parentTransform);
    }
    
    GameObject::ID gameObjectID = GameObjectManager::getInstance()->create(transform);
    
    loadNodeMeshes(pNode, pScene, scene, gameObjectID, materialID);
    
    for (size_t i = 0; i < pNode->mNumChildren; ++i)
    {
        loadHierarchy(pNode->mChildren[i], pScene, scene, transform, materialID);
    }
}

Scene::ID SceneManager::createFromFile(const std::string &filename)
{
    Assimp::Importer importer;
    
    const aiScene* pScene = importer.ReadFile(filename.c_str(),
                                              aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
    
    if (pScene) {
        auto shaderID = ShaderManager::getInstance()->createFromFile(util::resourcePath() + "vertex.glsl",
                                                                     util::resourcePath() + "frag.glsl");
        auto steveTextureID = TextureManager::getInstance()->createFromFile(util::resourcePath() + "Steeve_CLM.png");
        auto steveMaterialID = MaterialManager::getInstance()->create(steveTextureID, shaderID);
        
        auto scene = std::make_shared<Scene>();
        loadHierarchy(pScene->mRootNode, pScene, scene, nullptr, steveMaterialID);
        resources.push_back(scene);
        return Scene::ID(resources.size()-1);
    }
    else {
        fprintf(stderr, "Error parsing '%s': '%s'\n", filename.c_str(), importer.GetErrorString());
        return Scene::ID(-1);
    }
}