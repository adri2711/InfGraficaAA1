#pragma once
#include "objects/Model.h"
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

class AA1 :
    public Renderer
{
    Program* program;
    GLuint VAO;
    GLuint VBO;

    Model* catModel;
    Cube* floor;
    Cube* building;
    float elapsedTime;
    float speed = 63.f;

    float dollyProg = 0.f;
    float dollySpeed = 0.8f;
    float fovMin;
    float fovMax;
    float dollyMovement = 3.75f;

public:
    AA1(int width, int height);
    ~AA1();
protected:
    void render(float dt);
};