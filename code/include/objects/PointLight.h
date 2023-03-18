#pragma once
#include "Object.h"

class PointLight : public Object
{
private:

    float _radiantPower;

    void Illuminate(const char* shaderPath);

public:

    PointLight(const char* shaderPath, glm::vec3 color, float _radiantPower, glm::vec3 view, float angle, glm::vec3 model, glm::vec3 projection);
    PointLight(const char* shaderPath, glm::vec3 color, float _radiantPower, glm::vec3 view, glm::vec3 projection);
    PointLight(const char* shaderPath, glm::vec3 color, float _radiantPower, glm::vec3 view);
    ~PointLight();

    void SetRadiantPower(float radiantPower);

    float GetRadiantPower();

    void draw() override;
    
};
