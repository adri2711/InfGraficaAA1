#include "renderers/TransparencyExercise.h"

TransparencyExercise::TransparencyExercise(int width, int height) : Renderer(width, height)
{
    _cube = new Cube("shaders/Cube", glm::vec3(0), glm::vec3(0.f, 0.f, 5.f), 5.f, 5.f, 5.f);
}

TransparencyExercise::~TransparencyExercise()
{
    delete _cube;
}

void TransparencyExercise::render(float dt) {

    //Compute distances to the camera
    CubeAttributes cubes[] = {
        CubeAttributes {glm::vec3(.5f, .0f, -7.5f), glm::vec4(.1f, .1f, .6f, .8f)},
        CubeAttributes {glm::vec3(0.f, 0.f, -6.f), glm::vec4(.6f, .1f, .1f, .3f)},
    };

    std::map<float, CubeAttributes> sorted;
    for (int i = 0; i < 2; i++)
    {
        float dist = glm::length(glm::vec3(panv[0], panv[1], panv[2]) - cubes[i]._position);
        sorted[dist] = cubes[i];
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);
    glDisable(GL_DEPTH_TEST);

    for (std::map<float, CubeAttributes>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); it++)
    {
        CubeAttributes attrib = it->second;
        _cube->Move(attrib._position);
        _cube->setColor(attrib._color);
        _cube->setCam(_cam);
        _cube->draw(glm::vec3(), glm::vec4(), 0, 0, 0, 0, 0);
    }

    glEnable(GL_DEPTH_TEST);
}

void TransparencyExercise::renderGUI()
{
}
