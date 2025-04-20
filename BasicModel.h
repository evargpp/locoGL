#ifndef BASIC_MODEL_H
#define BASIC_MODEL_H

#include "Model.h"
#include <string>


namespace Models {
	
	using namespace std;
	using namespace glm;

	class BasicModel : public Model {
		public:
			BasicModel();
			BasicModel(std::string modelFileName);
			virtual ~BasicModel();
			virtual void drawSolid(bool smooth=false);
		private:
			vector<vec4> internalVertices;
			vector<vec4> internalFaceNormals;
			vector<vec4> internalVertexNormals;
	};

	extern BasicModel basicModel;
}


#endif
