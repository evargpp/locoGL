﻿#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H


#include <GL/glew.h>
#include "stdio.h"



class ShaderProgram {
private:
	GLuint shaderProgram; //Uchwyt reprezentujący program cieniujacy
	GLuint vertexShader; //Uchwyt reprezentujący vertex shader
	GLuint geometryShader; //Uchwyt reprezentujący geometry shader
	GLuint fragmentShader; //Uchwyt reprezentujący fragment shader
	char* readFile(const char* fileName); //metoda wczytująca plik tekstowy do tablicy znaków
	GLuint loadShader(GLenum shaderType,const char* fileName); //Metoda wczytuje i kompiluje shader, a następnie zwraca jego uchwyt
public:
	ShaderProgram(const char* vertexShaderFile,const char* geometryShaderFile,const char* fragmentShaderFile);
	~ShaderProgram();
	void use(); //Włącza wykorzystywanie programu cieniującego
	GLuint u(const char* variableName); //Pobiera numer slotu związanego z daną zmienną jednorodną
	GLuint a(const char* variableName); //Pobiera numer slotu związanego z danym atrybutem
};



//extern ShaderProgram* spConstant;
//extern ShaderProgram* spLambert;
//extern ShaderProgram* spTextured;
//extern ShaderProgram* spColored;
//extern ShaderProgram* spLambertTextured;
extern ShaderProgram* shader;

void initShaders();
void freeShaders();

#endif
