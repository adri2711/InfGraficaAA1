#include "objects/TexturePlane.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

TexturePlane::TexturePlane(glm::vec3 vertexPositions[], glm::vec3 normal) : Object()
{
	float vertices[]{
		//positions															 //texture coordinates
		vertexPositions[0][0], vertexPositions[0][1], vertexPositions[0][2], 1.f, 1.f, //top right
		vertexPositions[1][0], vertexPositions[1][1], vertexPositions[1][2], 0.f, 1.f, //top left 
		vertexPositions[2][0], vertexPositions[2][1], vertexPositions[2][2], 0.f, 0.f, //bottom left
		vertexPositions[3][0], vertexPositions[3][1], vertexPositions[3][2], 1.f, 0.f  //bottom right
	};
	unsigned int indices[]{

		0, 1, 3, //top triangle
		1, 2, 3  //bottom triangle	
	};

	glm::vec3 normals[]{normal, normal, normal, normal};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(3, VBO);

	glBindVertexArray(VAO);

	//Element Buffer Object
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	GenerateTexture();

	program = new Program("Square");
	program->compileAndAttachShader("shaders/texture.vert", GL_VERTEX_SHADER);
	program->compileAndAttachShader("shaders/texture.frag", GL_FRAGMENT_SHADER);

	program->bindAttribLocation(0, "in_Position");
	program->bindAttribLocation(1, "in_UV");
	program->bindAttribLocation(2, "in_Normal");

	program->link();

	glBindVertexArray(0);

	program->unuse();
}

void TexturePlane::SetTexture(std::string path) {
	texturePath = path;
	GenerateTexture();
}

void TexturePlane::GenerateTexture() {
	//Load image image un CPU
	int imageWidth, imageHeight, numberChannels;
	unsigned char* data = stbi_load(texturePath.c_str(), &imageWidth, &imageHeight, &numberChannels, 0);

	if (data)
	{
		//Generate texture
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	stbi_image_free(data);
}

TexturePlane::~TexturePlane()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO[0]);
	glDeleteBuffers(1, &VBO[1]);
	glDeleteTextures(1, &texture);
	delete program;
}

void TexturePlane::DrawTexture(glm::vec3 lightPosition, glm::vec3 lightColor, float radiantPower, float ambientReflectionCoefficient, float diffuseReflectionCoefficient, float specularReflectionCoefficient, float shininessCoefficient)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(VAO);
	program->use();

	float radiantEffect = radiantPower / (4.f * glm::pi<float>());

	glUniformMatrix4fv(
		program->getUniform("objMat"),
		1, GL_FALSE, glm::value_ptr(_objectMatrix)
	);
	glUniformMatrix4fv(
		program->getUniform("mv_Mat"),
		1, GL_FALSE, glm::value_ptr(_cam._modelView)
	);
	glUniformMatrix4fv(
		program->getUniform("mvpMat"),
		1, GL_FALSE, glm::value_ptr(_cam._MVP)
	);

	glUniform3f(program->getUniform("_lightColor"), lightColor.r, lightColor.g, lightColor.b);

	glUniform3f(program->getUniform("_lightPosition"), lightPosition.x, lightPosition.y, lightPosition.z);

	glUniform1f(program->getUniform("_shininessCoefficient"), shininessCoefficient);

	glUniform1f(program->getUniform("_ambientReflectionCoefficient"), ambientReflectionCoefficient);

	glUniform1f(program->getUniform("_diffuseReflectionCoefficient"), diffuseReflectionCoefficient);

	glUniform1f(program->getUniform("_specularReflectionCoefficient"), specularReflectionCoefficient);

	glUniform1f(program->getUniform("_radiantEffect"), radiantEffect);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	program->unuse();
	glBindVertexArray(0);
}

void TexturePlane::draw(float dt, glm::vec3 lightPosition, glm::vec3 lightColor, float radiantPower, float ambientReflectionCoefficient, float diffuseReflectionCoefficient, float specularReflectionCoefficient, float shininessCoefficient)
{
	DrawTexture(lightPosition, lightColor, radiantPower, ambientReflectionCoefficient, diffuseReflectionCoefficient, specularReflectionCoefficient, shininessCoefficient);
}
