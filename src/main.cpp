#include <GL/glew.h>

#include <SFML/Window.hpp>

#include <memory>

#include "GameObjectManager.hpp"
#include "DirectionalLight.hpp"
#include "MaterialManager.hpp"
#include "TextureManager.hpp"
#include "ShaderManager.hpp"
#include "SceneRenderer.hpp"
#include "LightManager.hpp"
#include "SceneManager.hpp"
#include "MeshRenderer.hpp"
#include "MeshManager.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"
#include "GameLoop.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "Input.hpp"
#include "Scene.hpp"
#include "Mesh.hpp"
#include "util.hpp"

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
    
    auto gameObjectManager = warp::GameObjectManager::getInstance();
    auto shaderManager = warp::ShaderManager::getInstance();
    auto textureManager = warp::TextureManager::getInstance();
    auto materialManager = warp::MaterialManager::getInstance();
//    auto meshManager = warp::MeshManager::getInstance();
    auto cameraManager = warp::CameraManager::getInstance();
    auto sceneManager = warp::SceneManager::getInstance();
    auto lightManager = warp::LightManager::getInstance();
    
    auto cameraID = cameraManager->create();
    if (std::shared_ptr<warp::Camera> camera = cameraManager->get(cameraID))
    {
        camera->setPosition(glm::vec3(0, 5, 0));
        camera->lookAt(glm::vec3(0,0,0), glm::vec3(0,0,1));
    }
    
    auto sunID = lightManager->create<warp::DirectionalLight>();
    if (std::shared_ptr<warp::DirectionalLight> sun = std::dynamic_pointer_cast<warp::DirectionalLight>(lightManager->get(sunID)))
    {
        sun->setIntensity(1.0f);
        sun->setDirection(glm::vec3(-0.15f, -0.1f, -0.9f));
        sun->setColor(glm::vec3(1.0f, 1.0f, 0.93f));
    }
    
//    auto steveShaderID = shaderManager->createFromFile(util::resourcePath() + "vertex.glsl", util::resourcePath() + "frag.glsl");
//    auto steveTextureID = textureManager->createFromFile(util::resourcePath() + "Steeve_CLM.png");
//    auto steveMaterialID = materialManager->create(steveTextureID, steveShaderID);
//    
//    // Create the Steeve scene object
//    warp::Scene::ID steveSceneID = sceneManager->createFromFile(util::resourcePath() + "Steeve.fbx", steveMaterialID);
//    
//    // Adjust Steeve
//    if (std::shared_ptr<warp::GameObject> rootObject = gameObjectManager->get(warp::GameObject::ID(1)))
//    {
//        rootObject->getTransform()->scale(0.015);
//        rootObject->getTransform()->rotate(-90, 0, 1, 0);
//        rootObject->getTransform()->translate(0, -1.25, 0);
//    }
//    
//    if (std::shared_ptr<warp::Scene> scene = sceneManager->get(steveSceneID))
//    {
//        scene->addCamera(cameraID);
//    }
    
    auto coinShaderID = shaderManager->createFromFile(util::resourcePath() + "vertex2.glsl", util::resourcePath() + "frag2.glsl");
    auto coinColorTextureID = textureManager->createFromFile(util::resourcePath() + "Logo_CLM.bmp");
    auto coinNormalTextureID = textureManager->createFromFile(util::resourcePath() + "Logo_NRM.png");
	auto coinMaterialID = materialManager->create(std::vector<warp::Texture::ID>({ coinColorTextureID, coinNormalTextureID }), coinShaderID);
    
    // Create the Coin scene object
    warp::Scene::ID coinSceneID = sceneManager->createFromFile(util::resourcePath() + "LogoLP_MDL.fbx", coinMaterialID);
    
    if (std::shared_ptr<warp::Scene> scene = sceneManager->get(coinSceneID))
    {
        scene->addCamera(cameraID);
        scene->addLight(sunID);
    }
    
    // Adjust Coin
    if (std::shared_ptr<warp::GameObject> rootObject = gameObjectManager->get(warp::GameObject::ID(1)))
    {
        rootObject->getTransform()->scale(0.015);
        rootObject->getTransform()->rotate(-90, 0, 1, 0);
        rootObject->getTransform()->translate(0, -1.25, 0);
    }
    
//    auto squareID = meshManager->create();
//    if (std::shared_ptr<warp::Mesh> squareMesh = meshManager->get(squareID))
//    {
//        squareMesh->setVertices({
//            -0.8f, 0.8f, 0.0f,   0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
//            -0.4f, 0.8f, 0.0f,   0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
//            -0.8f, 0.4f, 0.0f,   0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
//            -0.4f, 0.4f, 0.0f,   0.0f, 0.0f, 1.0f,  1.0f, 1.0f
//        });
//        squareMesh->setElements({
//            0, 2, 1,
//            2, 3, 1
//        });
//        squareMesh->load();
//    }
//    
//    warp::Scene::ID sceneID = sceneManager->create();
//    
//    if (std::shared_ptr<warp::Scene> scene = sceneManager->get(sceneID))
//    {
//        auto cameraID = cameraManager->create();
//        if (std::shared_ptr<warp::Camera> camera = cameraManager->get(cameraID))
//        {
//            camera->setPosition(glm::vec3(0, 0, 5));
//            camera->lookAt(glm::vec3(0,0,0), glm::vec3(0,1,0));
//        }
//        scene->addCamera(cameraID);
//        
//        auto t1 = std::make_shared<warp::Transform>();
//        t1->translate(0.6, 0, 0.6);
//        gameObjectManager->create(t1);
//        
//        auto t2 = std::make_shared<warp::Transform>();
//        t2->translate(-0.5, 0, 0);
//        t2->setParent(t1);
//        warp::GameObject::ID obj2 = gameObjectManager->create(t2);
//        scene->addRenderer(std::make_shared<warp::MeshRenderer>(obj2, materialID, squareID));
//        
//        auto t3 = std::make_shared<warp::Transform>();
//        t3->translate(0.5, 0, 0);
//        t3->setParent(t1);
//        warp::GameObject::ID obj3 = gameObjectManager->create(t3);
//        scene->addRenderer(std::make_shared<warp::MeshRenderer>(obj3, materialID, squareID));
//    }
    
    // Create and initialize the scene renderer
    auto sceneRenderer = std::make_shared<warp::SceneRenderer>(coinSceneID);
    sceneRenderer->init();
    
    // The scene renderer will listen to window events
    windowInput.addListener(sceneRenderer);
    
    // This is the main loop
    auto loop = std::make_shared<warp::GameLoop>(
    [&windowInput, sceneRenderer, window]()
    {
        // Process window events
        windowInput.flush();
        
        // Handle continuous input
        sceneRenderer->processInput();
        
        // Draw the scene
        sceneRenderer->render();
        
        // Swap buffers
        window->display();
    });
    windowInput.addListener(loop);
    
    loop->run();
    
    window->close();

    return EXIT_SUCCESS;
}

