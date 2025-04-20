#pragma once

#include "OpenGLCommon.h"


class Train
{
public:
	Train();
	void Move(float step);

private:
	glm::mat4 BaseLocation;
	glm::mat4 CurrentLocation;

};

