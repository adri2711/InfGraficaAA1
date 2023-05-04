#include <renderers/Texturing.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texturing::Texturing(int width, int height) : Renderer(width, height)
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
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	//Element Buffer Object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
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

Texturing::~Texturing()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteTextures(1, &texture);
	delete program;
}

void Texturing::render(float dt)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(VAO);
	program->use();

	color = glm::vec4(1.f, 0.3f, 0.2f, 1.f);

	objMat = glm::translate(glm::mat4(), glm::vec3(0.f, 0.f, -5.f));

	glUniformMatrix4fv(
		program->getUniform("objMat"),
		1, GL_FALSE, glm::value_ptr(objMat)
	);
	glUniformMatrix4fv(
		program->getUniform("mvpMat"),
		1, GL_FALSE, glm::value_ptr(cam._MVP)
	);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	program->unuse();
	glBindVertexArray(0);
}