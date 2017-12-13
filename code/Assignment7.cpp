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
    
    //Perspective A
//   camera->Rotate(glm::vec3(1.f, 0.f, 0.f), -PI / 12.f);
//    camera->SetPosition(glm::vec3(0.f, 7.f, 0.f));

    //Main view
    camera->Rotate(glm::vec3(1.f, 0.f, 0.f), -PI / 36.f);
    camera->SetPosition(glm::vec3(0.f, 9.f, 20.f));
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
    //For perspective A
    cubeMaterial->SetReflectivity(0.03f);
   //For main perspective
//    cubeMaterial->SetReflectivity(0.7f);
    
    std::shared_ptr<BlinnPhongMaterial> cubeMaterial2 = std::make_shared<BlinnPhongMaterial>();
    cubeMaterial2->SetDiffuse(glm::vec3(1.f, 1.f, 1.f));
//    cubeMaterial2->SetSpecular(glm::vec3(0.6f, 0.6f, 0.6f), 40.f);
//    cubeMaterial2->SetReflectivity(0.3f);
    
    // Objects
    std::vector<std::shared_ptr<aiMaterial>> loadedMaterials;
    std::vector<std::shared_ptr<aiMaterial>> loadedMaterials2;
    //std::vector<std::shared_ptr<MeshObject>> cubeObjects = MeshLoader::LoadMesh("CornellBox/CornellBox-Assignment7-Alt.obj", &loadedMaterials);
    //js
    //trying objects
    std::vector<std::shared_ptr<MeshObject>> cubeObjects = MeshLoader::LoadMesh("cs148-final/room/room5_shiny.obj", &loadedMaterials);
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
    std::vector<std::shared_ptr<MeshObject>> cubeObjects2 = MeshLoader::LoadMesh("cs148-final/room/room5_dull.obj", &loadedMaterials2);
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
//        cubeSceneObject->Rotate(glm::vec3(1.f, 0.f, 0.f), PI /2.f);
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
    
        
//        cubeSceneObject->Rotate(glm::vec3(1.f, 0.f, 0.f), PI /2.f);

        
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
        newScene->AddSceneObject(cubeSceneObject);
    }
    
    // Lights
    std::shared_ptr<Light> pointLight = std::make_shared<PointLight>();
    //js
    //std::shared_ptr<Light> pointLight = std::make_shared<AreaLight>(glm::vec2(5,5));
    //end js
    //pointLight->SetPosition(glm::vec3(0.01909f, 0.0101f, 1.97028f));
    pointLight->SetPosition(glm::vec3(0.0f,12.f,-10.f));
    //pointLight->SetPosition(glm::vec3(1,1,2));
    pointLight->SetLightColor(glm::vec3(1.f, 1.f,1.f));
    //adding new light
    std::shared_ptr<PointLight> redLight = std::make_shared<PointLight>();
    std::shared_ptr<PointLight> redLight2 = std::make_shared<PointLight>();
    std::shared_ptr<PointLight> redLight3 = std::make_shared<PointLight>();
    std::shared_ptr<PointLight> greenLight = std::make_shared<PointLight>();
    std::shared_ptr<PointLight> greenLight2 = std::make_shared<PointLight>();
    std::shared_ptr<PointLight> greenLight3 = std::make_shared<PointLight>();


    redLight->SetPosition(glm::vec3(-.75,2.4,-11.8f));
    redLight->SetLightColor(glm::vec3(1.f, 0.f, 0.f));
    redLight->SetIntensity(2.f);
    redLight2->SetIntensity(2.f);
    redLight3->SetIntensity(2.f);

    
    redLight2->SetPosition(glm::vec3(-2.7f,2.4f,-12.9f));
    redLight2->SetLightColor(glm::vec3(1.f, 0.f, 0.f));
    redLight3->SetPosition(glm::vec3(1.3f,2.6f,-10.9f));
    redLight3->SetLightColor(glm::vec3(1.f, 0.f, 0.f));
    
    
    greenLight->SetPosition(glm::vec3(-1.3f,2.4f,-13.6f));
    greenLight->SetLightColor(glm::vec3(0.f, 1.f, 0.f));
    greenLight->SetIntensity(2.f);
    greenLight2->SetIntensity(2.f);
    greenLight3->SetIntensity(2.f);
    greenLight2->SetLightColor(glm::vec3(0.f, 1.f, 0.f));
    greenLight2->SetPosition(glm::vec3(0.7f,2.4f,-12.5f));
    greenLight3->SetPosition(glm::vec3(2.5f,2.4f,-11.4f));
    greenLight3->SetLightColor(glm::vec3(0.f, 1.f, 0.f));
    
    //4,15,-23.6
    std::shared_ptr<PointLight> g = std::make_shared<PointLight>();
    //2, 14, -23.6
    std::shared_ptr<PointLight> h = std::make_shared<PointLight>();
    //2,11.2, -23.6
    std::shared_ptr<PointLight> o = std::make_shared<PointLight>();
    //-6.4,10.1, -23.6
    std::shared_ptr<PointLight> s = std::make_shared<PointLight>();
    //-5.3,8.9,-23.6
    std::shared_ptr<PointLight> t = std::make_shared<PointLight>();
    
    g->SetPosition(glm::vec3(4,14.5,-23.6));
    g->SetLightColor(glm::vec3(0.f, 0.f, 1.f));
    g->SetIntensity(2.f);
    
    h->SetPosition(glm::vec3(2, 14, -23.6));
    h->SetLightColor(glm::vec3(1.f, 0.f, 0.f));
    h->SetIntensity(2.f);
    
    o->SetPosition(glm::vec3(2.2, 11.8, -23.6));
    o->SetLightColor(glm::vec3(0.f, 1.f, 0.f));
    o->SetIntensity(2.f);

    s->SetPosition(glm::vec3(-6.4,10.1, -23.6));
    s->SetLightColor(glm::vec3(0.f, 0.f, 1.f));
    s->SetIntensity(2.f);

    t->SetPosition(glm::vec3(-5.3,9.5,-23.6));
    t->SetLightColor(glm::vec3(1.f, 0.f, 0.f));
    t->SetIntensity(2.f);
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
    newScene->AddLight(redLight);
    newScene->AddLight(redLight2);
    newScene->AddLight(redLight3);
    newScene->AddLight(greenLight);
    newScene->AddLight(greenLight2);
    newScene->AddLight(greenLight3);
    newScene->AddLight(g);
    newScene->AddLight(h);
    newScene->AddLight(o);
    newScene->AddLight(s);
    newScene->AddLight(t);



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
