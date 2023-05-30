#include "renderers/AA1.h"
#include "glm/gtx/string_cast.hpp"

AA1::AA1(int width, int height) : Renderer(width, height)
{
	srand(time(NULL));	

	int catSpawn = rand() % treeAmount;

	floor = new TexturePlane("resources/ground.jpg", glm::vec3(0.f, -1.f, 0.f), 90.f, glm::vec3(1.f, 0.f, 0.f), glm::vec3(100.f, 100.f, 1.f));
	for (int i = 0; i < treeAmount; i++) {
		std::string path = "resources/trees/treex.png";
		path[20] = rand() % 3 + '0';
		char* pathc = (char*)path.c_str();
		glm::vec3 pos;
		do {
			pos = glm::vec3(float(rand() % playArea) * 2.f - playArea, 4.0f, float(rand() % playArea) * 2.f - playArea);
		} while (vec3Modulo(pos) < carTrajectoryRadius * 1.2f && vec3Modulo(pos) > carTrajectoryRadius * 0.8f);
		if (i == catSpawn)
		{
			_cat = new Model("resources/a_man.obj", "shaders/Model", pos, glm::vec3(4.f, 4.f, 4.f));
			_cat->InitModel();
		}
		else
		{
			Billboard temp = Billboard(10.f, pathc, "shaders/Billboard", pos, 0.f, glm::vec3(0.f, 1.f, 0.f), glm::vec3(1.f, 1.f, 1.f));
			trees.push_back(temp);
			trees.back().Init();
		}		
	}

	_instanceCar = new Instance("resources/cotxe.obj", "shaders/Instance", maxCars);
}

float AA1::vec3Modulo(glm::vec3 in) {
	return glm::sqrt(in.x * in.x + in.y * in.y + in.z * in.z);
}

AA1::~AA1()
{
}

void AA1::render(float dt)
{
	_elapsedTime += dt;

	floor->SetObjectMatrix(floor->GetTranslationMatrix() * floor->GetRotationMatrix() * floor->GetScaleMatrix());
	floor->setCam(_cam);
	floor->draw(dt);

	for (int i = 0; i < trees.size(); i++) {
		trees[i].setCam(_cam);
		trees[i].draw(dt);
	}
	_cat->Rotate(float((int)(_elapsedTime * carSpeed) % 360), glm::vec3(0.0f, 1.0f, 0.0f));
	_cat->SetObjectMatrix(_cat->GetTranslationMatrix() * _cat->GetRotationMatrix() * _cat->GetScaleMatrix());
	_cat->setCam(_cam);
	_cat->draw(dt);

	if (_changeCharge)
	{
		_instanceCar->Race(carSpeed, carTrajectoryRadius, _changeView, panv, rota, _cam, dt);
	}
	else
	{
		if (carTimer <= 0 && _cars.size() < maxCars) {
			Model tempm = Model("resources/cotxe.obj", "shaders/Model", glm::vec3(0.0f, -0.3f, -3.0f), 0.f, glm::vec3(1.f, 1.f, 1.f), glm::vec3(.3f, .3f, .3f));
			_cars.push_back(tempm);
			_cars.back().InitModel();
			carTimer = rand() % 2 + 1.f;
		}

		for (int i = 0; i < _cars.size(); i++) {
			float speed = carSpeed / carTrajectoryRadius;
			float t = _cars[i].elapsedTime * speed;
			float a = glm::radians(t);
			glm::vec3 position = glm::vec3(cos(a) * carTrajectoryRadius, -0.8f, sin(a) * carTrajectoryRadius);
			int rotation = ((int)t * 1000 % 360000) / 1000.f;
			_cars[i].Move(position);
			_cars[i].Rotate(rotation, glm::vec3(0.f, 1.f, 0.f));

			if (i == 0)
			{
				if (_changeView)
				{					
					panv[0] = position.x;
					panv[1] = position.y;
					panv[2] = position.z;

					rota[0] = glm::radians((float)rotation);
					rota[1] = 0;
				}
			}

			_cars[i].SetObjectMatrix(_cars[i].GetTranslationMatrix() * _cars[i].GetRotationMatrix() * _cars[i].GetScaleMatrix());
			_cars[i].setCam(_cam);
			_cars[i].draw(dt);
		}
		carTimer -= dt;
	}
}

void AA1::renderGUI()
{
	if (ImGui::Button("Change View"))
	{
		_changeView = !_changeView;
		if (_changeView)
		{
			_lastCameraPosition[0] = panv[0];
			_lastCameraPosition[1] = panv[1];
			_lastCameraPosition[2] = panv[2];

			_lastCameraYRotation = rota[0];
			_lastCameraXRotation = rota[1];
		}
		else
		{
			panv[0] = _lastCameraPosition[0];
			panv[1] = _lastCameraPosition[1];
			panv[2] = _lastCameraPosition[2];

			rota[0] = _lastCameraYRotation;
			rota[1] = _lastCameraXRotation;
		}
	}

	if (ImGui::Button("Change Charge"))
	{
		_changeCharge = !_changeCharge;
	}
}