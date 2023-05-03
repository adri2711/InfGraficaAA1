#pragma once
#include "Model.h"
#include <imgui/imgui.h>

class ModelExploding :
    public Model
{
public:
    bool explode = false;
    float explosionTime = 0.f;
    float explosionSpeed = 4.f;
    ModelExploding(char* modelPath, char* shaderPath, glm::vec3 position, float angle, glm::vec3 rotation, glm::vec3 scale);
protected:
    void SetupProgram(std::string shaderPath) override;
    void SetupUniformsModel(glm::vec3 lightPosition, glm::vec3 lightColor, float radiantPower, float ambientReflectionCoefficient, float diffuseReflectionCoefficient, float specularReflectionCoefficient, float shininessCoefficient) override;
};

