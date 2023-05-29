#pragma once
#include "objects/TexturePlane.h"
#include "objects/Model.h"
#include "objects/Billboard.h"
#include "objects/PointLight.h"
#include "objects/Cube.h"
#include "objects/Instance.h"
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
    std::vector<Billboard> trees;
    std::vector<Model> _cars;

    Instance* _instanceCar;

    int maxCars = 10;
    int treeAmount = 20;
    int playArea = 40;
    float carTimer = 0;
    float carSpeed = 500.f;
    float carTrajectoryRadius = 20.f;

    bool _changeView;
    bool _changeCharge;

    glm::vec3 _lastCameraPosition;
    float _lastCameraYRotation;
    float _lastCameraXRotation;

    float vec3Modulo(glm::vec3 in);

public:
    AA1(int width, int height);
    ~AA1();
    
protected:
    void render(float dt);
    void renderGUI() override;
};
