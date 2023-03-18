#pragma once
#include <GL/glew.h>
#include <glm\gtc\type_ptr.hpp>
#include <Program.h>
#include <renderers/Renderer.h>

#include "Object.h"

class Cube : public Object
{
public:
	Cube(glm::vec3 position);
	~Cube();
	void draw() override;
	
private:
	GLuint VAO;
	GLuint VBO[3];
	Program* program;

	glm::mat4 objMat;
	CameraTransforms cam;
	glm::vec4 color;

	const int numVerts = 24 + 6; // 4 vertex/face * 6 faces + 6 PRIMITIVE RESTART
};
