#include "objects/Car.h"

Car::Car(int carsNum)
{    
    for (int i = 0; i < carsNum; ++i)
    {
        _cars.push_back(Model("resources/cotxe.obj", "shaders/Model", glm::vec3(0.0f, -0.3f, -3.0f), 0.f, glm::vec3(0.f, 1.f, 0.f), glm::vec3(.3f, .3f, .3f)));
        _cars.back().InitModel();
        _cars[i].elapsedTime = 100 - (100 / carsNum) * i;
        _objectMatrixArray[i] = _cars[i].GetObjectMatrix();
    }
}

Car::~Car()
{
}


void Car::Race(bool changeView, float* panv, float& rota, float dt)
{

    for (int i = 0; i < _cars.size(); i++) {
        float speed = carSpeed / carTrajectoryRadius;
        float t = _cars[i].elapsedTime * speed;
        float a = glm::radians(t);
        glm::vec3 position = glm::vec3(cos(a) * carTrajectoryRadius, -0.8f, sin(a) * carTrajectoryRadius);
        int rotation = ((int)t * 1000 % 360000) / 1000.f;
        _cars[i].Move(position);
        _cars[i].Rotate(rotation, glm::vec3(0.f, 1.f, 0.f));
		
        if (i == 0)
        {
            if (changeView)
            {
                panv[0] = position[0];
                panv[1] = position[1];
                panv[2] = position[2];
			
                rota = rotation;
            }
        }
		
        _cars[i].SetObjectMatrix(_cars[i].GetTranslationMatrix() * _cars[i].GetRotationMatrix());
        _cars[i].setCam(_cam);
        _cars[i].draw(dt);
    }
}

void Car::draw(float dt)
{
    
    for (Model car : _cars)
    {    
        car.elapsedTime += dt;

        glBindVertexArray(VAO);

        program->use();
        SetupUniformsModel();
        glMultiDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_SHORT, &_cars[0], _cars.size() + 1, 0);
        program->unuse();

        glBindVertexArray(0);
    }
}

void Car::SetupUniformsModel()
{
    glUniformMatrix4fv(
        program->getUniform("objectMatrixArray"),
        _cars.size(), GL_FALSE, glm::value_ptr(_objectMatrixArray[0])
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
}
