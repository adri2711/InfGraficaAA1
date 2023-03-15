#pragma once
#include <vector>
#include <string>
#include "glm//glm.hpp"
#include <GL/glew.h>
#include <glm\gtc\type_ptr.hpp>
#include <Program.h>
#include <renderers/Renderer.h>
class Model
{
public:
	Model(const char* path);
	~Model();
	bool loadOBJ(const char* path);
	void setTransforms(glm::mat4 objMat, CameraTransforms cam);
	void setColor(glm::vec4 color);
	void draw();
private:
	bool loadOBJ(const char* path, std::vector < glm::vec3 >& out_vertices, std::vector < glm::vec2 >& out_uvs, std::vector < glm::vec3 >& out_normals);
	GLuint VAO;
	GLuint VBO[3];
	Program* program;

	glm::mat4 objMat;
	CameraTransforms cam;
	glm::vec4 color;

	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals; // Won't be used at the moment.

	const int numVerts = 24 + 6; // 4 vertex/face * 6 faces + 6 PRIMITIVE RESTART
};

