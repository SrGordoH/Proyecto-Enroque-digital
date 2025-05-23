#include "Menus.h"
#include "freeglut.h"
#include "ETSIDI.h"


void Menus::Inicializa() {
	// Cargamos las dimensiones de la imagen
	dimX = 1920.0f;  // 1920x1080
	dimY = 1080.0f;
}

void Menus::Draw() {
	if (menu == MENU_PPAL) {
		
		// Ancho y alto iniciales:
		float ancho = 10.0f; // valor arbitrario
		float alto = ancho * (dimY / dimX); // mantener proporción de la imagen

		// Dibujo del fondo
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/MenuPpal_1920x1080.png").id);
		glDisable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glBegin(GL_POLYGON);
		glTexCoord2d(0, 1);  glVertex3d(-ancho / 2, -alto / 2, 0);
		glTexCoord2d(1, 1);  glVertex3d(ancho / 2, -alto / 2, 0);
		glTexCoord2d(1, 0);  glVertex3d(ancho / 2, alto / 2, 0);
		glTexCoord2d(0, 0);  glVertex3d(-ancho / 2, alto / 2, 0);
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
	}
	else if(menu == MENU_MODO){
		float ancho = 10.0f; // factor de escala
		float alto = ancho * (dimY / dimX); // mantener proporción de la imagen

		// Dibujo del fondo
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/MenuModo_1920x1080.png").id);
		glDisable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glBegin(GL_POLYGON);
		glTexCoord2d(0, 1);  glVertex3d(-ancho / 2, -alto / 2, 0);
		glTexCoord2d(1, 1);  glVertex3d(ancho / 2, -alto / 2, 0);
		glTexCoord2d(1, 0);  glVertex3d(ancho / 2, alto / 2, 0);
		glTexCoord2d(0, 0);  glVertex3d(-ancho / 2, alto / 2, 0);
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
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
	if (get_menu() == MENU_MODO) {
		// Clic en Petty:
		if (Modo_Petty.clic(posX, posY)) {
			set_modo(PETTY);
			set_menu(JUEGO);

			// INICIALIZA TABLERO PETTY
		}
		// Clic en esquinas opuestas
		if (Modo_Opuestas.clic(posX, posY)) {

			set_modo(OPUESTAS);
			set_menu(JUEGO);

		}
	}
	if (get_menu() == MENU_PPAL) {
		// Clic en 1 vs 1:
		if (Ppal_JvsJ.clic(posX, posY)) {
			set_riv(J_VS_J);
			set_menu(MENU_MODO);
		}
		// Clic en J vs IA
		if (Ppal_JvsIA.clic(posX, posY)) {
			set_riv(J_VS_IA);
			set_menu(MENU_MODO);
		}
	}
}

