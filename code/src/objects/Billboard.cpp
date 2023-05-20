#include "objects/Billboard.h"
//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Billboard::Billboard(float size, char* texturePath, char* shaderPath, glm::vec3 position, float angle, glm::vec3 rotation, glm::vec3 scale)
	: Object(position, angle, rotation, scale)
{
	this->size = size;
	this->texturePath = texturePath;
	this->shaderPath = shaderPath;
}

Billboard::~Billboard()
{
}

void Billboard::draw(float dt)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(VAO);

	DrawBillboard();

	glBindVertexArray(0);
}

void Billboard::DrawBillboard()
{
	program->use();
	SetupUniforms();
	glPointSize(40.f);
	glDrawArrays(GL_POINTS, 0, vertices.size());
	program->unuse();
}

void Billboard::SetupUniforms()
{
	glUniform1f(program->getUniform("quadSize"), size);

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
	glUniformMatrix4fv(
		program->getUniform("pMatrix"),
		1, GL_FALSE, glm::value_ptr(_cam._projection)
	);
	glUniform3f(
		program->getUniform("color"),
		color.r, color.g, color.b
	);
}

void Billboard::Init()
{
	SetupData();
	SetupProgram(shaderPath);
	program->link();
	SetupBuffers();
	LoadTexture();
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Billboard::SetupData()
{
	vertices.push_back(glm::vec3(0, 0, 0));
	normals.push_back(glm::vec3(0, 0, 1));
	uvs.push_back(glm::vec2(1, 1));
	uvs.push_back(glm::vec2(0, 1));
	uvs.push_back(glm::vec2(1, 0));
	uvs.push_back(glm::vec2(0, 0));
}



void Billboard::SetupProgram(std::string shaderPath)
{
	std::string vertexPath = std::string(shaderPath).append(".vert");
	std::string fragmentPath = std::string(shaderPath).append(".frag");
	std::string geometryPath = std::string(shaderPath).append(".geom");

	// Initialize program
	program = new Program("Billboard");
	program->compileAndAttachShader(vertexPath.c_str(), GL_VERTEX_SHADER, "vertex");
	program->compileAndAttachShader(fragmentPath.c_str(), GL_FRAGMENT_SHADER, "fragment");
	program->compileAndAttachShader(geometryPath.c_str(), GL_GEOMETRY_SHADER, "geometry");

	// Bind Attrib locations
	program->bindAttribLocation(0, "in_Position");
	program->bindAttribLocation(1, "in_Normals");
	program->bindAttribLocation(2, "in_UV");
}

void Billboard::SetupBuffers()
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

	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * uvs.size(), &uvs[0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, );

	int imageWidth, imageHeight, numberChannels;
	unsigned char* data = stbi_load( "", &imageHeight, &imageHeight, &numberChannels, 0);*/
}

void Billboard::LoadTexture()
{
	//Load image image un CPU
	int imageWidth, imageHeight, numberChannels;
	std::cout << texturePath << std::endl;
	unsigned char* data = stbi_load(texturePath, &imageWidth, &imageHeight, &numberChannels, 0);

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
}
