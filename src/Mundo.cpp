#include "Mundo.h"
#include "freeglut.h"
#include "ETSIDI.h"
#include <vector>
#include <iostream>
using namespace std;

void Mundo::Inicializa() {
	menus.Inicializa();
	tablero.Inicializa();
	tablero.setLogica(&logica);
	logica.inicializarTablero(tablero);
}


void Mundo::clicPos(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		// Obtener matrices actuales
		GLdouble modelview[16];
		glGetDoublev(GL_MODELVIEW_MATRIX, modelview);

		GLdouble projection[16];
		glGetDoublev(GL_PROJECTION_MATRIX, projection);

		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);

		// Invertir coordenada Y (GL tiene el origen en esquina inferior izquierda)
		GLdouble winX = x;
		GLdouble winY = viewport[3] - y;
		GLdouble winZ{}; //Consideramos profundidad 0

		// Coordenadas del mundo
		GLdouble posX, posY, posZ;
		gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ); // Conversión coordenadas de la pantalla a coordenadas del mundo
	
		std::cout << "Clic 2D en: (" << posX << ", " << posY << ")\n";
		if (menus.get_menu() == MENU_MODO) {
			// Clic en Petty:
			if (posX >= -1 && posX <= 1 && posY >= -1.9 && posY <= -1.4) {
				menus.set_modo(PETTY);
				menus.set_menu(JUEGO);
				// INICIALIZA TABLERO PETTY
			}
			// Clic en esquinas opuestas
			if (posX >= -1.7 && posX <= 1.7 && posY >= -2.6  && posY <= -2.1) {
				menus.set_modo(OPUESTAS);
				menus.set_menu(JUEGO);

			}
		}
		if(menus.get_menu() == MENU_PPAL){
			// Clic en 1 vs 1:
			if (posX >= -1 && posX <= 1 && posY >= -1.4 && posY <= -1) {
				menus.set_riv(J_VS_J);
				menus.set_menu(MENU_MODO);
			}
			// Clic en J vs IA
			if (posX >= -1.15 && posX <= 1.15 && posY >= -2.1 && posY <= -1.65) {
				menus.set_riv(J_VS_IA);
				menus.set_menu(MENU_MODO);

			}
		}
		

	}
}

void Mundo::Draw() {
	if (menus.get_menu() == MENU_PPAL || menus.get_menu() == MENU_MODO) {
		menus.Draw();
	}
	else if (menus.get_menu() == JUEGO) {
		tablero.Draw();
	}


}


void Mundo::Reshape(int width, int height) {
	if (menus.get_menu() == MENU_PPAL || menus.get_menu() == MENU_MODO) {
		menus.Reshape(width, height);
	}
	else if (menus.get_menu() == JUEGO) {
		tablero.reshape(width, height);
	}

}
