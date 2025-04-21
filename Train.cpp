#include <chrono>

#include "Train.h"
#include "shaderprogram.h"

Train::Train()
{
	basePosition = glm::vec3(0.0f, 0.0f, 0.0f);

	this->kolo1 = new BasicModel("01_os_1.obj");
	this->kolo2 = new BasicModel("01_os_2.obj");
	this->kolo3 = new BasicModel("01_os_2.obj");
	this->kolo4 = new BasicModel("01_os_4.obj");
	this->kolo5 = new BasicModel("01_os_2.obj");
	this->kolo6 = new BasicModel("01_os_6.obj");

	this->ostoja = new BasicModel("02_Ostojnica.obj");
}

void Train::Move(float step)
{
}

void Train::Draw()
{
	calculateSpeed();
	calculatePosition();

	
	float angle_x = 0;
	float angle_y = 0;
	
	glUniform4f(spLambert->u("color"), 0, 1, 1, 1); //Ustaw kolor rysowania obiektu

	// Model - kola
	kolo1->Clear();
	kolo1->Translate(975.0f, 500.0f, 0.0f);
	kolo1->Translate(basePosition); // ostateczne przesuniecie gotowego obiektu
	kolo1->RotateZ(kolo1Angle);
	kolo1->drawSolid();

	kolo2->Clear();
	kolo2->Translate(3775.0f, 975.0f, 0.0f);
	kolo2->Translate(basePosition); // ostateczne przesuniecie gotowego obiektu
	kolo2->RotateZ(kolo2Angle);
	kolo2->drawSolid();

	kolo3->Clear();
	kolo3->Translate(5775.0f, 975.0f, 0.0f);
	kolo3->Translate(basePosition); // ostateczne przesuniecie gotowego obiektu
	kolo3->RotateZ(kolo2Angle);
	kolo3->drawSolid();

	kolo4->Clear();
	kolo4->Translate(7775.0f, 975.0f, 0.0f);
	kolo4->Translate(basePosition); // ostateczne przesuniecie gotowego obiektu
	kolo4->RotateZ(kolo2Angle);
	kolo4->drawSolid();

	kolo5->Clear();
	kolo5->Translate(9775.0f, 975.0f, 0.0f);
	kolo5->Translate(basePosition); // ostateczne przesuniecie gotowego obiektu
	kolo5->RotateZ(kolo2Angle);
	kolo5->drawSolid();

	kolo6->Clear();
	kolo6->Translate(13195.0f, 600.0f, 0.0f);
	kolo6->Translate(basePosition); // ostateczne przesuniecie gotowego obiektu
	kolo6->RotateZ(kolo6Angle);
	kolo6->drawSolid();

	// ostoja
	glUniform4f(spLambert->u("color"), 0, 0, 0, 1); //Ustaw kolor rysowania obiektu

	ostoja->Clear();
	ostoja->Translate(40.0f, 1050.0f, -460.0f);
	ostoja->Translate(basePosition); 
	ostoja->drawSolid();

	ostoja->Clear();
	ostoja->Translate(40.0f, 1050.0f, 460.0f);
	ostoja->Translate(basePosition); 
	ostoja->drawSolid();

}

void Train::SetBase(glm::vec3 vec)
{
	basePosition = vec;
}

void Train::SetBase(float x, float y, float z)
{
	basePosition = glm::vec3(x, y, z);
}

void Train::RotateX(float angle)
{
}

void Train::RotateY(float angle)
{
}

void Train::RotateZ(float angle)
{
}

void Train::setAcceleration(float acc)
{
	acceleration = acc;
}

float Train::getAcceleration()
{
	return acceleration;
}

float Train::getSpeed()
{
	return speed;
}

void Train::calculateSpeed()
{
	float now = glfwGetTime();
	float deltaTime = now - lastTime;

	speed += acceleration * deltaTime;
	speed = std::min(speed, maxSpeed);

	basePosition.x -= 100*(speed * deltaTime);
	
	float wheelCircumference = glm::two_pi<float>() * 500.0f; // promieñ 0.4 m
	kolo1Angle += (speed * deltaTime * 100) / (500.0f);
	kolo2Angle += (speed * deltaTime * 100) / (1925.0f);
	kolo6Angle += (speed * deltaTime * 100) / (600.0f);

	printf("pos: %f  kol: %f   ", basePosition.x, kolo1Angle);

	//printf("dt: %f\n", deltaTime);
	lastTime = now;
}

void Train::calculatePosition()
{

}
