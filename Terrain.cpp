#include "Terrain.h"
#include "shaderprogram.h"
#include <stb_image.h>
#include <iostream>


Terrain::Terrain()
{
	this->M = glm::mat4(1.0f);

	int imgWidth, imgHeight, nrChannels;
	unsigned char* heightData = stbi_load("assets/heightmap.png", &imgWidth, &imgHeight, &nrChannels, 1);
	if (!heightData) {
		std::cerr << "Failed to load heightmap" << std::endl;
		exit(EXIT_FAILURE);
	}


	//this->szyna = new BasicModel("00_szyna.dae");
	//this->podklad = new BasicModel("00_podklad.dae");
	//this->podtorze = new BasicModel("00_podtorze.dae");

    LoadHeightmapTerrain("assets/heightmap.png", 1000, 1000);
}

Terrain::~Terrain()
{
}

void Terrain::LoadHeightmapTerrain(const char* filename, int width, int height) {
	int imgWidth, imgHeight, nrChannels;
	unsigned char* heightData = stbi_load(filename, &imgWidth, &imgHeight, &nrChannels, 1);
	if (!heightData) {
		std::cerr << "Failed to load heightmap: " << filename << std::endl;
		exit(EXIT_FAILURE);
	}

	if (imgWidth != width || imgHeight != height) {
		std::cerr << "Warning: heightmap size doesn't match expected dimensions!" << std::endl;
	}

	const float SIZE = 1000.0f;      // rozmiar terenu w jednostkach œwiata
	const float MAX_HEIGHT = 100.0f; // maksymalna wysokoœæ terenu

	const int VERTEX_COUNT_X = width;
	const int VERTEX_COUNT_Z = height;

	std::vector<float> vertices;  // x, y, z
	std::vector<float> normals;   // nx, ny, nz
	std::vector<float> texCoords; // u, v
	std::vector<unsigned int> indices;

	// Najpierw generujemy wierzcho³ki i tekstury
	for (int z = 0; z < VERTEX_COUNT_Z; ++z) {
		for (int x = 0; x < VERTEX_COUNT_X; ++x) {
			float xpos = (float)x / (VERTEX_COUNT_X - 1) * SIZE;
			float zpos = (float)z / (VERTEX_COUNT_Z - 1) * SIZE;

			// wysokoœæ z obrazka, skalowana do MAX_HEIGHT
			int idx = z * imgWidth + x;
			float y = (float)heightData[idx] / 255.0f * MAX_HEIGHT;

			vertices.push_back(xpos);
			vertices.push_back(y);
			vertices.push_back(zpos);

			// tekstura (u,v)
			texCoords.push_back((float)x / (VERTEX_COUNT_X - 1));
			texCoords.push_back((float)z / (VERTEX_COUNT_Z - 1));

			//std::cout << xpos << "," << zpos << "," << x << "," << std::endl;
		}
	}

	// Funkcja pomocnicza do pobrania wysokoœci (z klamrami na krawêdziach)
	auto getHeight = [&](int x, int z) -> float {
		if (x < 0) x = 0;
		else if (x >= VERTEX_COUNT_X) x = VERTEX_COUNT_X - 1;
		if (z < 0) z = 0;
		else if (z >= VERTEX_COUNT_Z) z = VERTEX_COUNT_Z - 1;
		int idx = z * imgWidth + x;
		return (float)heightData[idx] / 255.0f * MAX_HEIGHT;
		};

	// Obliczamy normalne przez aproksymacjê pochodnych
	for (int z = 0; z < VERTEX_COUNT_Z; ++z) {
		for (int x = 0; x < VERTEX_COUNT_X; ++x) {
			float heightL = getHeight(x - 1, z);
			float heightR = getHeight(x + 1, z);
			float heightD = getHeight(x, z - 1);
			float heightU = getHeight(x, z + 1);

			glm::vec3 normal = glm::normalize(glm::vec3(heightL - heightR, 2.0f, heightD - heightU));
			normals.push_back(normal.x);
			normals.push_back(normal.y);
			normals.push_back(normal.z);
		}
	}

	stbi_image_free(heightData);

	// Generujemy indeksy do rysowania siatki (triangle strip)
	for (int z = 0; z < VERTEX_COUNT_Z - 1; ++z) {
		for (int x = 0; x < VERTEX_COUNT_X - 1; ++x) {
			int topLeft = (z * VERTEX_COUNT_X) + x;
			int topRight = topLeft + 1;
			int bottomLeft = ((z + 1) * VERTEX_COUNT_X) + x;
			int bottomRight = bottomLeft + 1;

			// Dwa trójk¹ty na kwadrat
			indices.push_back(topLeft);
			indices.push_back(bottomLeft);
			indices.push_back(topRight);

			indices.push_back(topRight);
			indices.push_back(bottomLeft);
			indices.push_back(bottomRight);
		}
	}

	std::vector<float> finalVertexBuffer;

	for (unsigned int idx : indices) {
		// pozycja
		finalVertexBuffer.push_back(vertices[idx * 3 + 0]);
		finalVertexBuffer.push_back(vertices[idx * 3 + 1]);
		finalVertexBuffer.push_back(vertices[idx * 3 + 2]);

		// normalna
		finalVertexBuffer.push_back(normals[idx * 3 + 0]);
		finalVertexBuffer.push_back(normals[idx * 3 + 1]);
		finalVertexBuffer.push_back(normals[idx * 3 + 2]);

		// tekstura
		finalVertexBuffer.push_back(texCoords[idx * 2 + 0]);
		finalVertexBuffer.push_back(texCoords[idx * 2 + 1]);
	}

	this->vertices = (float*)finalVertexBuffer.data();
	//normals = (float*)internalFaceNormals.data();
	//vertexNormals = (float*)internalFaceNormals.data();

	this->vertexCount = finalVertexBuffer.size();
	//texCoords = (float*)internalTexCoords.data();


/*
	// Tworzymy VAO i VBO
	unsigned int VAO, VBO[3], EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(3, VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	// Wierzcho³ki (atrybut 0)
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	// Normalne (atrybut 1)
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);

	// Tekstury (atrybut 2)
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(float), texCoords.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(2);

	// Indeksy
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
*/
}


void Terrain::drawSolid(bool smooth)
{
	std::cout << "Vertex count: " << vertexCount << std::endl;

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, vertices);
	if (smooth) glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, normals);
	else glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, vertexNormals);
	glVertexAttribPointer(2, 4, GL_FLOAT, false, 0, texCoords);
	glVertexAttribPointer(3, 4, GL_FLOAT, false, 0, colors);

	glUniformMatrix4fv(shader->u("M"), 1, false, glm::value_ptr(this->M));
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);

}

void Terrain::Draw() {
	drawSolid();
}