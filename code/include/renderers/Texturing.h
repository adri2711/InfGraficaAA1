#pragma once
#include "Renderer.h"
#include <objects/Cube.h>
#include "objects/TexturePlane.h"


class Texturing : public Renderer
{
	TexturePlane* textureObject;

protected:

	void render(float dt);


public:
	Texturing(int width, int height);
	~Texturing();
};