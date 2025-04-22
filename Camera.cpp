#include "OpenGLCommon.h"

#include "Camera.h"


Camera::Camera() {
	//position = glm::vec3(0.0f, 972.0f, 30000.0f);
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	lookPoint = glm::vec3(0.0f, 0.0f, 0.0f);
	upDirection = glm::vec3(0.0f, 1.0f, 0.0f);
	fov = 0.0f;
	aspect = 0.0f;
	nearPlane = 0.0f;
	farPlane = 0.0f;
	M = glm::mat4(1.0f);
	
	hAngle = glm::radians(-120.0f);
	vAngle = glm::radians(60.0f);
	zoom = 16000;
}

void Camera::RotateX(float angle) {
	M = glm::rotate(M, angle, glm::vec3(1.0f, 0.0f, 0.0f));
};


void Camera::RotateY(float angle) {
	M = glm::rotate(M, angle, glm::vec3(0.0f, 1.0f, 0.0f));
};


void Camera::RotateZ(float angle) {
	M = glm::rotate(M, angle, glm::vec3(0.0f, 0.0f, 1.0f));
}


void Camera::setHAngle(float angle)
{
	hAngle = angle;
}


void Camera::setVAngle(float angle)
{
	vAngle = angle;
}


void Camera::deltaHAngle(float angle)
{
	hAngle += angle;
}


void Camera::deltaVAngle(float angle)
{
	vAngle += angle;
	if (vAngle > glm::half_pi<float>())
		vAngle = glm::half_pi<float>();
	if (vAngle <= 0)
		vAngle = glm::radians(1.0f);

}

void Camera::deltaZoom(float delta)
{
	zoom += delta;
}

void Camera::ShowParams()
{
	printf("hAngle: %f, vAngle: %f, zoom: %f, X: %f Y: %f, Z: %f\n", glm::degrees(hAngle), glm::degrees(vAngle), zoom, position.x, position.y, position.z);
}



glm::mat4 Camera::GetViewMatrix() {

	position.x = zoom * sin(vAngle) * cos(hAngle);
	position.y = zoom * cos(vAngle);
	position.z = zoom * sin(vAngle) * sin(hAngle);
	

	return glm::lookAt(
		position, 
		lookPoint,
		upDirection
	);
};


glm::mat4 Camera::GetProjectionMatrix() {
    return glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50000.0f);
}

glm::vec3 Camera::GetPosition()
{
	return position;
}
;
