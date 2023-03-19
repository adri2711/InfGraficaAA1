#pragma once
#include <vector>
#include "glm//glm.hpp"
#include <glm\gtc\type_ptr.hpp>

#include "Object.h"

class Model : public Object
{
public:
	Model(const char* modelPath, const char* shaderPath, glm::vec3 position, float angle, glm::vec3 rotation, glm::vec3 scale);
	Model(const char* modelPath, const char* shaderPath, glm::vec3 position, glm::vec3 scale);
	Model(const char* modelPath, const char* shaderPath, glm::vec3 position);
	Model(const char* modelPath, const char* shaderPath);
	void InitModel(const char* modelPath, const char* shaderPath);
	~Model();

	std::vector< glm::vec3 > GetVertices();
	std::vector< glm::vec2 > GetUvs();
	std::vector< glm::vec3 > GetNormals();
	void draw() override;
	
private:
	bool loadOBJ(const char* path, std::vector < glm::vec3 >& out_vertices, std::vector < glm::vec2 >& out_uvs, std::vector < glm::vec3 >& out_normals);

	const int numVerts = 24 + 6; // 4 vertex/face * 6 faces + 6 PRIMITIVE RESTART
};

