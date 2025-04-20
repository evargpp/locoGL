#include "Train.h"

Train::Train()
{
	basePosition = glm::vec3(0.0f, 0.0f, 0.0f);

	this->kolo1 = new BasicModel("01_os_2.obj");
	this->kolo2 = new BasicModel("01_os_2.obj");
	this->kolo3 = new BasicModel("01_os_2.obj");
	this->kolo4 = new BasicModel("01_os_2.obj");
	this->kolo5 = new BasicModel("01_os_2.obj");
	this->kolo6 = new BasicModel("01_os_2.obj");
}

void Train::Move(float step)
{
}

void Train::Draw()
{
	float angle_x = 0;
	float angle_y = 0;
	
	// Model - kola
	kolo1->Clear();
	kolo1->RotateX(angle_x);
	kolo1->RotateY(angle_y);
	kolo1->Translate(975.0f, 500.0f, 0.0f);
	kolo1->Translate(basePosition); // ostateczne przesuniecie gotowego obiektu
	kolo1->drawSolid();

	kolo2->Clear();
	kolo2->RotateX(angle_x);
	kolo2->RotateY(angle_y);
	kolo2->Translate(3775.0f, 975.0f, 0.0f);
	kolo2->Translate(basePosition); // ostateczne przesuniecie gotowego obiektu
	kolo2->drawSolid();

	kolo3->Clear();
	kolo3->RotateX(angle_x);
	kolo3->RotateY(angle_y);
	kolo3->Translate(5775.0f, 975.0f, 0.0f);
	kolo3->Translate(basePosition); // ostateczne przesuniecie gotowego obiektu
	kolo3->drawSolid();

	kolo4->Clear();
	kolo4->RotateX(angle_x);
	kolo4->RotateY(angle_y);
	kolo4->Translate(7775.0f, 975.0f, 0.0f);
	kolo4->Translate(basePosition); // ostateczne przesuniecie gotowego obiektu
	kolo4->drawSolid();

	kolo5->Clear();
	kolo5->RotateX(angle_x);
	kolo5->RotateY(angle_y);
	kolo5->Translate(9775.0f, 975.0f, 0.0f);
	kolo5->Translate(basePosition); // ostateczne przesuniecie gotowego obiektu
	kolo5->drawSolid();

	kolo6->Clear();
	kolo6->RotateX(angle_x);
	kolo6->RotateY(angle_y);
	kolo6->Translate(13195.0f, 600.0f, 0.0f);
	kolo6->Translate(basePosition); // ostateczne przesuniecie gotowego obiektu
	kolo6->drawSolid();

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
