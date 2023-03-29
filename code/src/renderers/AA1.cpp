#include "renderers/AA1.h"
#include <iostream>

AA1::AA1(int width, int height) : Renderer(width, height)
{
	_lightPosition = glm::vec3(0.0f, 2.3f, -3.0f);
	_radiantPower = 20.f;
	_shininessCoefficient = 5.f;
	catModel = new Model("resources/a_man.obj", "shaders/Model", glm::vec3(0.0f, -0.3f, -3.0f), glm::vec3(1.f, 1.f, 1.f));
	_pointLight = new PointLight("shaders/PointLight", glm::vec3(1.f,1.f,1.f),20, _lightPosition);
	_lightEmissor = new Cube("shaders/Cube", _lightPosition, glm::vec3(1.f, 1.f, 1.f));
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
	RenderPointLight();
	RenderLightEmissor();
}

void AA1::RenderCat(float elapsedTime)
{
	catModel->Rotate((int) (elapsedTime * speed) % 360, glm::vec3(0.0f, 1.0f, 0.0f));
	catModel->SetObjectMatrix(catModel->GetTranslationMatrix() * catModel->GetRotationMatrix());
	catModel->setColor(glm::vec4(0.5f, 0.5f, 1.f, 1.f));
	catModel->setCam(_cam);
	catModel->draw(_lightPosition, _lightColor, _radiantPower, _ambientReflectionCoefficient, _diffuseReflectionCoefficient, _specularReflectionCoefficient);    
}

void AA1::RenderPointLight()
{
	_pointLight->Move(_lightPosition);
	_pointLight->SetObjectMatrix(_pointLight->GetTranslationMatrix());
	_pointLight->setCam(_cam);
	_pointLight->draw(glm::vec3(), glm::vec4(), 0, 0, 0, 0);
}

void AA1::RenderLightEmissor()
{
	_lightEmissor->Move(_lightPosition);
	_lightEmissor->SetObjectMatrix(_lightEmissor->GetTranslationMatrix());
	_lightEmissor->setColor(glm::vec4(0.9f, 0.1f, 0.1f, 1.0f));	
	_lightEmissor->setCam(_cam);
	_lightEmissor->draw(glm::vec3(), glm::vec4(), 0, 0, 0,0);
}