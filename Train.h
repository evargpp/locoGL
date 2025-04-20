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


private:
	glm::vec3 basePosition;
	glm::vec3 currentPosition;
	BasicModel* kolo1;
	BasicModel* kolo2;
	BasicModel* kolo3;
	BasicModel* kolo4;
	BasicModel* kolo5;
	BasicModel* kolo6;
};

