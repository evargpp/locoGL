#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Camera.h"


Camera::Camera() {
	this->position = glm::vec3(0.0f, 1500.0f, 30000.0f);
	this->lookPoint = glm::vec3(0.0f, 0.0f, 0.0f);
	this->upDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	this->fov = 0.0f;
	this->aspect = 0.0f;
	this->nearPlane = 0.0f;
	this->farPlane = 0.0f;
}


glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(
		this->position, 
		this->lookPoint,
		this->upDirection
	);
};


glm::mat4 Camera::GetProjectionMatrix() {
    return glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50000.0f);
};
