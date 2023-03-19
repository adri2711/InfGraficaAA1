#include <objects/Object.h>

Object::Object(glm::vec3 position, float angle, glm::vec3 rotation, glm::vec3 scale)
{
    Move(position);
    Rotate(angle, rotation);
    Scale(scale);
    
    _objectMatrix = _view * _model * _projection;
}

Object::Object(glm::vec3 position, glm::vec3 scale)
{
    Move(position);
    Scale(scale);

    _objectMatrix = _view * _projection;
    
}

Object::Object(glm::vec3 position)
{
    Move(position);

    _objectMatrix = _view;
}

Object::Object()
{
    
}

Object::~Object()
{
    
}

void Object::Move(glm::vec3 position)
{
    _view = glm::translate(glm::mat4(), position);
}

void Object::Rotate(float angle, glm::vec3 rotation)
{
    _model = glm::rotate(glm::mat4(), -glm::radians(float(angle)), rotation);
}

void Object::Scale(glm::vec3 scale)
{
    _projection = glm::scale(glm::mat4(), scale);
}

void Object::SetObjectMatrix(glm::mat4 matrix)
{
    _objectMatrix = matrix;
}

glm::mat4 Object::GetView()
{
    return _view;
}

glm::mat4 Object::GetModel()
{
    return _model;
}

glm::mat4 Object::GetProjection()
{
    return _projection;
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