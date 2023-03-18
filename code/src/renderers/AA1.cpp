#include "renderers/AA1.h"
#include <iostream>

AA1::AA1(int width, int height) : Renderer(width, height)
{
	catModel = new Model("resources/a_man.obj", "shaders/Model", glm::vec3(0.0f, -0.3f, -3.0f), glm::vec3(1.f, 1.f, 1.f));
	_pointLight = new PointLight("shaders/PointLight", glm::vec3(1,1,1),20, glm::vec3(0.0f, 0.2, -3.0f));
	_lightEmissor = new Cube(glm::vec3(0.0f, 0.2, -3.0f));
}

AA1::~AA1()
{
	delete catModel;
	delete _pointLight;
	delete _lightEmissor;
}

void AA1::render(float dt)
{	
	elapsedTime += dt;    
	RenderCat(elapsedTime);
	RenderPointLight(dt);
}

void AA1::RenderCat(float elapsedTime)
{
	catModel->Rotate((int) (elapsedTime * speed) % 360, glm::vec3(0.0f, 1.0f, 0.0f));
	catModel->SetObjectMatrix(catModel->GetView() * catModel->GetModel());
	catModel->setCam(cam);
	catModel->draw();    
}

void AA1::RenderPointLight(float dt)
{
	_pointLight->setCam(cam);
	_pointLight->draw();
}

void AA1::RenderLightEmissor(float dt)
{		
	_lightEmissor->setCam(cam);
	_lightEmissor->draw();
}