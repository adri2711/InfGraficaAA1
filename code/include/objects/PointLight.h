#pragma once
#include "Object.h"

class PointLight : public Object
{
private:

    float _radiantPower;

    void Illuminate(const char* shaderPath);

public:

    PointLight(const char* shaderPath, glm::vec3 color, float _radiantPower, glm::vec3 position, float angle, glm::vec3 rotation, glm::vec3 scale);
    PointLight(const char* shaderPath, glm::vec3 color, float _radiantPower, glm::vec3 position, glm::vec3 scale);
    PointLight(const char* shaderPath, glm::vec3 color, float _radiantPower, glm::vec3 position);
    ~PointLight();

    void draw() override;
    
};
