#ifndef SceneInitializer_hpp
#define SceneInitializer_hpp

#include "MaterialManager.hpp"
#include "SkyboxRenderer.hpp"
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

#include "Behavior10.hpp"
#include "SceneManager.hpp"

#include <memory>
#include <string>
#include <vector>

class SceneInitializer
{
private:
	SceneInitializer() {}

public: 
	static void init(std::shared_ptr<warp::Scene> scene)
	{
		// These are resource managers
		auto shaderManager = warp::ShaderManager::getInstance();
		auto textureManager = warp::TextureManager::getInstance();
		auto materialManager = warp::MaterialManager::getInstance();
//		auto meshManager = warp::MeshManager::getInstance();

		// Create a camera object
		std::shared_ptr<warp::GameObject> go = scene->newGameObject();
		std::shared_ptr<warp::GameObject> go1 = scene->newGameObject();
		std::shared_ptr<warp::Camera> camera = go1->newComponent<warp::Camera>();
		camera->setPosition(glm::vec3(0, 2, 10));
		camera->lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		auto behavior = go1->newComponent<Behavior10>();
        Input::addListener(behavior);
		go1->getTransform()->setParent(go->getTransform());
		camera.reset();

		////////////
		// Lights //
		////////////

		/*
		Light testLight1 = Light(vec4(1.0, 0.054, 0.017, 1.0) * 200.0, vec4(-0.0, 80.0, 0.0, 0.0), vec4(0.0, 1.0, 0.1, 1.0));

		Light testLight2 = Light(vec4(1.0, 0.211, 0.008, 1.0) * 30.0, vec4(40.0, 14.0, 60.0, 0.0), vec4(0.0, 1.0, 0.1, 1.0));
		Light testLight3 = Light(vec4(1.0, 0.211, 0.008, 1.0) * 30.0, vec4(-40.0, 14.0, 60.0, 0.0), vec4(0.0, 1.0, 0.1, 1.0));
		Light testLight4 = Light(vec4(1.0, 0.211, 0.008, 1.0) * 30.0, vec4(40.0, 14.0, -60.0, 0.0), vec4(0.0, 1.0, 0.1, 1.0));
		Light testLight5 = Light(vec4(1.0, 0.211, 0.008, 1.0) * 30.0, vec4(-40.0, 14.0, -60.0, 0.0), vec4(0.0, 1.0, 0.1, 1.0));

		Light testLight6 = Light(vec4(1.0, 0.039, 0.009, 1.0) * 45.0, vec4(50.0, -20.0, 0.0, 0.0), vec4(0.0, 1.0, 0.1, 1.0));
		Light testLight7 = Light(vec4(1.0, 0.039, 0.009, 1.0) * 45.0, vec4(-50.0, -20.0, 0.0, 0.0), vec4(0.0, 1.0, 0.1, 1.0));
		*/

		// Create a directional light object
		go = scene->newGameObject();
		std::shared_ptr<warp::Light> light = go->newComponent<warp::Light>(warp::Light::Type::Directional);
		light->setColor(glm::vec3 (1.0* 200.0, 0.054* 200.0, 0.017* 200.0));
		light->setVector(glm::vec3(-0.0, 80.0, 0.0));
		light->setAttenuation(glm::vec4(0.0, 1.0, 0.1, 1.0));
		light.reset();
		go->getTransform()->translate(0, 0, 0);
        
        
        /////////////
        // Shaders //
        /////////////
        
        // Load a shader from file
        auto shaderID = shaderManager->createFromFile(util::resourcePath() + "vertex2.glsl", util::resourcePath() + "frag2.glsl");

		////////////////////////
		// SCENE CONSTRUCTION //
		////////////////////////

		auto noEmissionTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/BlackLight.png");
		auto noMetalicnessTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/BlackLight.png");

		std::vector<std::string> faces;
		faces.push_back(util::resourcePath() + "Skybox/Hell/right.png");
		faces.push_back(util::resourcePath() + "Skybox/Hell/left.png");
		faces.push_back(util::resourcePath() + "Skybox/Hell/top.png"); 
		faces.push_back(util::resourcePath() + "Skybox/Hell/bottom.png");
		faces.push_back(util::resourcePath() + "Skybox/Hell/back.png");
		faces.push_back(util::resourcePath() + "Skybox/Hell/front.png");
		auto cubemapID = textureManager->createCubemapFromFiles(faces);

		std::vector<std::string> faces2;
		faces2.push_back(util::resourcePath() + "Skybox/Hell/rightCM.png");
		faces2.push_back(util::resourcePath() + "Skybox/Hell/leftCM.png");
		faces2.push_back(util::resourcePath() + "Skybox/Hell/topCM.png");
		faces2.push_back(util::resourcePath() + "Skybox/Hell/bottomCM.png");
		faces2.push_back(util::resourcePath() + "Skybox/Hell/backCM.png");
		faces2.push_back(util::resourcePath() + "Skybox/Hell/frontCM.png");
		auto convolutedEM = textureManager->createCubemapFromFiles(faces2);

		//Floor

		// Load a texture from file
		auto colorTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/FloorTiles1.png");
		auto normalTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/FloorTiles1NM.png");
		auto emissionTextureID = noEmissionTextureID;

		// Create a material from shader and texture
		auto materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID, emissionTextureID, cubemapID, convolutedEM, noMetalicnessTextureID }), shaderID);

		auto go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "CatacombModels/FloorTiles_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(0.1, 0.1, 0.1);

		//Coin

		// Load a texture from file
		colorTextureID = textureManager->createFromFile(util::resourcePath() + "Logo_CLM.bmp");
		normalTextureID = textureManager->createFromFile(util::resourcePath() + "Logo_NRM.png");
		auto metalicTextureID = textureManager->createFromFile(util::resourcePath() + "Logo_MTL.png");
		emissionTextureID = noEmissionTextureID;

		// Create a material from shader and texture
		materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID, emissionTextureID, cubemapID, convolutedEM, metalicTextureID }), shaderID);

		go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "LogoLP_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(5.0, 5.0, 5.0);
		go3->getTransform()->rotateX (glm::pi<float>()*0.5);
		go3->getTransform()->translate (0.0, 20.0, 0.0);

		//LavaFall

		// Load a texture from file
		colorTextureID = noEmissionTextureID;
		normalTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/FlatTexture2NM.png");
		metalicTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/LavaFall_MTL.bmp");
		emissionTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/LavaFall_CLM.png");

		// Create a material from shader and texture
		materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID, emissionTextureID, cubemapID, convolutedEM, metalicTextureID }), shaderID);
		if (auto material = materialManager->get(materialID))
		{
			material->setSpeed (0.3);
		}

		go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "CatacombModels/AsLarvaDoVulcao_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(0.1, 0.1, 0.1);

		//Columns

		// Load a texture from file
		colorTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/Column2.png");
		normalTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/Column2NM.png");
		emissionTextureID = noEmissionTextureID;

		// Create a material from shader and texture
		materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID, emissionTextureID, cubemapID, convolutedEM, noMetalicnessTextureID }), shaderID);

		go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "CatacombModels/Column2_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(0.1, 0.1, 0.1);

		//Trims

		// Load a texture from file
		colorTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/Trims.png");
		normalTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/TrimsNM.png");
		emissionTextureID = noEmissionTextureID;

		// Create a material from shader and texture
		materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID, emissionTextureID, cubemapID, convolutedEM, noMetalicnessTextureID }), shaderID);

		go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "CatacombModels/Trims_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(0.1, 0.1, 0.1);

		//Gargoyle

		// Load a texture from file
		colorTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/Gargoyle.png");
		normalTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/GargoyleNM.png");
		emissionTextureID = noEmissionTextureID;

		// Create a material from shader and texture
		materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID, emissionTextureID, cubemapID, convolutedEM, noMetalicnessTextureID }), shaderID);

		go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "CatacombModels/Gargoyle_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(0.1, 0.1, 0.1);

		//DungeonWall

		// Load a texture from file
		colorTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/DungeonWall.png");
		normalTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/DungeonWallNM.png");
		emissionTextureID = noEmissionTextureID;

		// Create a material from shader and texture
		materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID, emissionTextureID, cubemapID, convolutedEM, noMetalicnessTextureID }), shaderID);

		go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "CatacombModels/DungeonWall_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(0.1, 0.1, 0.1);

		//Ceilling

		// Load a texture from file
		colorTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/Celling.png");
		normalTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/CellingNM.png");
		emissionTextureID = noEmissionTextureID;

		// Create a material from shader and texture
		materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID, emissionTextureID, cubemapID, convolutedEM, noMetalicnessTextureID }), shaderID);

		go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "CatacombModels/Ceiling_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(0.1, 0.1, 0.1);

		//Column3

		// Load a texture from file
		colorTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/Column3.png");
		normalTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/Column3NM.png");
		emissionTextureID = noEmissionTextureID;

		// Create a material from shader and texture
		materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID, emissionTextureID, cubemapID, convolutedEM, noMetalicnessTextureID }), shaderID);

		go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "CatacombModels/Column3_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(0.1, 0.1, 0.1);

		//Altar

		// Load a texture from file
		colorTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/Altar.png");
		normalTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/AltarNM.png");
		emissionTextureID = noEmissionTextureID;

		// Create a material from shader and texture
		materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID, emissionTextureID, cubemapID, convolutedEM, noMetalicnessTextureID }), shaderID);

		go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "CatacombModels/Altar_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(0.1, 0.1, 0.1);

		//Altar

		// Load a texture from file
		colorTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/AltarDeamon.png");
		normalTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/AltarDeamonNM.png");
		emissionTextureID = noEmissionTextureID;

		// Create a material from shader and texture
		materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID, emissionTextureID, cubemapID, convolutedEM, noMetalicnessTextureID }), shaderID);

		go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "CatacombModels/AltarStatues_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(0.1, 0.1, 0.1);

		//Atlas

		// Load a texture from file
		colorTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/AtlasTexture1.bmp");
		normalTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/AtlasTexture1NM.png");
		emissionTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/AtlasTexture1Light.png");

		// Create a material from shader and texture
		materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID, emissionTextureID, cubemapID, convolutedEM, noMetalicnessTextureID }), shaderID);

		go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "CatacombModels/Atlas_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(0.1, 0.1, 0.1);

		//Atlas2

		// Load a texture from file
		colorTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/AtlasTexture2.bmp");
		normalTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/AtlasTexture2NM.png");
		emissionTextureID = noEmissionTextureID;

		// Create a material from shader and texture
		materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID, emissionTextureID, cubemapID, convolutedEM, noMetalicnessTextureID }), shaderID);

		go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "CatacombModels/Atlas2_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(0.1, 0.1, 0.1);

		//Carvings

		// Load a texture from file
		colorTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/S_carvings.png");
		normalTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/S_carvingsNM.png");
		emissionTextureID = noEmissionTextureID;

		// Create a material from shader and texture
		materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID, emissionTextureID, cubemapID, convolutedEM, noMetalicnessTextureID }), shaderID);

		go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "CatacombModels/Carvings_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(0.1, 0.1, 0.1);

		//Cavern

		// Load a texture from file
		colorTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/CavernTexture_1.png");
		normalTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/CavernTexture_1NM.png");
		emissionTextureID = noEmissionTextureID;

		// Create a material from shader and texture
		materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID, emissionTextureID, cubemapID, convolutedEM, noMetalicnessTextureID }), shaderID);

		go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "CatacombModels/Cavern_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(0.1, 0.1, 0.1);

		//Flat

		// Load a texture from file
		colorTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/FlatTexture2.png");
		normalTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/FlatTexture2NM.png");
		emissionTextureID = noEmissionTextureID;

		// Create a material from shader and texture
		materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID, emissionTextureID, cubemapID, convolutedEM, noMetalicnessTextureID }), shaderID);

		go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "CatacombModels/FlatTexture2_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(0.1, 0.1, 0.1);

		//Lava

		// Load a texture from file
		colorTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/Lava.png");
		normalTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/LavaNM.png");
		emissionTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/LavaLight.png");

		// Create a material from shader and texture
		materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID, emissionTextureID, cubemapID, convolutedEM, noMetalicnessTextureID }), shaderID);
		if (auto material = materialManager->get(materialID))
		{
			material->setSpeed(0.1);
		}

		go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "CatacombModels/Lava_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(0.1, 0.1, 0.1);

		//Lava

		// Load a texture from file
		colorTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/StoneParts2.png");
		normalTextureID = textureManager->createFromFile(util::resourcePath() + "CatacombModels/Tex/StoneParts2.png");
		emissionTextureID = noEmissionTextureID;

		// Create a material from shader and texture
		materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID, emissionTextureID, cubemapID, convolutedEM, noMetalicnessTextureID }), shaderID);

		go3 = warp::SceneManager::getInstance()->createFromFile(util::resourcePath() + "CatacombModels/StoneParts_MDL.fbx", materialID, scene);
		go3->getTransform()->scale(0.1, 0.1, 0.1);
        
        ////////////
        // Skybox //
        ////////////
        
        // This uses a different shader
        auto skyshaderID = shaderManager->createFromFile(util::resourcePath() + "skybox_v.glsl", util::resourcePath() + "skybox_f.glsl");
        materialID = materialManager->create(cubemapID, skyshaderID);
        
        go3 = scene->newGameObject();
        go3->newComponent<SkyboxRenderer>(materialID);
        
        ///////////////////
        // SceneRenderer //
        ///////////////////
        
        std::shared_ptr<warp::SceneRenderer> sRenderer = scene->newComponent<warp::SceneRenderer>();
        sRenderer->init();
	}
};

#endif