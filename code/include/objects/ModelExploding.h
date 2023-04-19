#pragma once
#include "Model.h"
class ModelExploding :
    public Model
{
public:
    ModelExploding(const char* modelPath, const char* shaderPath, glm::vec3 position, float angle, glm::vec3 rotation, glm::vec3 scale);
};

