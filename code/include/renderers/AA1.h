#pragma once
#include "objects/Model.h"
#include "objects/PointLight.h"
#include "objects/Cube.h"
#include "Renderer.h"
#include "Program.h"

#define MIN_X_POSITION_LIGHT -5
#define MAX_X_POSITION_LIGHT 5

#define MIN_Y_POSITION_LIGHT -5
#define MAX_Y_POSITION_LIGHT 5

#define MIN_Z_POSITION_LIGHT -5 
#define MAX_Z_POSITION_LIGHT 5

#define MIN_RADIANT_POWER 0
#define MAX_RADIANT_POWER 50

#define MIN_RED_COLOR 0
#define MAX_RED_COLOR 1

#define MIN_GREEN_COLOR 0
#define MAX_GREEN_COLOR 1

#define MIN_BLUE_COLOR 0
#define MAX_BLUE_COLOR 1

#define MIN_ALPHA_COLOR 0
#define MAX_ALPHA_COLOR 1

#define MIN_AMBIENT_COEFFICIENT 0
#define MAX_AMBIENT_COEFFICIENT 1

#define MIN_DIFFUSE_COEFFICIENT 0
#define MAX_DIFFUSE_COEFFICIENT 1

#define MIN_SPECULAR_COEFFICIENT 0
#define MAX_SPECULAR_COEFFICIENT 1

#define MIN_SHININESS_COEFFICIENT 0
#define MAX_SHININESS_COEFFICIENT 500

class AA1 : public Renderer
{
private:
    Program* program;
    GLuint VAO;
    GLuint VBO;

    Model* catModel;
    
    PointLight* _pointLight;

    Cube* _lightEmissor;
    Cube* _auxCube;

    glm::vec3 _lightPosition;
    glm::vec4 _lightColor;
    float _radiantPower;

    float _ambientReflectionCoefficient;
    float _diffuseReflectionCoefficient;
    float _specularReflectionCoefficient;
    float _shininessCoefficient;
    
    float elapsedTime;
    float speed = 63.f;

public:
    AA1(int width, int height);
    ~AA1();
    
protected:
    void render(float dt);
    void RenderCat(float elapsedTime);
    void RenderPointLight();
    void RenderLightEmissor();
    void renderGUI() override;
};
