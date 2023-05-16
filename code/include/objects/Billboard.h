#pragma once
#include "Object.h"
class Billboard :
    public Object
{
protected:
    char* texturePath = "resources/container.jpg";
	GLuint texture;
    float size;
public:
    Billboard(float size, char* texturePath, char* shaderPath, glm::vec3 position, float angle = 0.f, glm::vec3 rotation = glm::vec3(), glm::vec3 scale = glm::vec3());
    ~Billboard();
    void draw(float dt) override;
    void Init();
    void SetupData();
    void SetupProgram(std::string shaderPath);
    void SetupBuffers();
    void LoadTexture();
    void DrawBillboard();
    void SetupUniforms();
};

