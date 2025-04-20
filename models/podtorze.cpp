/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#include <vector>
#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "tiny_obj_loader.h"
#include "lodepng.h"

#include "podtorze.h"


namespace Models {

	Podtorze podtorze;

	Podtorze::Podtorze() {
		modelFileName = "00_podtorze.obj";
		loadModelFromFile();
	}
	
	
	GLuint Podtorze::readTexture(const char* filename) { //Deklaracja globalna
		GLuint tex;
		glActiveTexture(GL_TEXTURE0);
		//Wczytanie do pamięci komputera
		std::vector<unsigned char> image; //Alokuj wektor do wczytania obrazka
		unsigned width, height; //Zmienne do których wczytamy wymiary obrazka
		//Wczytaj obrazek
		unsigned error = lodepng::decode(image, width, height, filename);
		//Import do pamięci karty graficznej
		glGenTextures(1, &tex); //Zainicjuj jeden uchwyt
		glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
		//Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		return tex;
	}


	Podtorze::~Podtorze() {
	}


	void Podtorze::drawSolid(bool smooth) {
		tex = readTexture("obj/Stone_Marble.png");
		
		glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);


		glVertexAttribPointer(0,4,GL_FLOAT,false,0,vertices);
        if (smooth) glVertexAttribPointer(1,4,GL_FLOAT,false,0,normals);
        else glVertexAttribPointer(1,4,GL_FLOAT,false,0,vertexNormals);
        glVertexAttribPointer(2,4,GL_FLOAT,false,0,texCoords);
        glVertexAttribPointer(3,4,GL_FLOAT,false,0,colors);

        glDrawArrays(GL_TRIANGLES,0,vertexCount);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(3);
	}

}
