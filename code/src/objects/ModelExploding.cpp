#include "objects/ModelExploding.h"
#include <iostream>


ModelExploding::ModelExploding(char* modelPath, char* shaderPath, glm::vec3 position, float angle, glm::vec3 rotation, glm::vec3 scale)
	: Model(modelPath, shaderPath, position, angle, rotation, scale)
{
}

void ModelExploding::SetupProgram(std::string shaderPath)
{
	Model::SetupProgram(shaderPath);
	std::string geometryPath = std::string("shaders/explode").append(".geom");
	program->compileAndAttachShader(geometryPath.c_str(), GL_GEOMETRY_SHADER, "geometry");

}

void ModelExploding::SetupUniformsModel()
{
	Model::SetupUniformsModel();
	if (explode) {
		explosionTime += dt;
	}
	else {
		explosionTime = false;
	}
	glUniform1f(program->getUniform("time"), explosionTime * explosionSpeed);
}
