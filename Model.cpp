#include <iostream>
#include <chrono>
#include <stdlib.h>
#include <stdio.h>

#include "OpenGLCommon.h"

#include "model.h"
#include "config.h"
#include "shaderprogram.h"

void Model::Clear() {
	this->M = glm::mat4(1.0f);
};

glm::mat4 Model::GetModelMatrix() {
	return this->M;
};


void Model::RotateX(float angle) {
	this->M = glm::rotate(this->M, angle, glm::vec3(1.0f, 0.0f, 0.0f));
};


void Model::RotateY(float angle) {
	this->M = glm::rotate(this->M, angle, glm::vec3(0.0f, 1.0f, 0.0f));
};


void Model::RotateZ(float angle) {
	this->M = glm::rotate(this->M, angle, glm::vec3(0.0f, 0.0f, 1.0f));
};

void Model::Translate(float x, float y, float z) {
	this->M = glm::translate(this->M, glm::vec3(x, y, z));
}


void Model::Translate(glm::vec3 vec)
{
	this->M = glm::translate(M, vec);
}


void Model::drawWire(bool smooth) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	drawSolid(smooth);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


void Model::loadModelFromFile(void) {
	internalVertices.clear();
	internalFaceNormals.clear();
	internalVertexNormals.clear();
	internalTexCoords.clear();

	std::string inputfile = Config::modelsFolder + modelFileName;

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, inputfile.c_str(), Config::modelsFolder.c_str());

	if (!warn.empty()) {
		std::cout << warn << "1" << std::endl;
	}

	if (!err.empty()) {
		std::cerr << err << "2" << std::endl;
	}

	if (!ret) {
		exit(1);
	}

	// Loop over shapes
	for (size_t s = 0; s < shapes.size(); s++) {
		// Loop over faces(polygon)
		size_t index_offset = 0;

		glm::vec4 vv[3];
		glm::vec4 nn[3];

		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

			// Loop over vertices in the face.
			for (size_t v = 0; v < fv; v++) {
				// access to vertex
				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

				tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
				tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
				tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];

				//internalVertices.push_back(vec4(vx / 0.03937f, vy / 0.03937f, vz / 0.03937f, 1.0f));
				vv[v] = glm::vec4(vx / 0.03937f, vy / 0.03937f, vz / 0.03937f, 1.0f);

				// Check if `normal_index` is zero or positive. negative = no normal data
				if (idx.normal_index >= 0) {
					tinyobj::real_t nx = 1.0f * attrib.normals[3 * size_t(idx.normal_index) + 0];
					tinyobj::real_t ny = 1.0f * attrib.normals[3 * size_t(idx.normal_index) + 1];
					tinyobj::real_t nz = 1.0f * attrib.normals[3 * size_t(idx.normal_index) + 2];

					const float normalFix = 1.0f;
					//internalFaceNormals.push_back(vec4(normalFix*nx, normalFix*ny, normalFix*nz, 0.0f));
					nn[v] = glm::vec4(normalFix * nx, normalFix * ny, normalFix * nz, 0.0f);
				}

				// Check if `texcoord_index` is zero or positive. negative = no texcoord data
				if (idx.texcoord_index >= 0) {
					tinyobj::real_t tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
					tinyobj::real_t ty = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
					internalTexCoords.push_back(glm::vec2(tx, ty));
				}
				// Optional: vertex colors
				// tinyobj::real_t red   = attrib.colors[3*size_t(idx.vertex_index)+0];
				// tinyobj::real_t green = attrib.colors[3*size_t(idx.vertex_index)+1];
				// tinyobj::real_t blue  = attrib.colors[3*size_t(idx.vertex_index)+2];
			}
			index_offset += fv;

			internalVertices.push_back(vv[0]);
			internalVertices.push_back(vv[1]);
			internalVertices.push_back(vv[2]);

			internalFaceNormals.push_back(nn[0]);
			internalFaceNormals.push_back(nn[1]);
			internalFaceNormals.push_back(nn[2]);


			// per-face material
			shapes[s].mesh.material_ids[f];
		}
	}

	vertices = (float*)internalVertices.data();
	normals = (float*)internalFaceNormals.data();
	vertexNormals = (float*)internalFaceNormals.data();

	vertexCount = internalVertices.size();
	texCoords = (float*)internalTexCoords.data();

};

