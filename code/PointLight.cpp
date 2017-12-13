#include "common/Scene/Lights/Point/PointLight.h"
#include <random>


void PointLight::ComputeSampleRays(std::vector<Ray>& output, glm::vec3 origin, glm::vec3 normal) const
{
    origin += normal * LARGE_EPSILON;
    const glm::vec3 lightPosition = glm::vec3(GetPosition());
    const glm::vec3 rayDirection = glm::normalize(lightPosition - origin);
    const float distanceToOrigin = glm::distance(origin, lightPosition);
    output.emplace_back(origin, rayDirection, distanceToOrigin);
}

void PointLight::SetIntensity(float input)
{
    intensity = input;
}

float PointLight::ComputeLightAttenuation(glm::vec3 origin) const
{
    if(intensity > 2.5f)
        return 1.f;
    float intensityColor = glm::length(GetLightColor());
    float d = glm::distance(origin, glm::vec3(GetPosition()));
//    if(d >5.f)
//        return 0.f;
//    return 1.f;
        
    return .4f/(d*d);
}


float randf()
{
    return rand() / (RAND_MAX + 0.);
}

void PointLight::GenerateRandomPhotonRay(Ray& ray) const
{
    float x,y,z;
    x = y = z = 2.f;
    while(x*x + y*y + z*z > 1){
        x = randf() * 2 - 1;
        y = randf() * 2 - 1;
        z = randf() * 2 - 1;
    }
    ray.SetRayPosition(glm::vec3(GetPosition()));
    ray.SetRayDirection(glm::normalize(glm::vec3(x,y,z)));
}
