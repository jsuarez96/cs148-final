#include "assignment7/Assignment7.h"
#include "common/core.h"
//js
//#include "common/Utility/Mesh/Simple/PrimitiveCreator.h"
#include "common/Utility/Mesh/Loading/MeshLoader.h"
#include "common/Utility/Texture/TextureLoader.h"
//end js

std::shared_ptr<Camera> Assignment7::CreateCamera() const
{
    const glm::vec2 resolution = GetImageOutputResolution();
    std::shared_ptr<Camera> camera = std::make_shared<PerspectiveCamera>(resolution.x / resolution.y, 26.6f);
    //js
    //std::shared_ptr<Camera> camera = std::make_shared<PerspectiveCamera>(1280.f / 720.f, 60.f);
    //end js
    //camera->SetPosition(glm::vec3(0.f, -4.1469f, 0.73693f));
    //camera->Rotate(glm::vec3(0.f, 0.f, 1.f), PI/8.f);
    //camera->Rotate(glm::vec3(1.f, 0.f, 0.f), PI / 4.f);
    camera->Rotate(glm::vec3(1.f, 0.f, 0.f), PI / 4.f + 55.f*PI/360.f);
    //camera->SetPosition(glm::vec3(0.f, 5.f, 0.f));
    //camera->SetPosition(glm::vec3(15.97f, -14.7f,8.95f));
    //camera->SetPosition(glm::vec3(0.496f, -5.11f, 5.22f));
    camera->SetPosition(glm::vec3(0.496f, -20.11f, 12.22f)); //correct
    //camera->SetPosition(glm::vec3(0.496f, 4.11f, 5.22f));
    //camera->SetPosition(glm::vec3(0.f, 3.f, 10.f));
    return camera;
}


// Assignment 7 Part 1 TODO: Change the '1' here.
// 0 -- Naive.
// 1 -- BVH.
// 2 -- Uniform Grid.
#define ACCELERATION_TYPE 2


/*std::shared_ptr<Scene> Assignment7::CreateScene() const
 {
 std::shared_ptr<Scene> newScene = std::make_shared<Scene>();
 
 // Material
 std::shared_ptr<BlinnPhongMaterial> cubeMaterial = std::make_shared<BlinnPhongMaterial>();
 cubeMaterial->SetDiffuse(glm::vec3(1.f, 1.f, 1.f));
 cubeMaterial->SetSpecular(glm::vec3(0.6f, 0.6f, 0.6f), 40.f);
 cubeMaterial->SetReflectivity(0.3f);
 
 // Objects
 std::vector<std::shared_ptr<aiMaterial>> loadedMaterials;
 std::vector<std::shared_ptr<MeshObject>> cubeObjects = MeshLoader::LoadMesh("CornellBox/CornellBox-Assignment7-Alt.obj", &loadedMaterials);
 for (size_t i = 0; i < cubeObjects.size(); ++i) {
 std::shared_ptr<Material> materialCopy = cubeMaterial->Clone();
 materialCopy->LoadMaterialFromAssimp(loadedMaterials[i]);
 cubeObjects[i]->SetMaterial(materialCopy);
 
 std::shared_ptr<SceneObject> cubeSceneObject = std::make_shared<SceneObject>();
 cubeSceneObject->AddMeshObject(cubeObjects[i]);
 cubeSceneObject->Rotate(glm::vec3(1.f, 0.f, 0.f), PI / 2.f);
 
 cubeSceneObject->CreateAccelerationData(AccelerationTypes::BVH);
 cubeSceneObject->ConfigureAccelerationStructure([](AccelerationStructure* genericAccelerator) {
 BVHAcceleration* accelerator = dynamic_cast<BVHAcceleration*>(genericAccelerator);
 accelerator->SetMaximumChildren(2);
 accelerator->SetNodesOnLeaves(2);
 });
 
 cubeSceneObject->ConfigureChildMeshAccelerationStructure([](AccelerationStructure* genericAccelerator) {
 BVHAcceleration* accelerator = dynamic_cast<BVHAcceleration*>(genericAccelerator);
 accelerator->SetMaximumChildren(2);
 accelerator->SetNodesOnLeaves(2);
 });
 newScene->AddSceneObject(cubeSceneObject);
 }
 
 // Lights
 std::shared_ptr<Light> pointLight = std::make_shared<PointLight>();
 pointLight->SetPosition(glm::vec3(0.01909f, 0.0101f, 1.97028f));
 pointLight->SetLightColor(glm::vec3(1.f, 1.f, 1.f));
 
 #if ACCELERATION_TYPE == 0
 newScene->GenerateAccelerationData(AccelerationTypes::NONE);
 #elif ACCELERATION_TYPE == 1
 newScene->GenerateAccelerationData(AccelerationTypes::BVH);
 #else
 UniformGridAcceleration* accelerator = dynamic_cast<UniformGridAcceleration*>(newScene->GenerateAccelerationData(AccelerationTypes::UNIFORM_GRID));
 assert(accelerator);
 // Assignment 7 Part 2 TODO: Change the glm::ivec3(10, 10, 10) here.
 //accelerator->SetSuggestedGridSize(glm::ivec3(10, 10, 10));
 accelerator->SetSuggestedGridSize(glm::ivec3(5, 5, 5));
 #endif
 newScene->AddLight(pointLight);
 
 return newScene;
 }*/


