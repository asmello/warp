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
#include "Scene.hpp"
#include "Transform.hpp"
#include "MeshRenderer.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "util.hpp"

using namespace warp;

void SceneManager::loadNodeMeshes(const aiNode * pNode,
                                  const aiScene * pScene,
                                  std::shared_ptr<GameObject> node,
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
                
                const aiVector3D& pTangent = paiMesh->HasTangentsAndBitangents() ? paiMesh->mTangents[j] : Zero3D;
                mesh->vertices.push_back(pTangent.x);
                mesh->vertices.push_back(pTangent.y);
                mesh->vertices.push_back(pTangent.z);
                
                const aiVector3D& pTexCoord = paiMesh->HasTextureCoords(0) ? paiMesh->mTextureCoords[0][j] : Zero3D;
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
        
        node->newComponent<MeshRenderer>(materialID, meshID);
    }
}

std::shared_ptr<GameObject> SceneManager::loadHierarchy(const aiNode *pNode,
														 const aiScene *pScene,
														 std::shared_ptr<GameObject> node,
														 std::shared_ptr<Scene> scene,
														 Material::ID materialID)
{
    auto newNode = scene->newGameObject();
    newNode->getTransform()->setTransformation(pNode->mTransformation);
    newNode->getTransform()->setParent(node->getTransform());
    
    loadNodeMeshes(pNode, pScene, newNode, materialID);
    for (size_t i = 0; i < pNode->mNumChildren; ++i)
    {
        loadHierarchy(pNode->mChildren[i], pScene, newNode, scene, materialID);
    }

	return newNode;
}

std::shared_ptr<warp::Scene> SceneManager::createFromFile(const std::string &filename, Material::ID material)
{
    Assimp::Importer importer;
    
    const aiScene* pScene = importer.ReadFile(filename.c_str(),
                                              aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    
    if (pScene) {
        auto scene = Scene::newScene();
        loadHierarchy(pScene->mRootNode, pScene, scene, scene, material);
        return scene;
    }
    else {
        fprintf(stderr, "Error parsing '%s': '%s'\n", filename.c_str(), importer.GetErrorString());
        return nullptr;
    }
}






std::shared_ptr<GameObject> SceneManager::createFromFile(const std::string &filename, Object<Material>::ID material, std::shared_ptr<warp::Scene> scene)
{
	Assimp::Importer importer;

	const aiScene* pScene = importer.ReadFile(filename.c_str(),
		aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if (pScene) {
		return loadHierarchy(pScene->mRootNode, pScene, scene, scene, material);
	}
	else {
		fprintf(stderr, "Error parsing '%s': '%s'\n", filename.c_str(), importer.GetErrorString());
		return nullptr;
	}
}