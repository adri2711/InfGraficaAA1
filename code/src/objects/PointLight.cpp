#include <objects/PointLight.h>

PointLight::PointLight(const char* shaderPath, glm::vec3 color, float radiantPower, glm::vec3 position, float angle, glm::vec3 rotation, glm::vec3 scale):
    Object(position, angle, rotation, scale), _radiantPower(radiantPower)
{
    Illuminate(shaderPath);
}

PointLight::PointLight(const char* shaderPath, glm::vec3 color, float radiantPower, glm::vec3 position, glm::vec3 scale):
    Object(position, scale), _radiantPower(radiantPower)
{
    Illuminate(shaderPath);
}

PointLight::PointLight(const char* shaderPath, glm::vec3 color, float radiantPower, glm::vec3 position) : Object(position), _radiantPower(radiantPower)
{
    Illuminate(shaderPath);
}

void PointLight::Illuminate(const char* shaderPath)
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3), &_position, GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)0, 1, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    std::string vertexPath = std::string(shaderPath).append(".vert");
    std::string fragmentPath = std::string(shaderPath).append(".frag");
    
    // Initialize program
    program = new Program("PointLight");
    program->compileAndAttachShader(vertexPath.c_str(), GL_VERTEX_SHADER, "vertex");
    program->compileAndAttachShader(fragmentPath.c_str(), GL_FRAGMENT_SHADER, "fragment");

    // Bind Attrib locations
    program->bindAttribLocation(0, "in_position");

    // Link program
    program->link();
    
}

PointLight::~PointLight()
{
    
}


void PointLight::draw()
{
    glBindVertexArray(VAO);
    program->use();
    
    glUniform1f(program->getUniform("radiantPower"), _radiantPower);
    
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
    glUniform4f(
        program->getUniform("color"),
        color.r, color.g, color.b, color.w
    );

    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    program->unuse();
    glBindVertexArray(0);
}


void PointLight::SetRadiantPower(float radiantPower)
{
    _radiantPower = radiantPower;
}

float PointLight::GetRadiantPower()
{
    return _radiantPower;
}