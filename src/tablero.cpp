#include "tablero.h"
#include "freeglut.h"
#include <iostream>  // Impresión por pantalla para hacer pruebas y debugs

void Tablero::Inicializa() {

	/*DISTANCIA DE VISTA A LA PANTALLA*/
	dist = DIST_PANTALLA;

	/*ANCHO Y ALTO DE LAS CASILLAS*/
	ancho_casillas = ANCHO_LARGO_CASILLAS;

	/*FILAS Y COLUMNAS*/
	casillas[0] = NUM_FILAS;
	casillas[1] = NUM_COLUMNAS;

	/*CENTRO PANTALLA (la queremos en el centro del tablero)*/
	center_y = casillas[0] * ancho_casillas / 2;
	center_x = casillas[1] * ancho_casillas / 2;
}



void Tablero::Draw() {

	// Borrado de la pantalla
	glClearColor(1, 1, 1, 1); // fondo blanco
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Definir punto de vista (cámara)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(center_x, center_y, dist,  // posición de la cámara
		center_x, center_y, 0, // hacia dónde mira
		0, 1, 0); // vector "arriba"

	glEnable(GL_LIGHTING);

	// Dibuja la cuadrícula y las piezas
	DrawGrid();
	for (int i = 0; i < casillas[0]; i++) {
		for (int j = 0; j < casillas[1]; j++) {
			DrawCell(i, j);
		}
	}


}

void Tablero::DrawGrid() {
	glColor3f(0.0f, 0.0f, 0.0f);
	
	float ancho = casillas[1] * ancho_casillas;
	float alto = casillas[0] * ancho_casillas;

	glLineWidth(1.0f);

	for (int i = 0; i <= casillas[1]; ++i) {
		glLineWidth((i == 0 || i == casillas[1]) ? 3.0f : 1.0f);
		glBegin(GL_LINES);
		glVertex3f(i * ancho_casillas, 0.0f, 0.0f);
		glVertex3f(i * ancho_casillas, alto, 0.0f);
		glEnd();
	}

	for (int i = 0; i <= casillas[0]; ++i) {
		glLineWidth((i == 0 || i == casillas[0]) ? 3.0f : 1.0f);
		glBegin(GL_LINES);
		glVertex3f(0.0f, i * ancho_casillas, 0.0f);
		glVertex3f(ancho, i * ancho_casillas, 0.0f);
		glEnd();
	}


	glLineWidth(1.0f);
}



void Tablero::DrawCell(int i, int j) {
	// Alterna color: blanco y negro
	if ((i + j) % 2 == 0)
		glColor3f(0.0f, 1.0f, 0.0f); // "Blanco" (verde claro)
	else
		glColor3f(0.0f, 0.5f, 0.0f); // "Negro" (verde oscuro)

	float x = j * ancho_casillas;
	float y = i * ancho_casillas; 

	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + ancho_casillas, y);
	glVertex2f(x + ancho_casillas, y + ancho_casillas);
	glVertex2f(x, y + ancho_casillas);
	glEnd();
}


bool Tablero::clicDentroTablero(float posX, float posY) {
	float ancho = casillas[1] * ancho_casillas;  
	float alto = casillas[0] * ancho_casillas;

	return (posX >= 0 && posX < ancho && posY >= 0 && posY < alto);
}

void Tablero::clicPos(int button, int state, int x, int y) {

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

		// Mostrar coordenadas en consola
		std::cout << "Clic 2D en: (" << posX << ", " << posY << ")\n"; // La coordenada 0,0 es la esquina inferior izquierda del tablero

		// Comprobación de si está dentro del tablero
		float ancho = casillas[1] * ancho_casillas;  // El tablero mide 0.5x0.6
		float alto = casillas[0] * ancho_casillas;

		if (posX >= 0 && posX < ancho && posY >= 0 && posY < alto) {
			// Determinar la celda en la que se ha hecho clic
			int j = int(posX / ancho_casillas);
			int i = int(posY / ancho_casillas);

			std::cout << "Has hecho clic dentro del tablero en la celda (" << i + 1 << ", " << j + 1 << ")\n";
		}
		else {
			std::cout << "Has hecho clic FUERA del tablero.\n";
		}
	}
}

