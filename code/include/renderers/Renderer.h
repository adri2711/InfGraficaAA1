#pragma once
#include <GL\glew.h>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <cstdio>
#include <cassert>

#include <imgui\imgui.h>
#include <imgui\imgui_impl_sdl_gl3.h>

#include "GL_framework.h"

#define MIN_X_POSITION_LIGHT -5
#define MAX_X_POSITION_LIGHT 5

#define MIN_Y_POSITION_LIGHT -5
#define MAX_Y_POSITION_LIGHT 5

#define MIN_Z_POSITION_LIGHT -5 
#define MAX_Z_POSITION_LIGHT 5

#define MIN_RADIANT_POWER 0
#define MAX_RADIANT_POWER 50

#define MIN_RED_COLOR 0
#define MAX_RED_COLOR 1

#define MIN_GREEN_COLOR 0
#define MAX_GREEN_COLOR 1

#define MIN_BLUE_COLOR 0
#define MAX_BLUE_COLOR 1

#define MIN_ALPHA_COLOR 0
#define MAX_ALPHA_COLOR 1

#define MIN_AMBIENT_COEFFICIENT 0
#define MAX_AMBIENT_COEFFICIENT 1

#define MIN_DIFFUSE_COEFFICIENT 0
#define MAX_DIFFUSE_COEFFICIENT 1

#define MIN_SPECULAR_COEFFICIENT 0
#define MAX_SPECULAR_COEFFICIENT 1

struct CameraTransforms {
	glm::mat4 _projection;
	glm::mat4 _modelView;
	glm::mat4 _MVP;
	glm::mat4 _cameraRotationMat;
	glm::mat4 _inv_modelview;
	glm::vec4 _cameraPoint;
};

class Renderer
{
public:
	Renderer(int width, int height);
	~Renderer();
	void GUI();
	void GLmousecb(MouseEvent ev);
	void GLResize(int width, int height);
	void GLrender(float dt);
protected:
	float FOV = glm::radians(65.f);
	float zNear = 1.f;
	float zFar = 50.f;

	glm::vec3 _lightPosition;
	glm::vec4 _lightColor;
	float _radiantPower;

	float _ambientReflectionCoefficient;
	float _diffuseReflectionCoefficient;
	float _specularReflectionCoefficient;
	float _shininessCoefficient;

	CameraTransforms _cam;

	struct prevMouse {
		float lastx, lasty;
		MouseEvent::Button button = MouseEvent::Button::None;
		bool waspressed = false;
	} prevMouse;

	float panv[3] = { 0.f, 0.f, 0.f };
	float rota[2] = { 0.f, 0.f };

	const GLfloat bgColor[4] = { 0.2f,0.2f,0.2f,1.0f };

	virtual void render(float dt);
	virtual void renderGUI();
};

