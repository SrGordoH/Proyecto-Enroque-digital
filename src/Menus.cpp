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

	float aspectWindow = (float)width / (float)height;
	float imageAspect = dimX / dimY;

	float ZOOM_FACTOR = 0.6f; // Cuanto más pequeño, más "zoom in"

	if (aspectWindow > imageAspect) {
		// Ajustamos altura
		float viewHeight = 10.0f * ZOOM_FACTOR;
		float viewWidth = viewHeight * aspectWindow;
		glOrtho(-viewWidth / 2.0f, viewWidth / 2.0f, -viewHeight / 2.0f, viewHeight / 2.0f, -10.0f, 10.0f);
	}
	else {
		// Ajustamos ancho
		float viewWidth = 10.0f * ZOOM_FACTOR;
		float viewHeight = viewWidth / aspectWindow;
		glOrtho(-viewWidth / 2.0f, viewWidth / 2.0f, -viewHeight / 2.0f, viewHeight / 2.0f, -10.0f, 10.0f);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


