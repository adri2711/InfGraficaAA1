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
    TexturePlane(std::string texturePath, glm::vec3 position, float angle, glm::vec3 rotation, glm::vec3 scale);
    ~TexturePlane();
    void DrawTexture();
    void SetTexture(std::string path);
    void draw(float dt) override;
};

