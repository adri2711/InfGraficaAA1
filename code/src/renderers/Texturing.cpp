#include <renderers/Texturing.h>

Texturing::Texturing(int width, int height) : Renderer(width, height)
{
	textureObject = new TexturePlane(glm::vec3(0.f, 0.f, -3.0f), 0.f, glm::vec3(1.f, 1.f, 1.f), glm::vec3(1.f, 1.f, 1.f));
}

Texturing::~Texturing()
{
	delete textureObject;
}

void Texturing::render(float dt)
{
	textureObject->SetObjectMatrix(textureObject->GetTranslationMatrix() * textureObject->GetRotationMatrix());
	textureObject->setCam(_cam);
	textureObject->draw(dt, glm::vec3(), glm::vec3(), 0.f, 0.f, 0.f, 0.f, 0.f);
}