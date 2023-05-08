#pragma once
#include "Object.h"

class TexturePlane :
    public Object
{
protected:
    GLuint texture;
public:
    TexturePlane(glm::vec3 position, float angle, glm::vec3 rotation, glm::vec3 scale);
    ~TexturePlane();
    void DrawTexture();
    void draw(float dt, glm::vec3 lightPosition, glm::vec3 lightColor, float radiantPower, float ambientReflectionCoefficient, float diffuseReflectionCoefficient, float specularReflectionCoefficient, float shininessCoefficient) override;
};

