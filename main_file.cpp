#include "config.h"

#define GLM_FORCE_RADIANS
#define STB_EASY_FONT_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION 

#include "OpenGLCommon.h"

#include <stdlib.h>
#include <stdio.h>
#include <chrono>

#include "constants.h"
#include "shaderprogram.h"

#include "BasicModel.h"
#include "Camera.h"
#include "Infrastructure.h"
#include "Train.h"

float speed_x = 0;//[radiany/s]
float speed_y = 0;//[radiany/s]

float cam_speed_x = 0.0f;
float cam_speed_y = 0.0f;
float cam_speed_z = 0.0f;

//glm::vec3 cameraPos1 = glm::vec3(0.0f, 5000.0f, 20000.0f);
//glm::vec3 cameraPos2 = glm::vec3(0.0f, 20000.0f, 0.0f);
//glm::vec3 cameraPos3 = glm::vec3(2000.0f, 0.0f, 0.0f);
//glm::vec3 cameraPos4 = glm::vec3(0.0f, 20000.0f, 0.0f);

//glm::vec3 cameraPos1 = glm::vec3(-20000.0f, +20000.0f, -20000.0f);
//glm::vec3 cameraPos2 = glm::vec3(+20000.0f, +20000.0f, -20000.0f);
//glm::vec3 cameraPos3 = glm::vec3(+20000.0f, +20000.0f, +20000.0f);
//glm::vec3 cameraPos4 = glm::vec3(-20000.0f, +20000.0f, +20000.0f);

glm::vec3 cameraPos1 = glm::vec3(0.0f, 1500.0f, 30000.0f);
glm::vec3 cameraPos2 = glm::vec3(500.0f, 30000.0f, 0.0f);
glm::vec3 cameraPos3 = glm::vec3(30000.0f, 2300.0f, 400.0f);
glm::vec3 cameraPos4 = glm::vec3(30000.0f, 3600.0f, 4800.0f);
glm::vec3 cameraPos5 = glm::vec3(-30000.0f, 500.0f, 1000.0f);


glm::vec3 upDirection1 = glm::vec3(0.0f, 1.0f, 0.0f);     // góra to Y+
glm::vec3 upDirection2 = glm::vec3(0.0f, 0.0f, -1.0f);     // góra to Y-

glm::vec3 cameraPos = cameraPos1;
glm::vec3 upDirection = upDirection1;     // góra to Y+

Infrastructure infrastructure;
Train train;
Camera camera;


struct AppParams {
	int screenWidth;
	int screenHeight;
	std::string name;
} appParams = { 1000, 800, "Hello locoGL!" };

//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void key_callback(
	GLFWwindow* window,
	int key,
	int scancode,
	int action,
	int mod
) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_LEFT) {
			speed_y = -PI;
		}
		if (key == GLFW_KEY_RIGHT) {
			speed_y = PI;
		}
		if (key == GLFW_KEY_UP) {
			speed_x = -PI;
		}
		if (key == GLFW_KEY_DOWN) {
			speed_x = PI;
		}
		if (key == GLFW_KEY_Q) {
			cam_speed_x = 1000;
		}
		if (key == GLFW_KEY_A) {
			cam_speed_x = -1000;
		}
		if (key == GLFW_KEY_W) {
			cam_speed_y = 1000;
		}
		if (key == GLFW_KEY_S) {
			cam_speed_y = -1000;
		}
		if (key == GLFW_KEY_E) {
			cam_speed_z = 1000;
		}
		if (key == GLFW_KEY_D) {
			cam_speed_z = -1000;
		}

		if (key == GLFW_KEY_1) {
			// widok z boku
			cameraPos = cameraPos1;
			upDirection = upDirection1;
		}
		if (key == GLFW_KEY_2) {
			// widok z gory
			cameraPos = cameraPos2;
			upDirection = upDirection2;
		}
		if (key == GLFW_KEY_3) {
			// widok z przodu
			cameraPos = cameraPos3;
			upDirection = upDirection1;
		}
		if (key == GLFW_KEY_4) {
			// widok od przodu
			cameraPos = cameraPos4;
			upDirection = upDirection1;
		}
		if (key == GLFW_KEY_5) {
			// widok od tylu 
			cameraPos = cameraPos5;
			upDirection = upDirection1;
		}

		if (key == GLFW_KEY_9) { upDirection = upDirection1; }
		if (key == GLFW_KEY_0) { upDirection = upDirection2; }

	}
	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT) {
			speed_y = 0;
		}
		if (key == GLFW_KEY_UP || key == GLFW_KEY_DOWN) {
			speed_x = 0;
		}
		if (key == GLFW_KEY_Q || key == GLFW_KEY_A) {
			cam_speed_x = 0;
		}
		if (key == GLFW_KEY_W || key == GLFW_KEY_S) {
			cam_speed_y = 0;
		}
		if (key == GLFW_KEY_E || key == GLFW_KEY_D) {
			cam_speed_z = 0;
		}
	}
}


