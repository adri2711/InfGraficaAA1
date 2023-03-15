#include "renderers/AA1.h"
#include <iostream>

AA1::AA1(int width, int height) : Renderer(width, height)
{
	catModel = new Model("resources/a_man.obj");
}

AA1::~AA1()
{
	delete catModel;
}

void AA1::render(float dt)
{
	elapsedTime += dt * speed;
	glm::mat4 model, view, objMat;
	model = glm::rotate(glm::mat4(), -glm::radians(float((int) elapsedTime % 360)), glm::vec3(0.0f, 1.0f, 0.0f));
	view = glm::translate(glm::mat4(), glm::vec3(0.0f, -0.3f, -3.0f));
	objMat = view * model;
	catModel->setTransforms(objMat, cam);
	catModel->draw();
}
