#pragma once
#include "objects/Model.h"
#include "objects/PointLight.h"
#include "objects/Cube.h"
#include "Renderer.h"
#include "Program.h"


class AA1 : public Renderer
{
private:
    Program* program;
    GLuint VAO;
    GLuint VBO;

    Model* catModel;
    
    PointLight* _pointLight;

    Cube* _lightEmissor; 
    
    float elapsedTime;
    float speed = 63.f;

public:
    AA1(int width, int height);
    ~AA1();

    void setTransforms(glm::mat4 objectMatrix, CameraTransforms cam);
    
protected:
    void render(float dt);
    void RenderCat(float elapsedTime);
    void RenderPointLight(float dt);
    void RenderLightEmissor(float dt);
};
