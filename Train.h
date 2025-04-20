#pragma once

#include "OpenGLCommon.h"
#include "BasicModel.h"

class Train
{
public:
	Train();
	void Move(float step);
	void Draw();
	void SetBase(glm::vec3 vec);
	void SetBase(float x, float y, float z);
	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);

	void setAcceleration(float acc);
	float getAcceleration();
	float getSpeed();

private:
	glm::vec3 basePosition;
	glm::vec3 currentPosition;
	BasicModel* kolo1;
	BasicModel* kolo2;
	BasicModel* kolo3;
	BasicModel* kolo4;
	BasicModel* kolo5;
	BasicModel* kolo6;
	BasicModel* ostoja;

	float kolo1Angle = 0.0f;
	float kolo2Angle = 0.0f;
	float kolo6Angle = 0.0f;

	float acceleration;
	float speed;
	float maxSpeed = 10.0f;
	float lastTime = glfwGetTime();

	void calculateSpeed();
	void calculatePosition();
};

