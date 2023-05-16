#pragma once
#include "objects/ModelExploding.h"
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
#include "objects/TexturePlane.h"
#include <iostream>
#include <lerp.h>

class AA1 : public Renderer
{
private:
    Program* program;
    GLuint VAO;
    GLuint VBO;

    TexturePlane* floor;
    Model* cars;

public:
    AA1(int width, int height);
    ~AA1();
    
protected:
    void render(float dt);
    void renderGUI() override;
};
