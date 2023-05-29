#include <objects/Object.h>

Object::Object(glm::vec3 position, float angle, glm::vec3 rotation, glm::vec3 scale)
{
    Move(position);
    Rotate(angle, rotation);
    Scale(scale);
    
    _objectMatrix = _translationMatrix * _rotationMatrix * _scaleMatrix;
}

Object::Object(glm::vec3 position, glm::vec3 scale)
{
    Move(position);
    Scale(scale);

    _objectMatrix = _translationMatrix * _scaleMatrix;
    
}

Object::Object(glm::vec3 position)
{
    Move(position);

    _objectMatrix = _translationMatrix;
}

Object::Object()
{
    glDeleteBuffers(3, VBO);
    glDeleteVertexArrays(1, &VAO);
}

Object::~Object()
{
    
}

void Object::Move(glm::vec3 position)
{
    _translationMatrix = glm::translate(glm::mat4(), position);
}

void Object::Rotate(float angle, glm::vec3 rotation)
{
    _rotationMatrix = glm::rotate(glm::mat4(), -glm::radians(float(angle)), rotation);
}

void Object::Scale(glm::vec3 scale)
{
    _scaleMatrix = glm::scale(glm::mat4(), scale);
}

void Object::SetObjectMatrix(glm::mat4 matrix)
{
    _objectMatrix = matrix;
}

glm::mat4 Object::GetTranslationMatrix()
{
    return _translationMatrix;
}

glm::mat4 Object::GetRotationMatrix()
{
    return _rotationMatrix;
}

glm::mat4 Object::GetScaleMatrix()
{
    return _scaleMatrix;
}

glm::mat4 Object::GetObjectMatrix()
{
    return _objectMatrix;
}

void Object::setCam(CameraTransforms cam)
{    
    this->_cam = cam;
}

void Object::setColor(glm::vec4 color)
{
    this->color = color;
}