#pragma once
#include "Object.h"

class PointLight : public Object
{
private:

    float _radiantPower;

    float _ambientReflectionCoefficient;
    float _diffuseReflectionCoefficient;
    float _specularReflectionCoefficient;
    float _shininessCoefficient;

    void Illuminate(const char* shaderPath);

public:

    PointLight(const char* shaderPath, glm::vec3 color, float _radiantPower, glm::vec3 position, float angle, glm::vec3 rotation, glm::vec3 scale);
    PointLight(const char* shaderPath, glm::vec3 color, float _radiantPower, glm::vec3 position, glm::vec3 scale);
    PointLight(const char* shaderPath, glm::vec3 color, float _radiantPower, glm::vec3 position);
    ~PointLight();

    void SetRadiantPower(float radiantPower);

    float GetRadiantPower();

    

    void draw(glm::vec3 lightPosition, glm::vec4 lightColor, float radiantPower, float ambientReflectionCoefficient, float diffuseReflectionCoefficient, float specularReflectionCoefficient, float shininessCoefficient) override;
    
};
