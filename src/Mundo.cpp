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

		Coords2D pos_clic{}, centro_casilla_clic{};
		Posicion casilla_clic{};
		Pieza* pieza_clic = nullptr;
		pos_clic = coorClics_to_cords2D(x, y);
		

		if (menus.get_menu() == MENU_PPAL || menus.get_menu() == MENU_MODO) {
			std::cout << "Clic 2D en: (" << pos_clic.x << ", " << pos_clic.y << ")\n";
			menus.coor_menus(pos_clic.x, pos_clic.y);
			logica.setearPosicionesIniciales(menus.get_modo());
		}
		else if (menus.get_menu() == JUEGO) {
			Pieza* seleccionada = tablero.get_pieza_selec(); // obtenemos la pieza actualmente seleccionada
			if (seleccionada == nullptr) {
				casilla_clic = pos_clic.coords_to_casilla();
				if (!casilla_clic.esValida()) return;

				centro_casilla_clic = casilla_clic.centro_en_coords();

				std::cout << "Que es la casilla: (" << casilla_clic.fil << ", " << casilla_clic.col << ")\n";
				std::cout << "Cuyo centro esta en: (" << centro_casilla_clic.x << ", " << centro_casilla_clic.y << ")\n";

				pieza_clic = logica.obtenerPieza(casilla_clic);
				if (pieza_clic != nullptr && pieza_clic->getColor() == logica.turno) {
					pieza_clic->movimientosValidos(logica);
					tablero.set_pieza_selec(pieza_clic); //actualizamos pieza seleccionada

				}
			}
			else {
				casilla_clic = pos_clic.coords_to_casilla(); // se calcula la casilla clicada
				if (!casilla_clic.esValida()) return; // EVITA CLICS FUERA DEL TABLERO
				bool ok = logica.moverPieza(seleccionada, casilla_clic); // se intenta mover directamente
				tablero.set_pieza_selec(nullptr); // se limpia la seleccion, se haya movido o no
			}



		}
	}
}

Coords2D Mundo::coorClics_to_cords2D(int x, int y) {
	
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
	Coords2D pos_actual{};
	return pos_actual = { (float)posX, (float)posY };
}



void Mundo::Draw() {
	if (menus.get_menu() == MENU_PPAL || menus.get_menu() == MENU_MODO) {
		menus.Draw();
	}
	else if (menus.get_menu() == JUEGO) {
		tablero.Draw();
		if(tablero.get_pieza_selec()!=nullptr)
			tablero.DrawMovsValidos();
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
