#pragma once
#include "Object.h"
class Billboard :
    public Object
{
protected:
    GLuint texture;
    float size;
public:
    Billboard(float size, char* texturePath, char* shaderPath, glm::vec3 position, float angle = 0.f, glm::vec3 rotation = glm::vec3(), glm::vec3 scale = glm::vec3());
    ~Billboard();
    virtual void draw(float dt, glm::vec3 lightPosition, glm::vec3 lightColor, float radiantPower, float ambientReflectionCoefficient, float diffuseReflectionCoefficient, float specularReflectionCoefficient, float shininessCoefficient) override;
};

