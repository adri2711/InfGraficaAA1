#pragma once
#include <vector>
#include "glm//glm.hpp"
#include <GL/glew.h>
#include <glm\gtc\type_ptr.hpp>
#include <Program.h>
#include <renderers/Renderer.h>

#include "Object.h"

class Model : public Object
{
public:
	Model(const char* modelPath, const char* shaderPath, glm::vec3 view, float angle, glm::vec3 model, glm::vec3 projection);
	Model(const char* modelPath, const char* shaderPath, glm::vec3 view, glm::vec3 projection);
	Model(const char* modelPath, const char* shaderPath, glm::vec3 view);
	void InitModel(const char* modelPath, const char* shaderPath);
	~Model();
	bool loadOBJ(const char* path);

	std::vector< glm::vec3 > GetVertices();
	std::vector< glm::vec2 > GetUvs();
	std::vector< glm::vec3 > GetNormals();
	void draw() override;
	
private:
	bool loadOBJ(const char* path, std::vector < glm::vec3 >& out_vertices, std::vector < glm::vec2 >& out_uvs, std::vector < glm::vec3 >& out_normals);

	const int numVerts = 24 + 6; // 4 vertex/face * 6 faces + 6 PRIMITIVE RESTART
};

