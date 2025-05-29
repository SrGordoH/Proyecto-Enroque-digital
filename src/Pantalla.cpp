#include "Pantalla.h"

void Pantalla::inicializaMenu(int tipo) {
		Boton Ppal_JvsJ{ -1.72f,1.4f,-1.28f,-0.65f }, Ppal_JvsIA{ -2.08f,1.87f,-2.17f,-1.55f };

		Boton Modo_Facil{ -1.72f,1.4f,-1.28f,-0.65f }, Modo_Dificil{ -2.08f,1.87f,-2.17f,-1.55f };
		Boton Modo_Petty{ -1.66f,1.0f,-1.76f,-1.25f }, Modo_Opuestas{ -2.2f,1.6f, -2.36f, -1.88f};
		Boton Salida{ 3.38f, 4.18f, -2.1f, -1.17f };
		Boton Salida2{ 3.45f, 4.25f, -2.6f, -1.67f };
	switch (tipo) {
	case 0: // Menú principal
		boton1 = Ppal_JvsJ;
		boton2 = Ppal_JvsIA;
		dimX = 1536.0f;
		dimY = 1024.0f;
		ruta_pantalla = "imagenes/Menu_Ppal_final.png";
		break;
	case 1: // Menú modo
		boton_salida = Salida;
		boton1 = Modo_Petty;
		boton2 = Modo_Opuestas;
		dimX = 1536.0f;
		dimY = 1024.0f;
		ruta_pantalla = "imagenes/MenuModos_final.png";
		break;
	case 2: // Menú dificultad
		boton_salida = Salida2;
		boton1 = Modo_Facil;
		boton2 = Modo_Dificil;
		dimX = 1536.0f;
		dimY = 1024.0f;
		ruta_pantalla = "imagenes/menu_IA.png";
		break;
	}
}

void Pantalla::dibujaPantalla() {

	// Ancho y alto iniciales:
	float ancho = 10.0f; // valor arbitrario
	float alto = ancho * (dimY / dimX); // mantener proporción de la imagen

	// Dibujo del fondo
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(ruta_pantalla.c_str()).id);
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


