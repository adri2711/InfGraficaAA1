#pragma once

#include <vector>
#include <glm/gtc/matrix_transform.hpp>

#include "Program.h"
#include "renderers/Renderer.h"

class Object
{
protected:
    glm::vec3 _position;
    glm::vec3 _rotation;
    glm::vec3 _scale;

    glm::mat4 _translationMatrix;
    glm::mat4 _rotationMatrix;
    glm::mat4 _scaleMatrix;

    glm::mat4 _objectMatrix;

    CameraTransforms _cam;
    glm::vec4 color;
    
    GLuint VAO;
    GLuint VBO[3];
    Program* program;

    std::vector< glm::vec3 > vertices;
    std::vector< glm::vec2 > uvs;
    std::vector< glm::vec3 > normals; // Won't be used at the moment.
    
public:

    Object(glm::vec3 position, float angle, glm::vec3 rotation, glm::vec3 scale);
    Object(glm::vec3 position, glm::vec3 scale);
    Object(glm::vec3 position);
    Object();
    ~Object();

    void Move(glm::vec3 position);
    void Rotate(float angle, glm::vec3 rotation);
    void Scale(glm::vec3 scale);
    void SetObjectMatrix(glm::mat4 matrix);

    glm::mat4 GetTranslationMatrix();
    glm::mat4 GetRotationMatrix();
    glm::mat4 GetScaleMatrix();
    glm::mat4 GetObjectMatrix();

    void setCam(CameraTransforms cam);
    void setColor(glm::vec4 color);
    virtual void draw(glm::vec3 lightPosition, glm::vec4 lightColor, float radiantPower, float ambientReflectionCoefficient, float diffuseReflectionCoefficient, float specularReflectionCoefficient, float shininessCoefficient) = 0;
};
