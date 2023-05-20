#pragma once
#include "objects/TexturePlane.h"
#include "objects/Model.h"
#include "objects/Billboard.h"
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

class AA1 : public Renderer
{
private:
    Program* program;
    GLuint VAO;
    GLuint VBO;

    TexturePlane* floor;
    std::vector<Model> cars;
    std::vector<Billboard> trees;

    int maxCars = 7;
    int treeAmount = 20;
    float carSpeed = 500.f;
    float carTrajectoryRadius = 20.f;
    int playArea = 40;
    float carTimer = 0;

    float vec3Modulo(glm::vec3 in);

public:
    AA1(int width, int height);
    ~AA1();
    
protected:
    void render(float dt);
    void renderGUI() override;
};
