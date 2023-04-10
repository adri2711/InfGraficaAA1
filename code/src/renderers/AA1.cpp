#include "renderers/AA1.h"
#include <iostream>

AA1::AA1(int width, int height) : Renderer(width, height)
{
	_lightPosition = glm::vec3(0.0f, 2.3f, -3.0f);
	_radiantPower = 20.f;
	_shininessCoefficient = 5.f;
	catModel = new Model("resources/a_man.obj", "shaders/Model", glm::vec3(0.0f, -0.3f, -3.0f), glm::vec3(1.f, 1.f, 1.f));
	_pointLight = new PointLight(20, _lightPosition);
	_lightEmissor = new Cube("shaders/Cube", _lightPosition, glm::vec3(1.f, 1.f, 1.f));
}

AA1::~AA1()
{
	delete catModel;
	delete _pointLight;
	delete _lightEmissor;
	delete _auxCube;
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
	catModel->Rotate((int)(elapsedTime * speed) % 360, glm::vec3(0.0f, 1.0f, 0.0f));
	catModel->SetObjectMatrix(catModel->GetTranslationMatrix() * catModel->GetRotationMatrix());
	catModel->setColor(glm::vec4(0.5f, 0.5f, 1.f, 1.f));
	catModel->setCam(_cam);
	catModel->draw(_lightPosition, _lightColor, _radiantPower, _ambientReflectionCoefficient, _diffuseReflectionCoefficient, _specularReflectionCoefficient, _shininessCoefficient);
}

void AA1::RenderPointLight()
{
	_pointLight->Move(_lightPosition);
	_pointLight->SetObjectMatrix(_pointLight->GetTranslationMatrix());
}

void AA1::RenderLightEmissor()
{
	_lightEmissor->Move(_lightPosition);
	_lightEmissor->SetObjectMatrix(_lightEmissor->GetTranslationMatrix());
	_lightEmissor->setColor(glm::vec4(_lightColor.r, _lightColor.g, _lightColor.b, _lightColor.a));	
	_lightEmissor->setCam(_cam);
	_lightEmissor->draw(glm::vec3(), glm::vec4(), 0, 0, 0,0, 0);
}

void AA1::renderGUI()
{

	ImGui::SliderFloat("X Position Light", &_lightPosition.x, MIN_X_POSITION_LIGHT, MAX_X_POSITION_LIGHT);
	ImGui::SliderFloat("Y Position Light", &_lightPosition.y, MIN_Y_POSITION_LIGHT, MAX_Y_POSITION_LIGHT);
	ImGui::SliderFloat("Z Position Light", &_lightPosition.z, MIN_Z_POSITION_LIGHT, MAX_Z_POSITION_LIGHT);

	ImGui::SliderFloat("Radiant Power", &_radiantPower, MIN_RADIANT_POWER, MAX_RADIANT_POWER);

	ImGui::SliderFloat("Color Red", &_lightColor.r, MIN_RED_COLOR, MAX_RED_COLOR);
	ImGui::SliderFloat("Color Green", &_lightColor.g, MIN_GREEN_COLOR, MAX_GREEN_COLOR);
	ImGui::SliderFloat("Color Blue", &_lightColor.b, MIN_BLUE_COLOR, MAX_BLUE_COLOR);
	ImGui::SliderFloat("Color Alpha", &_lightColor.w, MIN_ALPHA_COLOR, MAX_ALPHA_COLOR);

	ImGui::SliderFloat("Ambient Coefficient", &_ambientReflectionCoefficient, MIN_AMBIENT_COEFFICIENT, MAX_AMBIENT_COEFFICIENT);
	ImGui::SliderFloat("Diffuse Coefficient", &_diffuseReflectionCoefficient, MIN_DIFFUSE_COEFFICIENT, MAX_DIFFUSE_COEFFICIENT);
	ImGui::SliderFloat("Specular Coefficient", &_specularReflectionCoefficient, MIN_SPECULAR_COEFFICIENT, MAX_SPECULAR_COEFFICIENT);

	ImGui::SliderFloat("Shininess Coefficient", &_shininessCoefficient, MIN_SHININESS_COEFFICIENT, MAX_SHININESS_COEFFICIENT);
}
