#include "Mundo.h"
#include "freeglut.h"
#include "ETSIDI.h"
#include "Sonido.h"
#include <vector>
#include <iostream>

using namespace std;

void Mundo::Inicializa() {
	tablero.Inicializa();
	tablero.setLogica(&logica);
	ia.setLogica(&logica);
	logica.inicializarTablero();
}


void Mundo::clicPos(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		Coords2D pos_clic{}, centro_casilla_clic{};
		Posicion casilla_clic{};
		Pieza* pieza_clic = nullptr;
		pos_clic = coorClics_to_cords2D(x, y);
		casilla_clic = pos_clic.coords_to_casilla();
		

		if (menus.get_menu() == MENU_PPAL || menus.get_menu() == MENU_MODO) {
			std::cout << "Clic 2D en: (" << pos_clic.x << ", " << pos_clic.y << ")\n";
			menus.coor_menus(pos_clic.x, pos_clic.y);
			logica.setearPosicionesIniciales(menus.get_modo());
		}
		else if (menus.get_menu() == JUEGO) {
			if (logica.finPartida) {
				std::cout << "El juego ha terminado. Reinicia para jugar de nuevo.\n";
				return;
			}

			Pieza* seleccionada = tablero.get_pieza_selec(); // obtenemos la pieza actualmente seleccionada
			if (seleccionada == nullptr) {
				if (!casilla_clic.esValida()) return;

				centro_casilla_clic = casilla_clic.centro_en_coords();

				std::cout << "Que es la casilla: (" << casilla_clic.fil << ", " << casilla_clic.col << ")\n";
				std::cout << "Cuyo centro esta en: (" << centro_casilla_clic.x << ", " << centro_casilla_clic.y << ")\n";

				if (logica.coronacion.activa) {
					std::cout << "Esperando elección de pieza para coronación.\n";
					return;
				}

				pieza_clic = logica.obtenerPieza(casilla_clic);
				if (pieza_clic != nullptr && pieza_clic->getColor() == logica.turno) {
					pieza_clic->movimientosValidos(logica);
					tablero.set_pieza_selec(pieza_clic); //actualizamos pieza seleccionada

				}
			}
			else {
				if (!casilla_clic.esValida()) return; // EVITA CLICS FUERA DEL TABLERO
				bool ok = logica.moverPieza(seleccionada, casilla_clic); // se intenta mover directamente
				tablero.set_pieza_selec(nullptr); // se limpia la seleccion, se haya movido o no
				if (ok) {
					ia.elegirMejorMovimiento(logica.getTurno());
				}
				
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
	if (menus.get_menu() == MENU_PPAL || menus.get_menu() == MENU_MODO || menus.get_menu() == MENU_IA) {
		menus.Draw();
		Sonido::iniciarMusicaMenu();
	}
	else if (menus.get_menu() == JUEGO) {

		tablero.Draw();
		/*tablero.DrawTurno();
		tablero.DrawIndices();*/
		Sonido::detenerMusica();
		if(tablero.get_pieza_selec()!=nullptr)
			tablero.DrawMovsValidos();

		if (!logica.finPartida) {
			tablero.Draw();
			if (logica.coronacion.activa) {
				ETSIDI::setTextColor(0, 0, 0); 
				glPushMatrix();
				glTranslatef(0.0f, -0.2f, 0.f);
				ETSIDI::printxy("Elija una pieza a la que coronar:", -5.0f, 3.0f, 2.0f);
				glTranslatef(0.0f, -0.3f, 0.f);
				ETSIDI::printxy("Dama (d), Torre (t), Alfil (a) o Caballo (c)", -5.0f, 3.0f, 2.0f);
				glPopMatrix();
			}
		
		}
		else if (logica.finPartida) {
			tablero.DrawFinPartida(logica.ganador, logica.tablas);
		}

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

void Mundo::OnKeyboardDown(unsigned char key) {
	if (key == 'H' || key == 'h') {
		logica.printHistorial();
	}
	if (logica.finPartida && key == 'r') {
		menus.set_menu(MENU_PPAL);
		Inicializa();
	}
	if (logica.coronacion.activa) {
		switch (key) {
		case 'd': logica.realizarCoronacion(Pieza::tipo_t::DAMA); break;
		case 't': logica.realizarCoronacion(Pieza::tipo_t::TORRE); break;
		case 'a': logica.realizarCoronacion(Pieza::tipo_t::ALFIL); break;
		case 'c': logica.realizarCoronacion(Pieza::tipo_t::CABALLO); break;
		}
	}
}

