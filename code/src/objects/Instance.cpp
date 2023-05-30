#pragma warning(disable: 4996)
#include "objects/Instance.h"
#include "glm/gtx/string_cast.hpp"
#include <iostream>

Instance::Instance(char* modelPath, char* shaderPath, int carsNum)
{    
	loadOBJ(modelPath, vertices, uvs, normals);

	SetupProgram(shaderPath);
	program->link();

	SetupProgramNormal(shaderPath);
	programNormal->link();

	SetupBuffers();

    for (int i = 0; i < carsNum; ++i)
    {
        _cars.push_back(Model("resources/cotxe.obj", "shaders/Model", glm::vec3(0.0f, -0.3f, -3.0f), 0.f, glm::vec3(0.f, 1.f, 0.f), glm::vec3(.3f, .3f, .3f)));
        _cars[i].elapsedTime = 100 - (100 / carsNum) * i;
    }
}

Instance::~Instance()
{
}

void Instance::loadOBJ(const char* path, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals)
{
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;
	FILE* file = fopen(path, "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return;
	}

	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader
		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		out_vertices.push_back(vertex);
	}
	for (unsigned int i = 0; i < normalIndices.size(); i++) {
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 normal = temp_normals[normalIndex - 1];
		out_normals.push_back(normal);
	}
	for (unsigned int i = 0; i < uvIndices.size(); i++) {
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		out_uvs.push_back(uv);
	}
	fclose(file);
}


void Instance::SetupProgram(std::string shaderPath)
{
	std::string vertexPath = std::string(shaderPath).append(".vert");
	std::string fragmentPath = std::string(shaderPath).append(".frag");

	// Initialize program
	program = new Program("Instance");
	program->compileAndAttachShader(vertexPath.c_str(), GL_VERTEX_SHADER, "vertex");
	program->compileAndAttachShader(fragmentPath.c_str(), GL_FRAGMENT_SHADER, "fragment");

	// Bind Attrib locations
	program->bindAttribLocation(0, "in_Position");
	program->bindAttribLocation(1, "in_Normal");
}

void Instance::SetupProgramNormal(std::string shaderPath)
{
	programNormal = new Program("Normal");

	std::string vertexPath = std::string("shaders/Normal").append(".vert");
	std::string geometryPath = std::string("shaders/Normal").append(".geom");
	std::string fragmentPath = std::string("shaders/Normal").append(".frag");

	programNormal->compileAndAttachShader(vertexPath.c_str(), GL_VERTEX_SHADER, "vertex");
	programNormal->compileAndAttachShader(geometryPath.c_str(), GL_GEOMETRY_SHADER, "geometry");
	programNormal->compileAndAttachShader(fragmentPath.c_str(), GL_FRAGMENT_SHADER, "fragment");

	programNormal->bindAttribLocation(0, "in_Position");
	programNormal->bindAttribLocation(1, "in_Normal");
}

void Instance::SetupBuffers()
{
	// Initialize buffers
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(2, VBO);
	//glGenBuffers(1, &EBO);	

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, );

	int imageWidth, imageHeight, numberChannels;
	unsigned char* data = stbi_load( "", &imageHeight, &imageHeight, &numberChannels, 0);*/

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Instance::Race(float carSpeed, float carTrajectoryRadius, bool changeView, float* panv, float* rota, CameraTransforms cam, float dt)
{

    for (int i = 0; i < _cars.size(); i++) {
        float speed = carSpeed / carTrajectoryRadius;
        float t = _cars[i].elapsedTime * speed;
        float a = glm::radians(t);
        glm::vec3 position = glm::vec3(cos(a) * carTrajectoryRadius, -0.8f, sin(a) * carTrajectoryRadius);
        int rotation = ((int)t * 1000 % 360000) / 1000.f;
        _cars[i].Move(position);
        _cars[i].Rotate(rotation, glm::vec3(0.f, 1.f, 0.f));		
		
        if (i == 0)
        {
            if (changeView)
            {
                panv[0] = position.x;
                panv[1] = position.y;
                panv[2] = position.z;
			
                rota[0] = glm::radians((float)rotation);
				rota[1] = 0;
            }
        }

		_cars[i].SetObjectMatrix(_cars[i].GetTranslationMatrix()* _cars[i].GetRotationMatrix()* _cars[i].GetScaleMatrix());
		_cars[i].elapsedTime += dt;
		_objectMatrixArray[i] = _cars[i].GetObjectMatrix();
    }

	setCam(cam);
		
	draw(dt);

}

void Instance::draw(float dt)
{

	glBindVertexArray(VAO);

	program->use();
	SetupUniformsModel();
	glDrawArraysInstanced(GL_TRIANGLES, 0, vertices.size(), _cars.size());
	program->unuse();

	glBindVertexArray(0);
}

void Instance::SetupUniformsModel()
{

    glUniformMatrix4fv(
        program->getUniform("objectMatrixArray"),
        _cars.size(), GL_FALSE, glm::value_ptr(_objectMatrixArray[0])
    );
    glUniformMatrix4fv(
        program->getUniform("mv_Matrix"),
        1, GL_FALSE, glm::value_ptr(_cam._modelView)
    );
    glUniformMatrix4fv(
        program->getUniform("mvpMatrix"),
        1, GL_FALSE, glm::value_ptr(_cam._MVP)
    );
    glUniform3f(
        program->getUniform("color"),
        color.r, color.g, color.b
    );
}