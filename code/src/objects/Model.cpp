#pragma warning(disable: 4996)
#include "objects/Model.h"
#include "stb_image.h"

Model::Model(const char* modelPath, const char* shaderPath, glm::vec3 position, float angle, glm::vec3 rotation,
             glm::vec3 scale): Object(position, angle, rotation, scale)
{
	InitModel(modelPath, shaderPath);
}

Model::Model(const char* modelPath, const char* shaderPath, glm::vec3 position, glm::vec3 scale): Object(position, scale)
{
	InitModel(modelPath, shaderPath);
}

Model::Model(const char* modelPath, const char* shaderPath, glm::vec3 position): Object(position)
{
	InitModel(modelPath, shaderPath);
}

Model::Model(const char* modelPath, const char* shaderPath): Object()
{
	InitModel(modelPath, shaderPath);
}

void Model::InitModel(const char* modelPath, const char* shaderPath)
{
	std::string vertexPath = std::string(shaderPath).append(".vert");
	std::string fragmentPath = std::string(shaderPath).append(".frag");

	loadOBJ(modelPath, vertices, uvs, normals);
	// Initialize program
	program = new Program("Model");
	program->compileAndAttachShader(vertexPath.c_str(), GL_VERTEX_SHADER, "vertex");
	program->compileAndAttachShader(fragmentPath.c_str(), GL_FRAGMENT_SHADER, "fragment");

	// Bind Attrib locations
	program->bindAttribLocation(0, "in_Position");
	program->bindAttribLocation(1, "in_Normal");

	// Link program
	program->link();

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


Model::~Model()
{
	glDeleteBuffers(3, VBO);
	glDeleteVertexArrays(1, &VAO);
	delete program;
}

void Model::loadOBJ(const char* path, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals)
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

std::vector< glm::vec3 > Model::GetVertices()
{
	return vertices;
}

std::vector<glm::vec3> Model::GetNormals()
{
	return normals;
}

std::vector<glm::vec2> Model::GetUvs()
{
	return uvs;
}

void Model::draw(glm::vec3 lightPosition, glm::vec3 lightColor, float radiantPower, float ambientReflectionCoefficient, float diffuseReflectionCoefficient, float specularReflectionCoefficient, float shininessCoefficient)
{
	glBindVertexArray(VAO);
	program->use();

	float radiantEffect = radiantPower / (4.f * glm::pi<float>());
    
	glUniformMatrix4fv(
		program->getUniform("objectMatrix"),
		1, GL_FALSE, glm::value_ptr(_objectMatrix)
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

	glUniform3f(program->getUniform("_lightColor"), lightColor.r, lightColor.g, lightColor.b);

	glUniform3f(program->getUniform("_lightPosition"), lightPosition.x, lightPosition.y, lightPosition.z);

	glUniform1f(program->getUniform("_shininessCoefficient"), shininessCoefficient);

	glUniform1f(program->getUniform("_ambientReflectionCoefficient"), ambientReflectionCoefficient);

	glUniform1f(program->getUniform("_diffuseReflectionCoefficient"), diffuseReflectionCoefficient);

	glUniform1f(program->getUniform("_specularReflectionCoefficient"), specularReflectionCoefficient);

	glUniform1f(program->getUniform("_radiantEffect"), radiantEffect);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	program->unuse();
	glBindVertexArray(0);
}