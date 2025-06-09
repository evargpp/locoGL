#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>

#include "OpenGLCommon.h"
#include "Model.h"

using namespace std;
using namespace glm;


class Terrain : public Model {
public:
	Terrain();
	~Terrain();
	virtual void drawSolid(bool smooth = false);
	void Draw();
	void LoadHeightmapTerrain(const char* filename, int width, int height);
	vector<vec4> internalVertices;
	vector<vec4> internalFaceNormals;
	vector<vec4> internalVertexNormals;

private:
	glm::mat4 M;
};


//extern Terrain terrain;