//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
	initShaders();
	//************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
	glClearColor(0, 0, 0, 1); //Ustaw kolor czyszczenia bufora kolorów
	glEnable(GL_DEPTH_TEST); //Włącz test głębokości na pikselach
	glfwSetKeyCallback(window, key_callback);

	train.SetBase(-10000.0f, 972.0f, 0.0f);
}


//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
	freeShaders();
	//************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej************
}

//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window, float angle_x, float angle_y, float cam_x, float cam_y, float cam_z) {
	//************Tutaj umieszczaj kod rysujący obraz******************l
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Wyczyść bufor koloru i bufor głębokości

	//ustawienia kamery
	glm::mat4 P = camera.GetProjectionMatrix();
	glm::mat4 V = camera.GetViewMatrix();

	//ustawienie programu cieniujacego
	spLambert->use(); //Aktyeuj program cieniujący
	glUniform4f(spLambert->u("color"), 0, 1, 0, 1); //Ustaw kolor rysowania obiektu
	glUniformMatrix4fv(spLambert->u("P"), 1, false, glm::value_ptr(P)); //Załaduj do programu cieniującego macierz rzutowania
	glUniformMatrix4fv(spLambert->u("V"), 1, false, glm::value_ptr(V)); //Załaduj do programu cieniującego macierz widoku

	infrastructure.Draw();
	train.Draw();

	//koniec sceny
	glfwSwapBuffers(window); //Skopiuj bufor tylny do bufora przedniego
}


int main(void)
{
	GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno

	glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

	if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(appParams.screenWidth, appParams.screenHeight, appParams.name.c_str(), NULL, NULL);  //Utwórz okno i kontekst OpenGL.

	if (!window) //Jeżeli okna nie udało się utworzyć, to zamknij program
	{
		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekę GLEW
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjujące

	//Główna pętla
	float angle_x = 0; //zadeklaruj zmienną przechowującą aktualny kąt obrotu
	float angle_y = 0; //zadeklaruj zmienną przechowującą aktualny kąt obrotu

	float cam_x = 0.0f; //zadeklaruj zmienną przechowującą aktualny kąt obrotu
	float cam_y = 0.0f; //zadeklaruj zmienną przechowującą aktualny kąt obrotu
	float cam_z = 20000.0f; //zadeklaruj zmienną przechowującą aktualny kąt obrotu

	glfwSetTime(0); //Wyzeruj licznik czasu

	std::string windowTitle;

	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
		windowTitle = appParams.name + " - " + "Camera: " + std::to_string(cameraPos.x) + "," + std::to_string(cameraPos.y) + "," + std::to_string(cameraPos.z);
		glfwSetWindowTitle(window, windowTitle.c_str());
		angle_x += (float)(speed_x * glfwGetTime()); //Oblicz kąt o jaki obiekt obrócił się podczas poprzedniej klatki
		angle_y += (float)(speed_y * glfwGetTime()); //Oblicz kąt o jaki obiekt obrócił się podczas poprzedniej klatki

		cameraPos.x += (float)(cam_speed_x * glfwGetTime()); //Oblicz kąt o jaki obiekt obrócił się podczas poprzedniej klatki
		cameraPos.y += (float)(cam_speed_y * glfwGetTime()); //Oblicz kąt o jaki obiekt obrócił się podczas poprzedniej klatki
		cameraPos.z += (float)(cam_speed_z * glfwGetTime()); //Oblicz kąt o jaki obiekt obrócił się podczas poprzedniej klatki

		glfwSetTime(0); //Wyzeruj licznik czasu
		drawScene(window, angle_x, angle_y, cam_x, cam_y, cam_z); //Wykonaj procedurę rysującą
		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
		//printf("cam: %f, %f, %f\n", cam_x,cam_y,cam_z);
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}
