#pragma once
#include "Renderer.h"
#include "objects/Cube.h"
#include <map>

struct CubeAttributes {

    glm::vec3 _position;
    glm::vec4 _color;

};

class TransparencyExercise : public Renderer
{
private:
    Program* program;
    GLuint VAO;
    GLuint VBO;

    Cube* _cube;


public:
    TransparencyExercise(int width, int height);
    ~TransparencyExercise();

protected:
    void render(float dt);
    void renderGUI() override;
};

