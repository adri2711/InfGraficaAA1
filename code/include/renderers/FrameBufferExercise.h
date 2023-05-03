#pragma once
#include "Renderer.h"
#include "objects/Cube.h"

class FrameBufferExercise : public Renderer
{
private:
    Cube* _cube;

protected:
    void render(float dt);
    void renderGUI() override;

public:
    FrameBufferExercise(int width, int height);
    ~FrameBufferExercise();

};