std::shared_ptr<Scene> Assignment7::CreateScene() const
{
    std::shared_ptr<Scene> newScene = std::make_shared<Scene>();
    
    // Material
    std::shared_ptr<BlinnPhongMaterial> cubeMaterial = std::make_shared<BlinnPhongMaterial>();
    cubeMaterial->SetDiffuse(glm::vec3(1.f, 1.f, 1.f));
    cubeMaterial->SetSpecular(glm::vec3(0.9f, 0.9f, 0.9f), 60.f);
    //cubeMaterial->SetReflectivity(0.3f);
    cubeMaterial->SetReflectivity(0.1f);
    
    std::shared_ptr<BlinnPhongMaterial> cubeMaterial2 = std::make_shared<BlinnPhongMaterial>();
    cubeMaterial2->SetDiffuse(glm::vec3(1.f, 1.f, 1.f));
    cubeMaterial2->SetSpecular(glm::vec3(0.6f, 0.6f, 0.6f), 40.f);
    cubeMaterial2->SetReflectivity(0.3f);
    
    // Objects
    std::vector<std::shared_ptr<aiMaterial>> loadedMaterials;
    std::vector<std::shared_ptr<aiMaterial>> loadedMaterials2;
    //std::vector<std::shared_ptr<MeshObject>> cubeObjects = MeshLoader::LoadMesh("CornellBox/CornellBox-Assignment7-Alt.obj", &loadedMaterials);
    //js
    //trying objects
    std::vector<std::shared_ptr<MeshObject>> cubeObjects = MeshLoader::LoadMesh("cs148-final/room/room4.obj", &loadedMaterials);
    //std::vector<std::shared_ptr<MeshObject>> cubeObjects = MeshLoader::LoadMesh("B3/SA_45ACP_Example_blend/SA_45ACP_Example.obj", &loadedMaterials);
    
    //cubeMaterial->SetTexture("diffuseTexture", TextureLoader::LoadTexture("B3/SA_45ACP_Example_blend/SA_45ACP_Diffuse.tga")); //js test
    //    std::vector<std::shared_ptr<MeshObject>> cubeObjects = MeshLoader::LoadMesh("cl3/ChristmasLightsO.obj", &loadedMaterials);
    //
    //    cubeMaterial->SetTexture("diffuseTexture", TextureLoader::LoadTexture("cl3/lights_texture.png")); //js test
    //    std::vector<std::shared_ptr<MeshObject>> cubeObjects = MeshLoader::LoadMesh("light4/light4.obj", &loadedMaterials);
    //
    //    cubeMaterial->SetTexture("diffuseTexture", TextureLoader::LoadTexture("light4/vintage_floral_letter.png")); //js test
    //cubeMaterial->SetTexture("specularTexture", TextureLoader::LoadTexture("SpikedBat/Bat/Textures/Bat_Gloss.tga")); //js test
    //cubeMaterial->SetTexture("normalTexture", TextureLoader::LoadTexture("SpikedBat/Bat/Textures/Bat_Normal.tga")); //js test
    //    std::vector<std::shared_ptr<MeshObject>> cubeObjects = MeshLoader::LoadMesh("SpikedBat/Bat/Mesh/Bat.obj", &loadedMaterials);
    //
    //    cubeMaterial->SetTexture("diffuseTexture", TextureLoader::LoadTexture("SpikedBat/Bat/Textures/Bat_Diffuse.tga")); //js test
    //    cubeMaterial->SetTexture("specularTexture", TextureLoader::LoadTexture("SpikedBat/Bat/Textures/Bat_Gloss.tga")); //js test
    //    cubeMaterial->SetTexture("normalTexture", TextureLoader::LoadTexture("SpikedBat/Bat/Textures/Bat_Normal.tga")); //js test
    //trying balloon
    std::vector<std::shared_ptr<MeshObject>> cubeObjects2 = MeshLoader::LoadMesh("Balloon/assign5.obj", &loadedMaterials2);
    cubeMaterial2->SetTexture("diffuseTexture", TextureLoader::LoadTexture("Balloon/balloon_color.png")); //js test
    cubeMaterial2->SetTexture("specularTexture", TextureLoader::LoadTexture("Balloon/balloon_color.png")); //js test
    //trying bat
    //end js
    for (size_t i = 0; i < cubeObjects.size(); ++i) {
        std::shared_ptr<Material> materialCopy = cubeMaterial->Clone();
        materialCopy->LoadMaterialFromAssimp(loadedMaterials[i]);
        cubeObjects[i]->SetMaterial(materialCopy);
        
        std::shared_ptr<SceneObject> cubeSceneObject = std::make_shared<SceneObject>();
        cubeSceneObject->AddMeshObject(cubeObjects[i]);
        
        //js setting texture
        std::shared_ptr<Material> materialCop = cubeMaterial->Clone();
        materialCop->LoadMaterialFromAssimp(loadedMaterials[i]);
        
        //materialCop->SetTexture("diffuseTexture", TextureLoader::LoadTexture("Balloon/balloon_color.png"));
        //materialCop->SetTexture("diffuseTexture", TextureLoader::LoadTexture("Balloon/balloon_color.png"));
        //end js
        
        //js -- here is lights
        //cubeSceneObject->SetPosition(glm::vec3(-5.3f,-0.00452f,0.41f));
        //cubeSceneObject->SetPosition(glm::vec3(0,0,-5));
        //cubeSceneObject->MultScale(.7);
        cubeSceneObject->Rotate(glm::vec3(1.f, 0.f, 0.f), PI /2.f);
        //cubeSceneObject->Rotate(glm::vec3(1.f, 0.f, 0.f), PI * 2.f);
        //cubeMaterial->SetTexture("diffuseTexture", TextureLoader::LoadTexture("Balloon/balloon_color.png"));
        //endjs
        
        cubeSceneObject->CreateAccelerationData(AccelerationTypes::BVH);
        cubeSceneObject->ConfigureAccelerationStructure([](AccelerationStructure* genericAccelerator) {
            BVHAcceleration* accelerator = dynamic_cast<BVHAcceleration*>(genericAccelerator);
            accelerator->SetMaximumChildren(2);
            accelerator->SetNodesOnLeaves(2);
        });
        
        cubeSceneObject->ConfigureChildMeshAccelerationStructure([](AccelerationStructure* genericAccelerator) {
            BVHAcceleration* accelerator = dynamic_cast<BVHAcceleration*>(genericAccelerator);
            accelerator->SetMaximumChildren(2);
            accelerator->SetNodesOnLeaves(2);
        });
        newScene->AddSceneObject(cubeSceneObject);
    }
    
    //doing balloon here
    for (size_t i = 0; i < cubeObjects2.size(); ++i) {
        std::shared_ptr<Material> materialCopy = cubeMaterial2->Clone();
        materialCopy->LoadMaterialFromAssimp(loadedMaterials2[i]);
        cubeObjects2[i]->SetMaterial(materialCopy);
        
        std::shared_ptr<SceneObject> cubeSceneObject = std::make_shared<SceneObject>();
        cubeSceneObject->AddMeshObject(cubeObjects2[i]);
        
        //js setting texture
        std::shared_ptr<Material> materialCop = cubeMaterial2->Clone();
        materialCop->LoadMaterialFromAssimp(loadedMaterials2[i]);
        
        //materialCop->SetTexture("diffuseTexture", TextureLoader::LoadTexture("Balloon/balloon_color.png"));
        //materialCop->SetTexture("diffuseTexture", TextureLoader::LoadTexture("Balloon/balloon_color.png"));
        //end js
        
        //js
        //cubeSceneObject->SetPosition(glm::vec3(-3,-5,0));
        cubeSceneObject->SetPosition(glm::vec3(1.5,-3.0,-5));
        //cubeSceneObject->MultScale(.005);
        //cubeSceneObject->Rotate(glm::vec3(1.f, 0.f, 0.f), PI / 2.f);
        //cubeMaterial->SetTexture("diffuseTexture", TextureLoader::LoadTexture("Balloon/balloon_color.png"));
        //endjs
        
        cubeSceneObject->CreateAccelerationData(AccelerationTypes::BVH);
        cubeSceneObject->ConfigureAccelerationStructure([](AccelerationStructure* genericAccelerator) {
            BVHAcceleration* accelerator = dynamic_cast<BVHAcceleration*>(genericAccelerator);
            accelerator->SetMaximumChildren(2);
            accelerator->SetNodesOnLeaves(2);
        });
        
        cubeSceneObject->ConfigureChildMeshAccelerationStructure([](AccelerationStructure* genericAccelerator) {
            BVHAcceleration* accelerator = dynamic_cast<BVHAcceleration*>(genericAccelerator);
            accelerator->SetMaximumChildren(2);
            accelerator->SetNodesOnLeaves(2);
        });
        //getting rid of balloon rn
        //newScene->AddSceneObject(cubeSceneObject);
    }
    
    // Lights
    std::shared_ptr<Light> pointLight = std::make_shared<PointLight>();
    //js
    //std::shared_ptr<Light> pointLight = std::make_shared<AreaLight>(glm::vec2(5,5));
    //end js
    //pointLight->SetPosition(glm::vec3(0.01909f, 0.0101f, 1.97028f));
    pointLight->SetPosition(glm::vec3(0.01909f, 0.0101f, 7.2028f));
    //pointLight->SetPosition(glm::vec3(1,1,2));
    pointLight->SetLightColor(glm::vec3(1.f, 1.f, 1.f));
    //adding new light
    std::shared_ptr<Light> redLight = std::make_shared<PointLight>();
    redLight->SetPosition(glm::vec3(4,-1.5,0.5));
    redLight->SetLightColor(glm::vec3(1.f, 0.f, 0.f));
    std::shared_ptr<Light> redLight2 = std::make_shared<PointLight>();
    redLight2->SetPosition(glm::vec3(-6.65,-1.33,0.51));
    redLight2->SetLightColor(glm::vec3(1.f, 0.f, 0.f));
    std::shared_ptr<Light> redLight3 = std::make_shared<PointLight>();
    redLight3->SetPosition(glm::vec3(-1.35,-1.62,0.49));
    redLight3->SetLightColor(glm::vec3(1.f, 0.f, 0.f));
    std::shared_ptr<Light> greenLight = std::make_shared<PointLight>();
    greenLight->SetPosition(glm::vec3(6.6,1.5,0.5));
    greenLight->SetLightColor(glm::vec3(0.f, 1.f, 0.f));
    std::shared_ptr<Light> greenLight2 = std::make_shared<PointLight>();
    greenLight2->SetPosition(glm::vec3(1.33,1.54,0.408));
    greenLight2->SetLightColor(glm::vec3(0.f, 1.f, 0.f));
    std::shared_ptr<Light> greenLight3 = std::make_shared<PointLight>();
    greenLight3->SetPosition(glm::vec3(-3.95,1.28,0.58));
    greenLight3->SetLightColor(glm::vec3(0.f, 1.f, 0.f));
    //end light
    
#if ACCELERATION_TYPE == 0
    newScene->GenerateAccelerationData(AccelerationTypes::NONE);
#elif ACCELERATION_TYPE == 1
    newScene->GenerateAccelerationData(AccelerationTypes::BVH);
#else
    UniformGridAcceleration* accelerator = dynamic_cast<UniformGridAcceleration*>(newScene->GenerateAccelerationData(AccelerationTypes::UNIFORM_GRID));
    assert(accelerator);
    // Assignment 7 Part 2 TODO: Change the glm::ivec3(10, 10, 10) here.
    accelerator->SetSuggestedGridSize(glm::ivec3(10, 10, 10));
    //accelerator->SetSuggestedGridSize(glm::ivec3(5, 5, 5));
#endif
    newScene->AddLight(pointLight);
    //newScene->AddLight(redLight);
    //newScene->AddLight(greenLight);
    //newScene->AddLight(greenLight2);
    //newScene->AddLight(greenLight3);
    return newScene;
}

std::shared_ptr<ColorSampler> Assignment7::CreateSampler() const
{
    std::shared_ptr<JitterColorSampler> jitter = std::make_shared<JitterColorSampler>();
    jitter->SetGridSize(glm::ivec3(1, 1, 1));
    return jitter;
}

std::shared_ptr<class Renderer> Assignment7::CreateRenderer(std::shared_ptr<Scene> scene, std::shared_ptr<ColorSampler> sampler) const
{
    return std::make_shared<BackwardRenderer>(scene, sampler);
}

int Assignment7::GetSamplesPerPixel() const
{
    return 1; //was 2
}

bool Assignment7::NotifyNewPixelSample(glm::vec3 inputSampleColor, int sampleIndex)
{
    return true;
}

int Assignment7::GetMaxReflectionBounces() const
{
    return 2;
}

int Assignment7::GetMaxRefractionBounces() const
{
    return 4;
}

glm::vec2 Assignment7::GetImageOutputResolution() const
{
    return glm::vec2(640.f, 480.f);
    //js
    //return glm::vec2(1280.f, 720.f);
    //end js
}
