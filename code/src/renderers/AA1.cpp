#include "renderers/AA1.h"

AA1::AA1(int width, int height) : Renderer(width, height)
{
	catModel = new Model("resources/a_man.obj");
	floor = new Cube(15.f,1.f,15.f);
	building = new Cube(5.f,11.f,5.f);
	fovMin = FOV;
	fovMax = glm::radians(120.f);
}

AA1::~AA1()
{
	delete catModel;
}

void AA1::render(float dt)
{
	elapsedTime += dt * speed;

	glm::mat4 model, view, objMat;
	glm::vec3 globalPos = glm::vec3(0.0f, -1.5f, -7.0f + dollyMovement * dollyProg);
	model = glm::rotate(glm::mat4(), -glm::radians(float((int) elapsedTime % 360)), glm::vec3(0.0f, 1.0f, 0.0f));
	view = glm::translate(glm::mat4(), globalPos);
	objMat = view * model;

	if (dollyProg < 1.f) {
		FOV = lerp(fovMin, fovMax, dollyProg);
		cam._projection = glm::perspective(FOV, (float)width / (float)height, zNear, zFar);
		dollyProg = fmin(dollyProg + dt * dollySpeed, 1.f);
	}
	catModel->setTransforms(objMat, cam);
	catModel->draw();

	view = glm::translate(glm::mat4(), globalPos + glm::vec3(0.f,-1.f,0.f));
	objMat = view;
	floor->setTransforms(objMat, cam);
	floor->setColor(glm::vec4(.1f,.3f,.3f,1.f));
	floor->draw();

	view = glm::translate(glm::mat4(), globalPos + glm::vec3(-5.f,2.f,-5.f));
	objMat = view;
	building->setTransforms(objMat, cam);
	building->setColor(glm::vec4(.5f,.3f,.1f,1.f));
	building->draw();
}
