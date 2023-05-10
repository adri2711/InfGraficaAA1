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
    TexturePlane();
    ~TexturePlane();
    void DrawTexture();
    void SetTexture(std::string path);
    void draw(float dt, glm::vec3 lightPosition, glm::vec3 lightColor, float radiantPower, float ambientReflectionCoefficient, float diffuseReflectionCoefficient, float specularReflectionCoefficient, float shininessCoefficient) override;
};

