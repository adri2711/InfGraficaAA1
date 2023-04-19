#include "objects/ModelExploding.h"

ModelExploding::ModelExploding(const char* modelPath, const char* shaderPath, glm::vec3 position, float angle, glm::vec3 rotation, glm::vec3 scale)
	: Model(modelPath, shaderPath, position, angle, rotation, scale)
{
}
