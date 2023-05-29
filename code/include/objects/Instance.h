#pragma once
#include "objects/Model.h"

class Instance : public Object
{
private:

    char* modelPath;
    char* shaderPath;

    std::vector<Model> _cars;

    glm::mat4 _objectMatrixArray[10];
    
    float carSpeed = 500.f;
    float carTrajectoryRadius = 20.f;

    void SetupUniformsModel();
    
public:

    Instance(char* modelPath, char* shaderPath, int carsNum);
    ~Instance();

    void loadOBJ(const char* path, std::vector < glm::vec3 >& out_vertices, std::vector < glm::vec2 >& out_uvs, std::vector < glm::vec3 >& out_normals);

    void SetupProgram(std::string shaderPath);
    void SetupProgramNormal(std::string shaderPath);
    void SetupBuffers();

    void Race(bool changeView, float* panv, float* rota, CameraTransforms cam, float dt);

    void draw(float dt) override;
    
};
