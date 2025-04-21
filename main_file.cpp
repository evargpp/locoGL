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

Infrastructure infrastructure;
Train train;
Camera camera;


struct AppParams {
	int screenWidth;
	int screenHeight;
	std::string name;
} appParams = { 2000, 1600, "Hello locoGL!" };

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
			//speed_y = -PI;
			camera.deltaHAngle(glm::radians(-15.0f));
		}
		if (key == GLFW_KEY_RIGHT) {
			camera.deltaHAngle(glm::radians(15.0f));
			//speed_y = PI;
		}
		if (key == GLFW_KEY_UP) {
			camera.deltaVAngle(glm::radians(15.0f));
			//speed_x = -PI;
		}
		if (key == GLFW_KEY_DOWN) {
			camera.deltaVAngle(glm::radians(-15.0f));
			//speed_x = PI;
		}
		if (key == GLFW_KEY_PAGE_UP) {
			camera.deltaZoom(1000);
		}
		if (key == GLFW_KEY_PAGE_DOWN) {
			camera.deltaZoom(-1000);
		}

		if (key == GLFW_KEY_1) {
			train.setAcceleration(1.0f);
		}

		if (key == GLFW_KEY_2) {
			train.setAcceleration(2.0f);
		}

		if (key == GLFW_KEY_3) {
			train.setAcceleration(3.0f);
		}

		if (key == GLFW_KEY_4) {
			train.setAcceleration(4.0f);
		}

		if (key == GLFW_KEY_0) {
			train.setAcceleration(0.0f);
		}

		if (key == GLFW_KEY_5) {
			train.setAcceleration(-1.0f);
		}

		if (key == GLFW_KEY_6) {
			train.setAcceleration(-2.0f);
		}

		if (key == GLFW_KEY_7) {
			train.setAcceleration(-3.0f);
		}

		if (key == GLFW_KEY_8) {
			train.setAcceleration(-4.0f);
		}


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

	train.SetBase(-7000.0f, 972.0f, 0.0f);
}


//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
	freeShaders();
	//************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej************
}

//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window) {
	//************Tutaj umieszczaj kod rysujący obraz******************l
	glClearColor(0.309f, 1.0f, 0.905f, 1.0f);
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
	printf("acc: %f cs: %f\n", train.getAcceleration(), train.getSpeed());

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
	//glfwSetTime(0); //Wyzeruj licznik czasu

	std::string windowTitle;

	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
		glfwSetWindowTitle(window, windowTitle.c_str());

		//glfwSetTime(0); //Wyzeruj licznik czasu
		drawScene(window); //Wykonaj procedurę rysującą
		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
		//printf("cam: %f, %f, %f\n", cam_x,cam_y,cam_z);
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}
