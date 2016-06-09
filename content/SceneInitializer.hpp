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
#include "Behaviour10.hpp"
#include "SceneManager.hpp"


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


		// Create a camera object
		std::shared_ptr<warp::GameObject> go1 = scene->newGameObject();
		std::shared_ptr<warp::Camera> camera = go1->newComponent<warp::Camera>();
		camera->setPosition(glm::vec3(0, 0, 3));
		camera->lookAt(glm::vec3(1, 2, 0), glm::vec3(0, 1, 0));
		go1->newComponent<Behaviour10>();
		camera.reset();

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
	/*	auto meshID = meshManager->create();
		if (std::shared_ptr<warp::Mesh> squareMesh = meshManager->get(meshID))
		{
			squareMesh->setVertices({
				-0.5f, -0.5f, -0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
				-0.5f, 0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
				0.5f, -0.5f, -0.0f,    0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
				0.5f, 0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f
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
		go->newComponent<Behaviour1>();

		auto go5 = scene->newGameObject();
		go->getTransform()->setParent(go5->getTransform());*/

		auto go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "Gecko.fbx", materialID, scene);
		go3->getTransform()->scale(1, 1, 1);

		
	}
};

#endif