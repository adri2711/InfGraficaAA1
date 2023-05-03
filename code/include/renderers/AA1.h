#pragma once
#include "objects/ModelExploding.h"
#include "objects/PointLight.h"
#include "objects/Cube.h"
#include "objects/Cube.h"
#include "Renderer.h"
#include "Program.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <cmath>
#include <iostream>
#include <lerp.h>

#define MIN_X_POSITION_LIGHT -5
#define MAX_X_POSITION_LIGHT 5

#define MIN_Y_POSITION_LIGHT -5
#define MAX_Y_POSITION_LIGHT 5

#define MIN_Z_POSITION_LIGHT -5 
#define MAX_Z_POSITION_LIGHT 5

#define MIN_RADIANT_POWER 1
#define MAX_RADIANT_POWER 250

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

#define MIN_SHININESS_COEFFICIENT 1
#define MAX_SHININESS_COEFFICIENT 64

class AA1 : public Renderer
{
private:
    Program* program;
    GLuint VAO;
    GLuint VBO;

    ModelExploding* catModel;
    
    PointLight* _pointLight;

    Cube* _lightEmissor;
    Cube* _auxCube;

    glm::vec3 _globalPosition;
    
    glm::vec3 _lightPosition;
    glm::vec3 _lightColor;
    float _radiantPower;

    float _ambientReflectionCoefficient;
    float _diffuseReflectionCoefficient;
    float _specularReflectionCoefficient;
    float _shininessCoefficient;
    
    Cube* floor;
    Cube* building;
    float elapsedTime;
    float speed = 63.f;

    float dollyProg = 0.f;
    float dollySpeed = 0.8f;
    float fovMin;
    float fovMax;
    float dollyMovement = 3.75f;

    bool explode = false;

public:
    AA1(int width, int height);
    ~AA1();
    
protected:
    void render(float dt);
    void CalculateDollyEffect(float dt);
    void RenderCat(float elapsedTime);
    void RenderPointLight(float dt);
    void RenderLightEmissor(float dt);
    void RenderScenario(float dt);
    void renderGUI() override;
};
