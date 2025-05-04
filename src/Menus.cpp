#include "Menus.h"
#include "freeglut.h"
#include "ETSIDI.h"


void Menus::Inicializa() {
	// Cargamos las dimensiones de la imagen
	dimX = 1024.0f;
	dimY = 1536.0f;
}

void Menus::Draw() {
	if (menu == MENU_PPAL) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-10.0, 10.0, 0.0, 15.0, -10.0, 10.0); // Valor inicial
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Ancho y alto iniciales:
		float ancho = 10.0f; // valor arbitrario
		float alto = ancho * (dimY / dimX); // mantener proporción de la imagen


		// Dibujo del fondo
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/MenuPpal_ED.png").id);
		glDisable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glBegin(GL_POLYGON);
		glTexCoord2d(0, 1);  glVertex3d(-ancho, 0, -1);
		glTexCoord2d(1, 1);  glVertex3d(ancho, 0, -1);
		glTexCoord2d(1, 0);  glVertex3d(ancho, alto, -1);
		glTexCoord2d(0, 0);  glVertex3d(-ancho, alto, -1);
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
	}
	
}

void Menus::Reshape(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float aspectImage = dimX / dimY;  
	float aspectWindow = (float)width / (float)height;

	if (aspectWindow > aspectImage) {
		// Ventana más ancha que la imagen: se ajusta en Y
		float viewWidth = aspectWindow * 15.0f; // 15 es la altura del fondo
		glOrtho(-viewWidth / 2.0f, viewWidth / 2.0f, 0, 15.0f, -10.0f, 10.0f);
	}
	else {
		// Ventana más alta que la imagen: se ajusta en X
		float viewHeight = 20.0f / aspectWindow; // 20 es el ancho del fondo
		glOrtho(-10.0f, 10.0f, 7.5f - viewHeight / 2.0f, 7.5f + viewHeight / 2.0f, -10.0f, 10.0f);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
