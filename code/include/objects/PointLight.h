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
    PointLight(float _radiantPower, glm::vec3 position);
    ~PointLight();

    void SetRadiantPower(float radiantPower);

    float GetRadiantPower();

    

    void draw(float dt) override;
    
};
