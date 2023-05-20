#include "renderers/AA1.h"

AA1::AA1(int width, int height) : Renderer(width, height)
{
	srand(time(NULL));

	floor = new TexturePlane("resources/ground.jpg", glm::vec3(0.f, -1.f, 0.f), 90.f, glm::vec3(1.f, 0.f, 0.f), glm::vec3(100.f, 100.f, 1.f));
	for (int i = 0; i < treeAmount; i++) {
		std::string path = "resources/trees/treex.jpg";
		path[20] = rand() % 10 + '0';
		char* pathc = (char*)path.c_str();
		glm::vec3 pos;
		do {
			pos = glm::vec3(float(rand() % playArea) * 2.f - playArea, 2.4f, float(rand() % playArea) * 2.f - playArea);
		} while (vec3Modulo(pos) < carTrajectoryRadius * 1.2f && vec3Modulo(pos) > carTrajectoryRadius * 0.8f);
		Billboard temp = Billboard(8.f, pathc, "shaders/Billboard", pos, 0.f, glm::vec3(0.f, 1.f, 0.f), glm::vec3(1.f, 1.f, 1.f));
		trees.push_back(temp);
		trees.back().Init();
	}
}

float AA1::vec3Modulo(glm::vec3 in) {
	return glm::sqrt(in.x * in.x + in.y * in.y + in.z * in.z);
}

AA1::~AA1()
{
}

void AA1::render(float dt)
{	
	floor->SetObjectMatrix(floor->GetTranslationMatrix() * floor->GetRotationMatrix() * floor->GetScaleMatrix());
	floor->setCam(_cam);
	floor->draw(dt);

	carTimer -= dt;
	if (carTimer <= 0 && cars.size() < maxCars) {
		Model tempm = Model("resources/cotxe.obj", "shaders/Model", glm::vec3(0.0f, -0.3f, -3.0f), 0.f, glm::vec3(1.f, 1.f, 1.f), glm::vec3(.3f, .3f, .3f));
		cars.push_back(tempm);
		cars.back().InitModel();
		carTimer = rand() % 2 + 1.f;
	}

	for (int i = 0; i < trees.size(); i++) {
		trees[i].SetObjectMatrix(trees[i].GetTranslationMatrix() * trees[i].GetRotationMatrix() * trees[i].GetScaleMatrix());
		trees[i].setCam(_cam);
		trees[i].draw(dt);
	}

	for (int i = 0; i < cars.size(); i++) {
		float speed = carSpeed / carTrajectoryRadius;
		float t = cars[i].elapsedTime * speed;
		float a = glm::radians(t);
		cars[i].Move(glm::vec3(cos(a) * carTrajectoryRadius, 0.f, sin(a) * carTrajectoryRadius));
		cars[i].Rotate(((int)t * 1000 % 360000) / 1000.f, glm::vec3(0.f, 1.f, 0.f));
		cars[i].SetObjectMatrix(cars[i].GetTranslationMatrix() * cars[i].GetRotationMatrix() * cars[i].GetScaleMatrix());
		cars[i].setCam(_cam);
		cars[i].draw(dt);
	}
}

void AA1::renderGUI()
{

}
