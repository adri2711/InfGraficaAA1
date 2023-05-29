#pragma once
#include "objects/Model.h"

class Car : public Object
{
private:

    std::vector<Model> _cars;

    glm::mat4 _objectMatrixArray[10];
    
    float carSpeed = 500.f;
    float carTrajectoryRadius = 20.f;

    void SetupUniformsModel();
    
public:

    Car(int carsNum);
    ~Car();

    void Race(bool changeView, float* panv, float& rota, float dt);

    void draw(float dt) override;
    
};
