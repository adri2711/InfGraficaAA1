#pragma once
#include <GL/glew.h>
#include <glm\gtc\type_ptr.hpp>
#include <Program.h>
#include <renderers/Renderer.h>

#include "Object.h"

class Cube : public Object
{
public:
	Cube(const char* shaderPath, glm::vec3 position, glm::vec3 scale);
	~Cube();
	void draw(glm::vec3 lightPosition, glm::vec4 lightColor, float radiantPower, float ambientReflectionCoefficient, float diffuseReflectionCoefficient, float specularReflectionCoefficient) override;
	
private:

	const int numVerts = 24 + 6; // 4 vertex/face * 6 faces + 6 PRIMITIVE RESTART
};
