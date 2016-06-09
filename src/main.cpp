#include <GL/glew.h>

#include <SFML/Window.hpp>

#include <memory>

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

#include "SceneInitializer.hpp"
#include "SceneManager.hpp"
#include "Behaviour10.hpp"



int main(int, char const**)
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.majorVersion = 4;
    settings.minorVersion = 1;
    settings.antialiasingLevel = 4;
    settings.attributeFlags = sf::ContextSettings::Core;
    
    auto window = std::make_shared<sf::Window>(sf::VideoMode(800, 800, 32), "Warp",
                                               sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize,
                                               settings);
    window->setVerticalSyncEnabled(true);
    
    warp::Input windowInput(window);
    
    glewExperimental = GL_TRUE;
    glewInit();
    glGetError(); // Discard error 500

	// Create the scene object
	std::shared_ptr<warp::Scene> scene = warp::Scene::newScene();
	std::shared_ptr<warp::SceneRenderer> sRenderer = scene->newComponent<warp::SceneRenderer>();

	// These are resource managers
	auto shaderManager = warp::ShaderManager::getInstance();
	auto textureManager = warp::TextureManager::getInstance();
	auto materialManager = warp::MaterialManager::getInstance();
	auto meshManager = warp::MeshManager::getInstance();

	// Populating scene
	SceneInitializer::Init(scene);

	
// These are resource managers
	/*auto shaderManager = warp::ShaderManager::getInstance();
	auto textureManager = warp::TextureManager::getInstance();
	auto materialManager = warp::MaterialManager::getInstance();
	auto meshManager = warp::MeshManager::getInstance();
	auto sm = warp::SceneManager::getInstance();


	// Load a shader from file
	auto shaderID = shaderManager->createFromFile(util::resourcePath() + "vertex2.glsl",
		util::resourcePath() + "frag2.glsl");

	// Load a texture from file
	auto colorTextureID = textureManager->createFromFile(util::resourcePath() + "Logo_CLM.bmp");
	auto normalTextureID = textureManager->createFromFile(util::resourcePath() + "Logo_NRM.png");

	// Create a material from shader and texture
	auto materialID = materialManager->create(std::vector<warp::Texture::ID>({ colorTextureID, normalTextureID }), shaderID);


	std::shared_ptr<warp::Scene> scene = sm->createFromFile(util::resourcePath() + "LogoLP_MDL.fbx", materialID);
	std::shared_ptr<warp::SceneRenderer> sRenderer = scene->newComponent<warp::SceneRenderer>();

//	scene->getTransform()->scale(0.015); // TODO [Pau???]
//	scene->getTransform()->rotate(-90, 0, 1, 0);
//	scene->getTransform()->translate(0, -1.25, 0);
	


	// Create a directional light object
	auto go2 = scene->newGameObject();
	std::shared_ptr<warp::Light> light = go2->newComponent<warp::Light>(warp::Light::Type::Directional);
	light->setVector(glm::vec3(-0.15f, -0.1f, -0.9f));
	light->setColor(glm::vec3(1.0f, 1.0f, 0.93f));
	light.reset();

	// Create a camera object
	std::shared_ptr<warp::GameObject> go1 = scene->newGameObject();
	std::shared_ptr<warp::Camera> camera = go1->newComponent<warp::Camera>();
	camera->setPosition(glm::vec3(0, 0, 5));
	camera->lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	camera.reset();*/
	



    // Initialize rendering context
    sRenderer->init();
    
    // The scene renderer will listen to window events
    windowInput.addListener(sRenderer);
    
	// Start scene behaviour
	scene->Behaviour_Start();

    // This is the main loop
    auto loop = std::make_shared<warp::GameLoop>(
    [&windowInput, sRenderer, window, scene]()
    {
        // Process window events
        windowInput.flush();
        
		// Update scene behaviour
		scene->Behaviour_Update();
        
        // Draw the scene
        sRenderer->render();
        
        // Swap buffers
        window->display();
    });
    windowInput.addListener(loop);
    
    loop->run();
    
    window->close();

    return EXIT_SUCCESS;
}

