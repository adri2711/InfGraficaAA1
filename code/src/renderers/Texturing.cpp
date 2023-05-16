#include <renderers/Texturing.h>

Texturing::Texturing(int width, int height) : Renderer(width, height)
{
	textureObject = new TexturePlane("resources/ground.jpg", glm::vec3(0.f, -1.f, 0.f), 90.f, glm::vec3(1.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f));
}

Texturing::~Texturing()
{
	delete textureObject;
}

void Texturing::render(float dt)
{
	textureObject->SetObjectMatrix(textureObject->GetTranslationMatrix() * textureObject->GetRotationMatrix());
	textureObject->setCam(_cam);
	textureObject->draw(dt);
}