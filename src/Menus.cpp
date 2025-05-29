#include "Menus.h"
#include "freeglut.h"
#include "ETSIDI.h"
#include <iostream>

void Menus::Draw() {
	switch (t_menu) {
	case MENU_PPAL:
		pant_menu.inicializaMenu(t_menu);
		pant_menu.dibujaPantalla();
	case MENU_MODO:
		pant_menu.inicializaMenu(t_menu);
		pant_menu.dibujaPantalla();
	case MENU_IA:
		pant_menu.inicializaMenu(t_menu);
		pant_menu.dibujaPantalla();
	default:
		break;
	}	
}


void Menus::Reshape(int width, int height) {
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Mismo criterio que el reshape del tablero
	float aspectWindow = (float)width / (float)height;

	float imageHeight = 6.5f; // define una "altura lógica" constante
	float imageWidth = imageHeight * aspectWindow;

	glOrtho(-imageWidth / 2.0f, imageWidth / 2.0f, -imageHeight / 2.0f, imageHeight / 2.0f, -10.0, 10.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}



void Menus::coor_menus(float posX, float posY) {
	if (get_menu() == MENU_IA) {
		// Clic en FACIL:
		if (pant_menu.clic_b1(posX, posY)) {
			set_dif(FACIL);
			set_menu(JUEGO);
		}
		// Clic en DIFICIL:
		if (pant_menu.clic_b2(posX, posY)) {
			set_dif(DIFICIL);
			set_menu(JUEGO);
		}
		if (pant_menu.clic_sal(posX, posY)) {
			set_menu(MENU_PPAL);
			std::cout << "Cilc en salida." << std::endl;
		}
	}
	if (get_menu() == MENU_MODO) {
		// Clic en Petty:
		if (pant_menu.clic_b1(posX, posY)) {
			set_modo(PETTY);
			set_menu(JUEGO);

		}
		// Clic en esquinas opuestas
		if (pant_menu.clic_b2(posX, posY)) {
			set_modo(OPUESTAS);
			set_menu(JUEGO);
		}
		if (pant_menu.clic_sal(posX, posY)) {
			set_menu(MENU_PPAL);
			std::cout << "Cilc en salida." << std::endl;
		}
	}
	if (get_menu() == MENU_PPAL) {
		// Clic en 1 vs 1:
		if (pant_menu.clic_b1(posX, posY)) {
			set_riv(J_VS_J);
			set_menu(MENU_MODO);
		}
		// Clic en J vs IA
		if (pant_menu.clic_b2(posX, posY)) {
			set_riv(J_VS_IA);
			set_menu(MENU_IA);
		}
	}
}

