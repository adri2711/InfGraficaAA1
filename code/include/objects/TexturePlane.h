#pragma once
#include "Object.h"
#include <stdio.h>

class TexturePlane :
    public Object
{
protected:
    GLuint texture;
    std::string texturePath = "resources/texture0.jpg";
    void GenerateTexture();
public:
    TexturePlane(glm::vec3 vertexPositions[], glm::vec3 normal);
    ~TexturePlane();
    void DrawTexture(glm::vec3 lightPosition, glm::vec3 lightColor, float radiantPower, float ambientReflectionCoefficient, float diffuseReflectionCoefficient, float specularReflectionCoefficient, float shininessCoefficient);
    void SetTexture(std::string path);
    void draw(float dt, glm::vec3 lightPosition, glm::vec3 lightColor, float radiantPower, float ambientReflectionCoefficient, float diffuseReflectionCoefficient, float specularReflectionCoefficient, float shininessCoefficient) override;
};

