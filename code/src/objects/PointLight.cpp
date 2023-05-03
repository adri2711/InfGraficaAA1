#include <objects/PointLight.h>

PointLight::PointLight(float radiantPower, glm::vec3 position) : Object(position), _radiantPower(radiantPower)
{
    
}

PointLight::~PointLight()
{
    
}


void PointLight::SetRadiantPower(float radiantPower)
{
    _radiantPower = radiantPower;
}

float PointLight::GetRadiantPower()
{
    return _radiantPower;
}



void PointLight::draw(float dt, glm::vec3 lightPosition, glm::vec3 lightColor, float radiantPower, float ambientReflectionCoefficient, float diffuseReflectionCoefficient, float specularReflectionCoefficient, float shininessCoefficient)
{
    glBindVertexArray(VAO);
    program->use();
    
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

    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    program->unuse();
    glBindVertexArray(0);
}