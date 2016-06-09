#ifndef SceneInitializer_hpp
#define SceneInitializer_hpp

#include <memory>

#include <vector>


#include "MaterialManager.hpp"
#include "TextureManager.hpp"
#include "ShaderManager.hpp"
#include "SceneRenderer.hpp"
#include "MeshRenderer.hpp"
#include "MeshManager.hpp"
#include "Transform.hpp"
#include "GameLoop.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "Input.hpp"
#include "Scene.hpp"
#include "Light.hpp"
#include "Mesh.hpp"
#include "util.hpp"

#include "Behaviour1.hpp"


class SceneInitializer
{
private:
	SceneInitializer() {}

public: 
	static void Init(std::shared_ptr<warp::Scene> scene)
	{
		// These are resource managers
		auto shaderManager = warp::ShaderManager::getInstance();
		auto textureManager = warp::TextureManager::getInstance();
		auto materialManager = warp::MaterialManager::getInstance();
		auto meshManager = warp::MeshManager::getInstance();

		////////////
		// Lights //
		////////////

		// Create a directional light object
		auto go2 = scene->newGameObject();
		std::shared_ptr<warp::Light> light = go2->newComponent<warp::Light>(warp::Light::Type::Directional);
		light->setVector(glm::vec3(-0.15f, -0.1f, -0.9f));
		light->setColor(glm::vec3(1.0f, 1.0f, 0.93f));
		light.reset();

		////////////////////////
		// SCENE CONSTRUCTION //
		////////////////////////

		// Load a shader from file
		auto shaderID = shaderManager->createFromFile(util::resourcePath() + "vertex2.glsl",
			util::resourcePath() + "frag2.glsl");

		// Load a texture from file
		auto colorTextureID = textureManager->createFromFile(util::resourcePath() + "Logo_CLM.bmp");
		auto normalTextureID = textureManager->createFromFile(util::resourcePath() + "Logo_NRM.png");

		// Create a material from shader and texture
		auto materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID }), shaderID);

		// Create a mesh representation
		auto meshID = meshManager->create();
		if (std::shared_ptr<warp::Mesh> squareMesh = meshManager->get(meshID))
		{
			squareMesh->setVertices({
				-0.5f, 0.0f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
				-0.5f, 0.0f, 0.5f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
				0.5f, 0.0f, 0.5f,    0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
				0.5f, 0.0f, -0.5f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f
			});
			squareMesh->setElements({
				0, 2, 1,
				2, 3, 1
			});
			squareMesh->load();
		}
		else
		{
			std::cout << "erro!!!";
		}

		// Create a GameObject
		auto go = scene->newGameObject();
		go->newComponent<warp::MeshRenderer>(materialID, meshID);
		go->getTransform()->scale(10, 10, 10);
		go->getTransform()->translate(0, -1, 0);
		go->newComponent<Behaviour1>();

		util::printMat4(go->getTransform()->getTransformation());
	}
};

#endif