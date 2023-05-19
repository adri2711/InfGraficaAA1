#include "renderers/AA1.h"

AA1::AA1(int width, int height) : Renderer(width, height)
{
	_ambientReflectionCoefficient = 0.5f;
	_diffuseReflectionCoefficient = 0.5f;
	_specularReflectionCoefficient = 0.5f;
	_shininessCoefficient = 1;
	//fovMin = FOV;
	//fovMax = glm::radians(120.f);
	_lightPosition = glm::vec3(0.0f, 2.3f, -3.0f);
	catModel = new ModelExploding("resources/a_man.obj", "shaders/Model", glm::vec3(0.0f, -0.3f, -3.0f), 0.f, glm::vec3(1.f, 1.f, 1.f), glm::vec3(1.f, 1.f, 1.f));
	catModel->InitModel();
	billboard = new Billboard(1, "resources/texture1.jpg", "shaders/Billboard", glm::vec3(3.0f, 0.f, -3.0f), 0.f, glm::vec3(1.f, 1.f, 1.f), glm::vec3(1.f, 1.f, 1.f));
	billboard->Init();

	_cubePosition = glm::vec3(-3.f, 0.f, -3.f);

	glm::vec3 vertexs[] = {

		glm::vec3(-0.5f, -0.5f, -0.5f) + _cubePosition, // Bottom Back Left
		glm::vec3(-0.5f, -0.5f, 0.5f) + _cubePosition, // Bottom Front Left
		glm::vec3(0.5f, -0.5f, 0.5f) + _cubePosition, // Bottom Front Right
		glm::vec3(0.5f, -0.5f, -0.5f) + _cubePosition, //Bottom Back Right
		glm::vec3(-0.5f, 0.5f, -0.5f) + _cubePosition, // Top Back Left
		glm::vec3(-0.5f, 0.5f, 0.5f) + _cubePosition, // Top Front Left
		glm::vec3(0.5f, 0.5f, 0.5f) + _cubePosition, // Top Front Right
		glm::vec3(0.5f, 0.5f, -0.5f) + _cubePosition// Top Back Right
	};

	glm::vec3 bottomPlane[] = { vertexs[2], vertexs[1], vertexs[0], vertexs[3] };
	glm::vec3 topPlane[] = {vertexs[7], vertexs[4], vertexs[5], vertexs[6]};
	glm::vec3 leftPlane[] = { vertexs[5], vertexs[4], vertexs[0], vertexs[1] };
	glm::vec3 rightPlane[] = { vertexs[7], vertexs[6], vertexs[2], vertexs[3] };
	glm::vec3 frontPlane[] = { vertexs[6], vertexs[5], vertexs[1], vertexs[2] };
	glm::vec3 backPlane[] = { vertexs[7], vertexs[4], vertexs[0], vertexs[3] };

	texture.push_back(new TexturePlane(bottomPlane, glm::vec3(0, -1, 0)));
	texture.push_back(new TexturePlane(topPlane, glm::vec3(0, 1, 0)));
	texture.push_back(new TexturePlane(leftPlane, glm::vec3(-1, 0, 0)));
	texture.push_back(new TexturePlane(rightPlane, glm::vec3(1, 0, 0)));
	texture.push_back(new TexturePlane(frontPlane, glm::vec3(0, 0, 1)));
	texture.push_back(new TexturePlane(backPlane, glm::vec3(0, 0, -1)));
	
	SetTexturesMultiple();
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

void AA1::SetTexturesSingle()
{
	for (int i = 0; i < 6; i++) {
		texture[i]->SetTexture("resources/texture1.jpg");
	}
}

void AA1::SetTexturesMultiple()
{
	for (int i = 0; i < 6; i++) {
		std::string p = "resources/texturex.jpg";
		p[17] = i + '0';
		texture[i]->SetTexture(p);
	}
}

void AA1::render(float dt)
{	
	RenderCat(dt);
	RenderTexture(dt);
	RenderBillboard(dt);
	RenderPointLight(dt);
	RenderLightEmissor(dt);
	//RenderScenario(dt);
}

void AA1::RenderTexture(float dt) {
	for (int i = 0; i < 6; i++) {
		texture[i]->setCam(_cam);
		texture[i]->draw(dt, _lightPosition, _lightColor, _radiantPower, _ambientReflectionCoefficient, _diffuseReflectionCoefficient, _specularReflectionCoefficient, _shininessCoefficient);
	}
}

void AA1::RenderBillboard(float dt)
{
	billboard->SetObjectMatrix(billboard->GetTranslationMatrix());
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
	if (ImGui::Button("Boom")) {
		catModel->explode = !catModel->explode;
	}
	if (ImGui::Button("Toggle Cube Textures")) {
		cubeMultiple = !cubeMultiple;
		if (cubeMultiple) {
			SetTexturesMultiple();
		}
		else {
			SetTexturesSingle();
		}
	}

	ImGui::SliderFloat("X Position Light", &_lightPosition.x, MIN_X_POSITION_LIGHT, MAX_X_POSITION_LIGHT);
	ImGui::SliderFloat("Y Position Light", &_lightPosition.y, MIN_Y_POSITION_LIGHT, MAX_Y_POSITION_LIGHT);
	ImGui::SliderFloat("Z Position Light", &_lightPosition.z, MIN_Z_POSITION_LIGHT, MAX_Z_POSITION_LIGHT);

	ImGui::SliderFloat("Radiant Power", &_radiantPower, MIN_RADIANT_POWER, MAX_RADIANT_POWER);

	ImGui::SliderFloat("Light Color Red", &_lightColor.r, MIN_RED_COLOR, MAX_RED_COLOR);
	ImGui::SliderFloat("Light Color Green", &_lightColor.g, MIN_GREEN_COLOR, MAX_GREEN_COLOR);
	ImGui::SliderFloat("Light Color Blue", &_lightColor.b, MIN_BLUE_COLOR, MAX_BLUE_COLOR);

	ImGui::SliderFloat("Ambient Coefficient", &_ambientReflectionCoefficient, MIN_AMBIENT_COEFFICIENT, MAX_AMBIENT_COEFFICIENT);
	ImGui::SliderFloat("Diffuse Coefficient", &_diffuseReflectionCoefficient, MIN_DIFFUSE_COEFFICIENT, MAX_DIFFUSE_COEFFICIENT);
	ImGui::SliderFloat("Specular Coefficient", &_specularReflectionCoefficient, MIN_SPECULAR_COEFFICIENT, MAX_SPECULAR_COEFFICIENT);

	ImGui::SliderFloat("Shininess Coefficient", &_shininessCoefficient, MIN_SHININESS_COEFFICIENT, MAX_SHININESS_COEFFICIENT);
}
