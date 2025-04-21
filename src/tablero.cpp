#include "tablero.h"
#include "freeglut.h"

void Tablero::Draw() {
	ancho_casillas = 0.1;

	center_x = num_casillas * ancho_casillas / 2;
	center_y = -num_casillas * ancho_casillas / 2;
	

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
	for (int i = 0; i < num_casillas; i++) {
		for (int j = 0; j < num_casillas; j++) {
			DrawCell(i, j);
		}
	}

	//// Rectángulo transparente encima del tablero para capturar clics
	//glDisable(GL_LIGHTING);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // blanco con alpha
	//glPushMatrix();
	//glTranslatef(center_x, center_y, 0);
	//glTranslatef(-center_x, -center_y, -0);
	//glRectf(num_casillas* ancho_casillas / 2.0f, num_casillas* ancho_casillas / 2.0f,
	//	-num_casillas* ancho_casillas / 2.0f, -num_casillas* ancho_casillas / 2.0f);
	//glEnable(GL_LIGHTING);
	//glPopMatrix();
}

void Tablero::DrawGrid() {
	// Color negro para las líneas
	glClearColor(1.0f, 1.0f, 1.0f, 0); // Color de fondo blanco

	// Dimensión total del tablero (de 0 a N*width)
	float totalSize = num_casillas * ancho_casillas;

	for (int i = 0; i <= num_casillas; ++i) {
		// Líneas del borde más gruesas
		if (i == 0 || i == num_casillas)
			glLineWidth(3.0f);
		else
			glLineWidth(1.0f);

		glBegin(GL_LINES);

		// Línea vertical (de arriba a abajo)
		glVertex3f(i * ancho_casillas, 0.0f, 0.0f);         // Desde (i, 0)
		glVertex3f(i * ancho_casillas, -totalSize, 0.0f);   // Hasta (i, -N)

		// Línea horizontal (de izquierda a derecha)
		glVertex3f(0.0f, -i * ancho_casillas, 0.0f);        // Desde (0, -i)
		glVertex3f(totalSize, -i * ancho_casillas, 0.0f);   // Hasta (N, -i)

		glEnd();
	}

	// Restaurar grosor estándar
	glLineWidth(1.0f);
}

void Tablero::DrawCell(int i, int j) {
	// Alterna color: blanco y negro
	if ((i + j) % 2 == 0)
		glColor3f(0.0f, 1.0f, 0.0f); // Blanco
	else
		glColor3f(0.5f, 1.0f, 0.5f); // Negro

	float x = j * ancho_casillas;
	float y = -i * ancho_casillas;

	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + ancho_casillas, y);
	glVertex2f(x + ancho_casillas, y - ancho_casillas);
	glVertex2f(x, y - ancho_casillas);
	glEnd();
}

