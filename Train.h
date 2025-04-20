#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Train
{
public:
	Train();
	void Move(float step);

private:
	glm::mat4 BaseLocation;
	glm::mat4 CurrentLocation;

};

