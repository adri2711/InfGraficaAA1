#include "objects/Billboard.h"

Billboard::Billboard(float size, char* texturePath, char* shaderPath, glm::vec3 position, float angle, glm::vec3 rotation, glm::vec3 scale)
	: Object(position, angle, rotation, scale)
{
	this->size = size;
}

Billboard::~Billboard()
{
}

void Billboard::draw(float dt, glm::vec3 lightPosition, glm::vec3 lightColor, float radiantPower, float ambientReflectionCoefficient, float diffuseReflectionCoefficient, float specularReflectionCoefficient, float shininessCoefficient)
{

}
