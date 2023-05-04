#pragma once
#include "Renderer.h"
#include <objects/Cube.h>


class Texturing : public Renderer
{
	Program* program;
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	GLuint texture;

	glm::mat4 objMat;

	glm::vec4 color;

protected:

	void render(float dt);


public:
	Texturing(int width, int height);
	~Texturing();
};