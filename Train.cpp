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

	this->cylinderLewy = new BasicModel("03_Cylinder_parowy_prawy.obj");
	this->cylinderPrawy = new BasicModel("03_Cylinder_parowy_lewy.obj");
	this->krzyzulec = new BasicModel("03_Krzyzulec.obj");

	this->wiazar12 = new BasicModel("03_Wiazar_1_2.obj");
	this->wiazar23 = new BasicModel("03_Wiazar_2_3.obj");
	this->wiazar34 = new BasicModel("03_Wiazar_3_4.obj");

	this->korbowod = new BasicModel("03_Korbowod.obj");
	this->tlok = new BasicModel("02_Tlok.obj");

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
	
	glUniform4f(shader->u("color"), 0, 1, 1, 1); //Ustaw kolor rysowania obiektu


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
	//glUniform4f(shader->u("color"), 0, 0, 0, 1); //Ustaw kolor rysowania obiektu
	//glUniform4f(shader->u("color"), 0, 1, 1, 1); //Ustaw kolor rysowania obiektu

	ostoja->Clear();
	ostoja->Translate(40.0f, 1050.0f, -460.0f);
	ostoja->Translate(basePosition); 
	ostoja->drawSolid();

	ostoja->Clear();
	ostoja->Translate(40.0f, 1050.0f, 460.0f);
	ostoja->Translate(basePosition); 
	ostoja->drawSolid();

	//glUniform4f(shader->u("color"), 0, 1, 1, 1); //Ustaw kolor rysowania obiektu

	// cylindel lewy
	cylinderLewy->Clear();
	cylinderLewy->Translate(40.0f+1575.0f, 1050.0f+320.0f, 460.0f+45.0f);
	cylinderLewy->Translate(basePosition);
	cylinderLewy->drawSolid();

	// cylindel prawy
	cylinderPrawy->Clear();
	cylinderPrawy->Translate(40.0f+1575.0f, 1050.0f+320.0, -460.0f-45.0f);
	cylinderPrawy->Translate(basePosition);
	cylinderPrawy->drawSolid();

	// wiazary
	glm::mat4 rotationL = glm::rotate(glm::mat4(1.0f), -kolo2Angle, vec3(0.0f, 0.0f, 1.0f));
	glm::vec4 rotatedL = rotationL * glm::vec4(0.0f, -350.0f, 0.0f, 1.0f);
	
	glm::mat4 rotationP = glm::rotate(glm::mat4(1.0f), -kolo2Angle, vec3(0.0f, 0.0f, 1.0f));
	glm::vec4 rotatedP = rotationP * glm::vec4(-350.0f, 0.0f, 0.0f, 1.0f);

    wiazar12->Clear();
	wiazar12->Translate(3824.0f-rotatedL.x, 975.0f+rotatedL.y, -912.0f-rotatedL.z);
	wiazar12->Translate(basePosition);
	wiazar12->drawSolid();

	wiazar12->Clear();
	wiazar12->Translate(3824.0f - rotatedP.x, 975.0f + rotatedP.y, 912.0f - rotatedP.z);
	wiazar12->Translate(basePosition);
	wiazar12->drawSolid();

	wiazar23->Clear();
	wiazar23->Translate(7824.0f - rotatedL.x, 975.0f + rotatedL.y, -912.0f - rotatedL.z);
	wiazar23->Translate(basePosition);
	wiazar23->drawSolid();

	wiazar23->Clear();
	wiazar23->Translate(7824.0f - rotatedP.x, 975.0f + rotatedP.y, 912.0f - rotatedP.z);
	wiazar23->Translate(basePosition);
	wiazar23->drawSolid();

	wiazar34->Clear();
	wiazar34->Translate(9824.0f - rotatedL.x, 975.0f + rotatedL.y, -912.0f - rotatedL.z);
	wiazar34->Translate(basePosition);
	wiazar34->drawSolid();

	wiazar34->Clear();
	wiazar34->Translate(9824.0f - rotatedP.x, 975.0f + rotatedP.y, 912.0f - rotatedP.z);
	wiazar34->Translate(basePosition);
	wiazar34->drawSolid();

	// korobwod
	float d = 3848.0f;
	float x2L = 7824.0f - rotatedL.x;
	float y2L = 975.0f + rotatedL.y;
	float y1L = 905.0f;
	
	float x1L = -1.0 * (sqrt( d*d - (y2L-y1L)* (y2L - y1L)) - x2L);
	float aL = atan((y2L - y1L) / (x2L - x1L));

	float x2P = 7824.0f - rotatedP.x;
	float y2P = 975.0f + rotatedP.y;
	float y1P = 905.0f;

	float x1P = -1.0 * (sqrt(d * d - (y2P - y1P) * (y2P - y1P)) - x2P);
	float aP = atan((y2P - y1P) / (x2P - x1P));


//	printf("a = %f\n", glm::degrees(a));

	korbowod->Clear();
	korbowod->Translate(7824.0f - rotatedL.x, 975.0f + rotatedL.y, -1102.0f - rotatedL.z);
	korbowod->Translate(basePosition);
	korbowod->RotateZ(aL);
	korbowod->drawSolid();

	korbowod->Clear();
	korbowod->Translate(7824.0f - rotatedP.x, 975.0f + rotatedP.y, 1102.0f - rotatedP.z);
	korbowod->Translate(basePosition);
	korbowod->RotateZ(aP);
	korbowod->drawSolid();

	// krzyzulec
	krzyzulec->Clear();
	krzyzulec->Translate(x1L, y1L, -1102.0f);
	krzyzulec->Translate(basePosition);
	krzyzulec->drawSolid();

	krzyzulec->Clear();
	krzyzulec->Translate(x1P, y1P, 1102.0f);
	krzyzulec->Translate(basePosition);
	krzyzulec->drawSolid();

	// tlok
	tlok->Clear();
	tlok->Translate(x1L-200.0f, y1L, -1102.0f);
	tlok->Translate(basePosition);
	tlok->drawSolid();

	tlok->Clear();
	tlok->Translate(x1P - 200.0f, y1P, 1102.0f);
	tlok->Translate(basePosition);
	tlok->drawSolid();

	//printf("x %f %f\n", x1, y1);

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

	//basePosition.x -= 100*(speed * deltaTime);
	
	float wheelCircumference = glm::two_pi<float>() * 500.0f; // promie� 0.4 m
	kolo1Angle += (speed * deltaTime * 100) / (500.0f);
	kolo2Angle += (speed * deltaTime * 100) / (1925.0f);
	kolo6Angle += (speed * deltaTime * 100) / (600.0f);

	// obiczenie wiazar�w


	//printf("pos: %f  kol: %f   ", basePosition.x, kolo1Angle);

	//printf("dt: %f\n", deltaTime);
	lastTime = now;
}

void Train::calculatePosition()
{

}
