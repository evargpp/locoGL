#include "Infrastructure.h"
#include "shaderprogram.h"

Infrastructure::Infrastructure()
{
	this->M = glm::mat4(1.0f);
	this->szyna = new BasicModel("00_szyna.obj");
	this->podklad = new BasicModel("00_podklad.obj");
	this->podtorze = new BasicModel("00_podtorze.obj");
}

Infrastructure::~Infrastructure()
{
}

void Infrastructure::Draw()
{
	float angle_x = 0.0f;
	float angle_y = 0.0f;
	
	// Model - podtorze
	podtorze->Clear();
	podtorze->RotateX(angle_x);
	podtorze->RotateY(angle_y);
	podtorze->drawSolid(); //Narysuj obiekt

	// Model - podklady
	podklad->Clear();
	podklad->RotateX(angle_x);
	podklad->RotateY(angle_y);
	podklad->Translate(22775.0f, 650.0f, 0.0f);

	for (int i = 0; i < 60; i++) {
		podklad->Translate(-600.0f, 0.0f, 0.0f);
		podklad->drawSolid(); //Narysuj obiekt
	}

	glUniform4f(shader->u("color"), 0, 1, 1, 1); //Ustaw kolor rysowania obiektu

	// Model - szyny
	szyna->Clear();
	szyna->RotateX(angle_x);
	szyna->RotateY(angle_y);
	szyna->Translate(0.0f, 800.0f, 717.5f);
	szyna->drawSolid();

	szyna->Translate(0.0f, 0.0f, -1435.0f);
	szyna->drawSolid();

}
