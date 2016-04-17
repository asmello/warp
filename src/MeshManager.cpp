#include "MeshManager.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "TextureManager.hpp"

#include "util.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

using namespace warp;

void MeshManager::setActive(Mesh::ID id)
{
//    if (activeID == id) return;
    activeID = id;
}

void MeshManager::initMeshFromScene(const aiScene *aiScene, std::shared_ptr<Mesh> mesh)
{
    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
    
    for (size_t i = 0; i < aiScene->mNumMeshes; ++i)
    {
        const aiMesh* paiMesh = aiScene->mMeshes[i];
        
        auto entry = std::make_shared<Mesh::MeshEntry>();
        entry->textureID = Texture::ID(paiMesh->mMaterialIndex);
        
        for (size_t j = 0; j < paiMesh->mNumVertices; ++j)
        {
            const aiVector3D* pPos = &paiMesh->mVertices[j];
            entry->vertices.push_back(pPos->x);
            entry->vertices.push_back(pPos->y);
            entry->vertices.push_back(pPos->z);
            
            const aiVector3D* pNormal = &paiMesh->mNormals[j];
            entry->vertices.push_back(pNormal->x);
            entry->vertices.push_back(pNormal->y);
            entry->vertices.push_back(pNormal->z);
            
            const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &paiMesh->mTextureCoords[0][i] : &Zero3D;
            entry->vertices.push_back(pTexCoord->x);
            entry->vertices.push_back(pTexCoord->y);
        }
        
        for (size_t j = 0 ; j < paiMesh->mNumFaces; ++j)
        {
            const aiFace& Face = paiMesh->mFaces[j];
            assert(Face.mNumIndices == 3);
            entry->elements.push_back(Face.mIndices[0]);
            entry->elements.push_back(Face.mIndices[1]);
            entry->elements.push_back(Face.mIndices[2]);
        }
        
        entry->load();
        
        mesh->addEntry(entry);
    }
}

void MeshManager::initMeshTexturesFromScene(const aiScene *aiScene, std::shared_ptr<Mesh> mesh)
{
    for (size_t i = 0; i < aiScene->mNumMaterials; ++i)
    {
        const aiMaterial* pMaterial = aiScene->mMaterials[i];
        
        if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
        {
            aiString Path;
            
            if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
            {
                // TextureManager should handle the case where the file does not exist...
                mesh->textures[i] = TextureManager::getInstance()->createFromFile(Path.data);
            }
        }
    }
}


Mesh::ID MeshManager::loadFromFile(const std::string &filename)
{
    Assimp::Importer importer;
    
    const aiScene* pScene = importer.ReadFile(filename.c_str(),
                                              aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
    
    if (pScene) {
        auto mesh = std::make_shared<Mesh>();
        initMeshFromScene(pScene, mesh);
        initMeshTexturesFromScene(pScene, mesh);
        resources.push_back(mesh);
        return Mesh::ID(resources.size()-1);
    }
    else {
        fprintf(stderr, "Error parsing '%s': '%s'\n", filename.c_str(), importer.GetErrorString());
        return Mesh::ID(-1);
    }
}