#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "constants.h"
#include <string>
#include <vector>
#include <glm/ext/vector_float4.hpp>


namespace Models {

	class Model {
		public:
			int vertexCount;
			float *vertices;
			float *normals;
			float *vertexNormals;
			float *texCoords;
			float *colors;

			virtual void drawSolid(bool smooth)=0;
			virtual void drawWire(bool smooth=false);
			virtual void loadModelFromFile(void);

			void Clear();
			void RotateX(float angle);
			void RotateY(float angle);
			void RotateZ(float angle);
			void Translate(float x, float y, float z);
			glm::mat4 GetModelMatrix();

		
		protected:
			std::vector<glm::vec4> internalVertices;
			std::vector<glm::vec4> internalFaceNormals;
			std::vector<glm::vec4> internalVertexNormals;
			std::vector<glm::vec2> internalTexCoords;
			std::string modelFileName;
			glm::mat4 M;
	};
}

#endif
