#include "objects/TextureObject.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

TexturePlane::TexturePlane(glm::vec3 position, float angle, glm::vec3 rotation, glm::vec3 scale) : Object(position, angle, rotation, scale)
{
	float vertices[]{
		//positions		   //texture coordinates
		 0.5f,  0.5f, 0.f, 1.f, 1.f, //top right
		-0.5f,  0.5f, 0.f, 0.f, 1.f, //top left 
		-0.5f, -0.5f, 0.f, 0.f, 0.f, //bottom left
		 0.5f, -0.5f, 0.f, 1.f, 0.f  //bottom right
	};


	unsigned int indices[]{

		0, 1, 3, //top triangle
		1, 2, 3  //bottom triangle	
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO[0]);
	glGenBuffers(1, &VBO[1]);

	glBindVertexArray(VAO);

	//Element Buffer Object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	//Load image image un CPU
	int imageWidth, imageHeight, numberChannels;
	unsigned char* data = stbi_load("resources/container.jpg", &imageWidth, &imageHeight, &numberChannels, 0);

	if (data)
	{
		//Generate texture
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		//Handle error
		std::cerr << "Error loading the texture" << std::endl;
	}

	stbi_image_free(data);

	program = new Program("Square");
	program->compileAndAttachShader("shaders/texture.vert", GL_VERTEX_SHADER);
	program->compileAndAttachShader("shaders/texture.frag", GL_FRAGMENT_SHADER);

	program->bindAttribLocation(0, "in_Position");
	program->bindAttribLocation(1, "in_UV");

	program->link();

	glBindVertexArray(0);

	program->unuse();
}

TexturePlane::~TexturePlane()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO[0]);
	glDeleteBuffers(1, &VBO[1]);
	glDeleteTextures(1, &texture);
	delete program;
}

void TexturePlane::DrawTexture()
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(VAO);
	program->use();

	glUniformMatrix4fv(
		program->getUniform("objMat"),
		1, GL_FALSE, glm::value_ptr(_objectMatrix)
	);
	glUniformMatrix4fv(
		program->getUniform("mvpMat"),
		1, GL_FALSE, glm::value_ptr(_cam._MVP)
	);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	program->unuse();
	glBindVertexArray(0);
}

void TexturePlane::draw(float dt, glm::vec3 lightPosition, glm::vec3 lightColor, float radiantPower, float ambientReflectionCoefficient, float diffuseReflectionCoefficient, float specularReflectionCoefficient, float shininessCoefficient)
{
	DrawTexture();
}
