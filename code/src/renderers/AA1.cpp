#include "renderers/AA1.h"

AA1::AA1(int width, int height) : Renderer(width, height)
{
	//fovMin = FOV;
	//fovMax = glm::radians(120.f);
	_lightPosition = glm::vec3(0.0f, 2.3f, -3.0f);
	catModel = new ModelExploding("resources/a_man.obj", "shaders/Model", glm::vec3(0.0f, -0.3f, -3.0f), 0.f, glm::vec3(1.f, 1.f, 1.f), glm::vec3(1.f, 1.f, 1.f));
	catModel->InitModel();
	billboard = new Billboard(3, "resources/container.jpg", "shaders/Billboard", glm::vec3(3.0f, 0.f, -3.0f), 0.f, glm::vec3(1.f, 1.f, 1.f), glm::vec3(1.f, 1.f, 1.f));
	billboard->Init();
	_pointLight = new PointLight(20, _lightPosition);
	_lightEmissor = new Cube("shaders/Cube", _lightPosition, glm::vec3(1.f, 1.f, 1.f));
	floor = new Cube("shaders/Cube", _lightPosition, glm::vec3(15.f, 1.f, 15.f), 15.f, 1.f, 15.f);
	building = new Cube("shaders/Cube", _lightPosition, glm::vec3(5.f, 11.f, 15.f), 5.f, 11.f, 5.f);
	_lightColor = glm::vec3(1,1,1);
}

AA1::~AA1()
{
	delete catModel;
	delete billboard;
	delete _pointLight;
	delete _lightEmissor;
	delete _auxCube;
}

void AA1::render(float dt)
{	
	RenderCat(dt);
	RenderBillboard(dt);
	RenderPointLight(dt);
	RenderLightEmissor(dt);
	//RenderScenario(dt);
}

void AA1::RenderBillboard(float dt)
{
	billboard->SetObjectMatrix(billboard->GetTranslationMatrix() * billboard->GetRotationMatrix());
	billboard->setCam(_cam);
	billboard->draw(dt, _lightPosition, _lightColor, _radiantPower, _ambientReflectionCoefficient, _diffuseReflectionCoefficient, _specularReflectionCoefficient, _shininessCoefficient);
}

void AA1::RenderCat(float dt)
{
	//catModel->Move(_globalPosition);
	catModel->Rotate((int)(elapsedTime * speed) % 360, glm::vec3(0.0f, 1.0f, 0.0f));
	catModel->SetObjectMatrix(catModel->GetTranslationMatrix() * catModel->GetRotationMatrix());
	catModel->setCam(_cam);
	catModel->draw(dt, _lightPosition, _lightColor, _radiantPower, _ambientReflectionCoefficient, _diffuseReflectionCoefficient, _specularReflectionCoefficient, _shininessCoefficient);

}

void AA1::RenderPointLight(float dt)
{
	_pointLight->Move(_lightPosition);
	_pointLight->SetObjectMatrix(_pointLight->GetTranslationMatrix());
}

void AA1::RenderLightEmissor(float dt)
{
	_lightEmissor->Move(_lightPosition);
	_lightEmissor->SetObjectMatrix(_lightEmissor->GetTranslationMatrix());
	_lightEmissor->setColor(glm::vec3(_lightColor.r, _lightColor.g, _lightColor.b));	
	_lightEmissor->setCam(_cam);
	_lightEmissor->draw(dt, _lightPosition, _lightColor, _radiantPower, _ambientReflectionCoefficient, _diffuseReflectionCoefficient, _specularReflectionCoefficient, _shininessCoefficient);
}

void AA1::RenderScenario(float dt)
{
	glm::mat4 view, objMat;
	
	view = glm::translate(glm::mat4(), _globalPosition + glm::vec3(0.f,-1.f,0.f));
	objMat = view;
	floor->SetTransforms(objMat, _cam);
	floor->setColor(glm::vec4(.1f,.3f,.3f,1.f));
	floor->draw(dt, glm::vec3(), glm::vec4(), 0, 0, 0,0, 0);

	view = glm::translate(glm::mat4(), _globalPosition + glm::vec3(-5.f,2.f,-5.f));
	objMat = view;
	building->SetTransforms(objMat, _cam);
	building->setColor(glm::vec4(.5f,.3f,.1f,1.f));
	building->draw(dt, glm::vec3(), glm::vec4(), 0, 0, 0,0, 0);
}

void AA1::renderGUI()
{

	ImGui::SliderFloat("X Position Light", &_lightPosition.x, MIN_X_POSITION_LIGHT, MAX_X_POSITION_LIGHT);
	ImGui::SliderFloat("Y Position Light", &_lightPosition.y, MIN_Y_POSITION_LIGHT, MAX_Y_POSITION_LIGHT);
	ImGui::SliderFloat("Z Position Light", &_lightPosition.z, MIN_Z_POSITION_LIGHT, MAX_Z_POSITION_LIGHT);

	ImGui::SliderFloat("Radiant Power", &_radiantPower, MIN_RADIANT_POWER, MAX_RADIANT_POWER);

	ImGui::SliderFloat("Light Color Red", &_lightColor.r, MIN_RED_COLOR, MAX_RED_COLOR);
	ImGui::SliderFloat("Light Color Green", &_lightColor.g, MIN_GREEN_COLOR, MAX_GREEN_COLOR);
	ImGui::SliderFloat("Light Color Blue", &_lightColor.b, MIN_BLUE_COLOR, MAX_BLUE_COLOR);

	ImGui::SliderFloat("Cat Color Red", &catModel->color.r, MIN_RED_COLOR, MAX_RED_COLOR);
	ImGui::SliderFloat("Cat Color Green", &catModel->color.g, MIN_GREEN_COLOR, MAX_GREEN_COLOR);
	ImGui::SliderFloat("Cat Color Blue", &catModel->color.b, MIN_BLUE_COLOR, MAX_BLUE_COLOR);

	ImGui::SliderFloat("Ambient Coefficient", &_ambientReflectionCoefficient, MIN_AMBIENT_COEFFICIENT, MAX_AMBIENT_COEFFICIENT);
	ImGui::SliderFloat("Diffuse Coefficient", &_diffuseReflectionCoefficient, MIN_DIFFUSE_COEFFICIENT, MAX_DIFFUSE_COEFFICIENT);
	ImGui::SliderFloat("Specular Coefficient", &_specularReflectionCoefficient, MIN_SPECULAR_COEFFICIENT, MAX_SPECULAR_COEFFICIENT);

	ImGui::SliderFloat("Shininess Coefficient", &_shininessCoefficient, MIN_SHININESS_COEFFICIENT, MAX_SHININESS_COEFFICIENT);
	if (ImGui::Button("Boom")) {
		catModel->explode = !catModel->explode;
	}
}
