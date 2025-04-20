#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>

#include "OpenGLCommon.h"

#include "BasicModel.h"
#include "shaderprogram.h"


BasicModel::BasicModel() {
}


BasicModel::BasicModel(std::string modelFileName) {
	this->modelFileName = modelFileName;
	loadModelFromFile();
	this->M = glm::mat4(1.0f);
}


BasicModel::~BasicModel() {
}


void BasicModel::drawSolid(bool smooth) {
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, vertices);
	if (smooth) glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, normals);
	else glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, vertexNormals);
	glVertexAttribPointer(2, 4, GL_FLOAT, false, 0, texCoords);
	glVertexAttribPointer(3, 4, GL_FLOAT, false, 0, colors);

	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(this->M));
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
}

