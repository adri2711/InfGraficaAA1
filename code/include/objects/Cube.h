#pragma once
#include <GL/glew.h>
#include <glm\gtc\type_ptr.hpp>
#include <Program.h>
#include <renderers/Renderer.h>

#include "Object.h"

class Cube : public Object
{
public:
	Cube(const char* shaderPath, glm::vec3 position, glm::vec3 scale, float x = 1.f, float y = 1.f, float z = 1.f);
	~Cube();
	void SetTransforms(glm::mat4 objectMatrix, CameraTransforms cam);
	void draw(float dt) override;
	
private:

	const int numVerts = 24 + 6; // 4 vertex/face * 6 faces + 6 PRIMITIVE RESTART
};
