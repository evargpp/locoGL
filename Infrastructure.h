#pragma once

#include "OpenGLCommon.h"

#include "BasicModel.h"

class Infrastructure
{
public:
	Infrastructure();
	~Infrastructure();
	void Draw();


private:
	glm::mat4 M;
	BasicModel* szyna;
	BasicModel* podklad;
	BasicModel* podtorze;
};

