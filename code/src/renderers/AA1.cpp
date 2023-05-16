#include "renderers/AA1.h"

AA1::AA1(int width, int height) : Renderer(width, height)
{
	floor = new TexturePlane("resources/ground.jpg", glm::vec3(0.f, -1.f, 0.f), 90.f, glm::vec3(1.f, 0.f, 0.f), glm::vec3(100.f, 100.f, 1.f));
	cars = new ModelExploding("resources/a_man.obj", "shaders/Model", glm::vec3(0.0f, -0.3f, -3.0f), 0.f, glm::vec3(1.f, 1.f, 1.f), glm::vec3(1.f, 1.f, 1.f));
	cars[0].InitModel();
}

AA1::~AA1()
{
}

void AA1::render(float dt)
{	
	floor->SetObjectMatrix(floor->GetTranslationMatrix() * floor->GetRotationMatrix() * floor->GetScaleMatrix());
	floor->setCam(_cam);
	floor->draw(dt);

	cars[0].SetObjectMatrix(cars[0].GetTranslationMatrix() * cars[0].GetRotationMatrix());
	cars[0].setCam(_cam);
	cars[0].draw(dt);
}

void AA1::renderGUI()
{

}
