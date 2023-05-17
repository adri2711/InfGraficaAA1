#include <renderers/Texturing.h>

Texturing::Texturing(int width, int height) : Renderer(width, height)
{
	//textureObject = new TexturePlane();
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