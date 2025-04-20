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


#include "podklad.h"

#include <vector>
#include <iostream>
#include <string>

#include "tiny_obj_loader.h"

namespace Models {

	Podklad podklad;

	Podklad::Podklad() {
        modelFileName = "00_podklad.obj";
        loadModelFromFile();
    }


	Podklad::~Podklad() {
	}


	void Podklad::drawSolid(bool smooth) {
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
