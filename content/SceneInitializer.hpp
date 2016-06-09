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
		std::shared_ptr<warp::GameObject> go = scene->newGameObject();
		std::shared_ptr<warp::GameObject> go1 = scene->newGameObject();
		std::shared_ptr<warp::Camera> camera = go1->newComponent<warp::Camera>();
		camera->setPosition(glm::vec3(0, 2, 10));
		camera->lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		go1->newComponent<Behaviour10>();
		go1->getTransform()->setParent(go->getTransform());
		camera.reset();

		////////////
		// Lights //
		////////////

		// Create a directional light object
		go = scene->newGameObject();
		std::shared_ptr<warp::Light> light = go->newComponent<warp::Light>(warp::Light::Type::Directional);
		light->setVector(glm::vec3(-0.15f, -0.1f, -0.9f));
		light->setColor(glm::vec3(1.0f, 1.0f, 0.93f));
		light.reset();
		go->getTransform()->translate(0, 0, 0);

		////////////////////////
		// SCENE CONSTRUCTION //
		////////////////////////

		//Floor
		// Load a shader from file
		auto shaderID = shaderManager->createFromFile(util::resourcePath() + "vertex2.glsl",
			util::resourcePath() + "frag2.glsl");

		// Load a texture from file
		auto colorTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/FloorTiles1.png");
		auto normalTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/FloorTiles1NM.png");

		// Create a material from shader and texture
		auto materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID }), shaderID);

		auto go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "CatacombModels/FloorTiles_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(0.1, 0.1, 0.1);

		//Columns
		// Load a shader from file
		shaderID = shaderManager->createFromFile(util::resourcePath() + "vertex2.glsl",
			util::resourcePath() + "frag2.glsl");

		// Load a texture from file
		colorTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/Column2.png");
		normalTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/Column2NM.png");

		// Create a material from shader and texture
		materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID }), shaderID);

		go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "CatacombModels/Column2_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(0.1, 0.1, 0.1);

		//Trims
		// Load a shader from file
		shaderID = shaderManager->createFromFile(util::resourcePath() + "vertex2.glsl",
			util::resourcePath() + "frag2.glsl");

		// Load a texture from file
		colorTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/Trims.png");
		normalTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/TrimsNM.png");

		// Create a material from shader and texture
		materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID }), shaderID);

		go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "CatacombModels/Trims_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(0.1, 0.1, 0.1);

		//Gargoyle
		// Load a shader from file
		shaderID = shaderManager->createFromFile(util::resourcePath() + "vertex2.glsl",
			util::resourcePath() + "frag2.glsl");

		// Load a texture from file
		colorTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/Gargoyle.png");
		normalTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/GargoyleNM.png");

		// Create a material from shader and texture
		materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID }), shaderID);

		go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "CatacombModels/Gargoyle_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(0.1, 0.1, 0.1);

		//DungeonWall
		// Load a shader from file
		shaderID = shaderManager->createFromFile(util::resourcePath() + "vertex2.glsl",
			util::resourcePath() + "frag2.glsl");

		// Load a texture from file
		colorTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/DungeonWall.png");
		normalTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/DungeonWallNM.png");

		// Create a material from shader and texture
		materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID }), shaderID);

		go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "CatacombModels/DungeonWall_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(0.1, 0.1, 0.1);

		//Ceilling
		// Load a shader from file
		shaderID = shaderManager->createFromFile(util::resourcePath() + "vertex2.glsl",
			util::resourcePath() + "frag2.glsl");

		// Load a texture from file
		colorTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/Celling.png");
		normalTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/CellingNM.png");

		// Create a material from shader and texture
		materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID }), shaderID);

		go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "CatacombModels/Ceiling_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(0.1, 0.1, 0.1);

		//Column3
		// Load a shader from file
		shaderID = shaderManager->createFromFile(util::resourcePath() + "vertex2.glsl",
			util::resourcePath() + "frag2.glsl");

		// Load a texture from file
		colorTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/Column3.png");
		normalTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/Column3NM.png");

		// Create a material from shader and texture
		materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID }), shaderID);

		go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "CatacombModels/Column3_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(0.1, 0.1, 0.1);

		//Altar
		// Load a shader from file
		shaderID = shaderManager->createFromFile(util::resourcePath() + "vertex2.glsl",
			util::resourcePath() + "frag2.glsl");

		// Load a texture from file
		colorTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/Altar.png");
		normalTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/AltarNM.png");

		// Create a material from shader and texture
		materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID }), shaderID);

		go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "CatacombModels/Altar_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(0.1, 0.1, 0.1);

		//Altar
		// Load a shader from file
		shaderID = shaderManager->createFromFile(util::resourcePath() + "vertex2.glsl",
			util::resourcePath() + "frag2.glsl");

		// Load a texture from file
		colorTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/AltarDeamon.png");
		normalTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/AltarDeamonNM.png");

		// Create a material from shader and texture
		materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID }), shaderID);

		go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "CatacombModels/AltarStatues_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(0.1, 0.1, 0.1);

		//Atlas
		// Load a shader from file
		shaderID = shaderManager->createFromFile(util::resourcePath() + "vertex2.glsl",
			util::resourcePath() + "frag2.glsl");

		// Load a texture from file
		colorTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/AtlasTexture1.png");
		normalTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/AtlasTexture1NM.png");

		// Create a material from shader and texture
		materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID }), shaderID);

		go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "CatacombModels/Atlas_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(0.1, 0.1, 0.1);

		//Atlas2
		// Load a shader from file
		shaderID = shaderManager->createFromFile(util::resourcePath() + "vertex2.glsl",
			util::resourcePath() + "frag2.glsl");

		// Load a texture from file
		colorTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/AtlasTexture2.png");
		normalTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/AtlasTexture2NM.png");

		// Create a material from shader and texture
		materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID }), shaderID);

		go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "CatacombModels/Atlas2_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(0.1, 0.1, 0.1);

		//Carvings
		// Load a shader from file
		shaderID = shaderManager->createFromFile(util::resourcePath() + "vertex2.glsl",
			util::resourcePath() + "frag2.glsl");

		// Load a texture from file
		colorTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/S_carvings.png");
		normalTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/S_carvingsNM.png");

		// Create a material from shader and texture
		materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID }), shaderID);

		go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "CatacombModels/Carvings_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(0.1, 0.1, 0.1);

		//Cavern
		// Load a shader from file
		shaderID = shaderManager->createFromFile(util::resourcePath() + "vertex2.glsl",
			util::resourcePath() + "frag2.glsl");

		// Load a texture from file
		colorTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/CavernTexture_1.png");
		normalTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/CavernTexture_1NM.png");

		// Create a material from shader and texture
		materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID }), shaderID);

		go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "CatacombModels/Cavern_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(0.1, 0.1, 0.1);

		//Flat
		// Load a shader from file
		shaderID = shaderManager->createFromFile(util::resourcePath() + "vertex2.glsl",
			util::resourcePath() + "frag2.glsl");

		// Load a texture from file
		colorTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/FlatTexture2.png");
		normalTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/FlatTexture2NM.png");

		// Create a material from shader and texture
		materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID }), shaderID);

		go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "CatacombModels/FlatTexture2_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(0.1, 0.1, 0.1);

		//Lava
		// Load a shader from file
		shaderID = shaderManager->createFromFile(util::resourcePath() + "vertex2.glsl",
			util::resourcePath() + "frag2.glsl");

		// Load a texture from file
		colorTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/Lava.png");
		normalTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/LavaNM.png");

		// Create a material from shader and texture
		materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID }), shaderID);

		go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "CatacombModels/Lava_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(0.1, 0.1, 0.1);

		//Lava
		// Load a shader from file
		shaderID = shaderManager->createFromFile(util::resourcePath() + "vertex2.glsl",
			util::resourcePath() + "frag2.glsl");

		// Load a texture from file
		colorTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/StoneParts2.png");
		normalTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/StoneParts2.png");

		// Create a material from shader and texture
		materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID }), shaderID);

		go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "CatacombModels/StoneParts_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(0.1, 0.1, 0.1);



		
	}
};

#endif