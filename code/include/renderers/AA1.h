#pragma once
#include "objects/Model.h"
#include "Renderer.h"
#include "Program.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>

class AA1 :
    public Renderer
{
    Program* program;
    GLuint VAO;
    GLuint VBO;

    Model* catModel;
    float elapsedTime;
    float speed = 63.f;

public:
    AA1(int width, int height);
    ~AA1();
protected:
    void render(float dt);
};