#include "tablero.h"
#include "Pieza.h"
#include "Tablero_logica.h"

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


	glClearColor(0.82f, 0.71f, 0.55f, 1.0f); // fondo marron (madera)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_LIGHTING); // Si solo hay colores planos, no hace falta luz

	glTranslatef((GLfloat) -center_x, (GLfloat) -center_y, (GLfloat) 0.0f);

	// Dibuja la cuadrícula y las piezas
	DrawGrid();
	for (int i = 0; i < casillas[0]; i++) {
		for (int j = 0; j < casillas[1]; j++) {
			DrawCell(i, j);
		}
	}

	glTranslatef((GLfloat) -ancho_casillas, (GLfloat) -ancho_casillas, (GLfloat) 0.2f);
	DrawPiezas();
	glTranslatef((GLfloat) ancho_casillas, (GLfloat) ancho_casillas, (GLfloat) 0.0f);
	if (get_pieza_selec() != nullptr) DrawMovsValidos();
	DrawIndices();
	DrawTurno();
}

void Tablero::DrawGrid() {

	
	glColor3f((GLfloat) 0.0f, (GLfloat) 0.0f, (GLfloat) 0.0f);

	double ancho = casillas[1] * ancho_casillas;
	double alto = casillas[0] * ancho_casillas;

	glLineWidth(1.0f);

	for (int i = 0; i <= casillas[1]; ++i) {
		glLineWidth((i == 0 || i == casillas[1]) ? (GLfloat) 3.0f : (GLfloat) 1.0f);
		glBegin(GL_LINES);
		glVertex3f((GLfloat) (i * ancho_casillas), (GLfloat) 0.0f , (GLfloat) 0.0f);
		glVertex3f((GLfloat) (i * ancho_casillas), (GLfloat) alto , (GLfloat) 0.0f);
		glEnd();
	}

	for (int i = 0; i <= casillas[0]; ++i) {
		glLineWidth((i == 0 || i == casillas[0]) ? (GLfloat) 3.0f : (GLfloat) 1.0f);
		glBegin(GL_LINES);
		glVertex3f((GLfloat)0.0f, (GLfloat) (i * ancho_casillas), (GLfloat)0.0f);
		glVertex3f((GLfloat)ancho, (GLfloat) (i * ancho_casillas), (GLfloat)0.0f);
		glEnd();
	}

	glLineWidth((GLfloat)1.0f);
}


void Tablero::DrawCell(int i, int j) {
	if ((i + j) % 2 == 0)
		glColor3f((GLfloat)0.82f, (GLfloat)0.71f, (GLfloat)0.55f); // Marron claro casi beige
	else
		glColor3f((GLfloat)0.40f, (GLfloat)0.26f, (GLfloat)0.13f); // Marron oscuro

	double x = j * ancho_casillas;
	double y = i * ancho_casillas;

	glBegin(GL_QUADS);
	glVertex2f((GLfloat) x, (GLfloat) y);
	glVertex2f((GLfloat) (x + ancho_casillas), (GLfloat) y);
	glVertex2f((GLfloat)(x + ancho_casillas), (GLfloat) (y + ancho_casillas));
	glVertex2f((GLfloat)x, (GLfloat) (y + ancho_casillas));
	glEnd();
}


bool Tablero::clicDentroTablero(float posX, float posY) {
	double ancho = casillas[1] * ancho_casillas;
	double alto = casillas[0] * ancho_casillas;

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
		double ancho = casillas[1] * ancho_casillas;  // El tablero mide 0.5x0.6
		double alto = casillas[0] * ancho_casillas;

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

Posicion Tablero::coor_to_casilla(float posX, float posY) {
	Posicion casilla{};
	casilla.col = int(posX / ancho_casillas);
	casilla.fil = int(posY / ancho_casillas);

	if (!casilla.esValida()) {
		std::cout << "Fuera del tablero";
		return casilla = { -1,-1 };
	}
	return casilla;
}


void Tablero::reshape(int width, int height) {
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Tamaño del tablero (con base en el número de casillas y el tamaño de cada una)
	float tableroAncho = (float)(casillas[1] * ancho_casillas);
	float tableroAlto = (float)(casillas[0] * ancho_casillas);

	// Márgenes en porcentaje (por ejemplo, un margen del 10%)
	float margen = 0.1f; // 10% de margen
	float worldAncho = tableroAncho * (1.0f + margen * 2.0f);
	float worldAlto = tableroAlto * (1.0f + margen * 2.0f);

	// Relación de aspecto de la ventana
	float aspectWin = (float)width / (float)height;
	float aspectWorld = worldAncho / worldAlto;

	// Variables para los límites de la vista
	float viewLeft, viewRight, viewBottom, viewTop;

	// Ajuste de la proyección en función de la relación de aspecto
	if (aspectWin > aspectWorld) {
		// La ventana es más ancha que el mundo -> ajustamos horizontalmente
		float visibleAncho = worldAlto * aspectWin;
		float offsetX = (visibleAncho - worldAncho) / 2.0f;
		viewLeft = -offsetX;
		viewRight = worldAncho + offsetX;
		viewBottom = 0.0f;
		viewTop = worldAlto;
	}
	else {
		// La ventana es más alta que el mundo -> ajustamos verticalmente
		float visibleAlto = worldAncho / aspectWin;
		float offsetY = (visibleAlto - worldAlto) / 2.0f;
		viewLeft = 0.0f;
		viewRight = worldAncho;
		viewBottom = -offsetY;
		viewTop = worldAlto + offsetY;
	}

	// Calculamos el centro de la ventana (esto es para ajustar el desplazamiento)
	float centerWindowX = (viewRight + viewLeft) / 2.0f;
	float centerWindowY = (viewTop + viewBottom) / 2.0f;

	dx = viewLeft + (viewRight - viewLeft - tableroAncho) / 2.0f;
	dy = viewBottom + (viewTop - viewBottom - tableroAlto) / 2.0f;

	// Ajustamos la proyección ortográfica para centrar el tablero en la pantalla
	//glOrtho(viewLeft, viewRight, viewBottom, viewTop, -1.0, 1.0);
	glOrtho(viewLeft - center_x - dx, viewRight - center_x - dx, viewBottom - center_y - dy, viewTop - center_y - dy, -1.0, 1.0);

	// Centramos el tablero usando glTranslatef
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Desplazamos el tablero al centro de la pantalla
	glTranslatef((GLfloat)(centerWindowX - center_x), (GLfloat) (centerWindowY - center_y), (GLfloat) 0.0f);

	// Aquí, el tablero se centra correctamente en la pantalla
}


void Tablero::DrawPiezas() {

	glEnable(GL_DEPTH_TEST); // Habilita el z-buffer
	if (!logica) return;     // No se dibuja si no hay logica

	auto piezas = logica->getPiezas();
	for (Pieza* p : piezas) {
		if (!p) continue;
		p->Dibuja(ancho_casillas); // Dibuja el sprite segun posicion
	}
}

void Tablero::DrawMovsValidos() {
	if (pieza_selec) {
		pieza_selec->DibujaMovValidos(ancho_casillas);
	}
}


void Tablero::DrawIndices() {
	

	ETSIDI::setTextColor(0, 0, 0); // Negro
	ETSIDI::setFont("fuentes/Bitwise.ttf", 12);

	glPushMatrix(); // Evita que el translate afecte a otras partes, guarda lo que ya hay
	
	glTranslatef(0.2f, -0.2f, 0.f); // Baja el texto debajo del tablero
	ETSIDI::printxy("a", 0.0f, 0.0f);
	ETSIDI::printxy("c", 1.0f, 0.0f);
	ETSIDI::printxy("e", 2.0f, 0.0f);
	glTranslatef(0.5f, 0.f, 0.f);
	ETSIDI::printxy("b", 0.0f, 0.0f);
	ETSIDI::printxy("d", 1.0f, 0.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.2f, 0.2f, 0.f);   //Afecta a todos los numeros
	ETSIDI::printxy("1", 0.0f, 0.0f);
	ETSIDI::printxy("3", 0.0f, 1.0f);
	ETSIDI::printxy("5", 0.0f, 2.0f);
	glTranslatef(0.f, 0.5f, 0.f);     //Afecta solo a los tres numeros de debajo se suma al otro glTranslatef
	ETSIDI::printxy("2", 0.0f, 0.0f);
	ETSIDI::printxy("4", 0.0f, 1.0f);
	ETSIDI::printxy("6", 0.0f, 2.0f);
	glPopMatrix();
}

void Tablero::DrawFinPartida(bool ganador, bool tablas) {
	if (tablas) {
		// Ancho y alto iniciales:
		float ancho = 9.0f; // valor arbitrario
		float alto = ancho * (1024.0f / 1536.0f); // mantener proporción de la imagen

		// Dibujo del fondo
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/Tablas_Ahogado.png").id);
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

	} else if (ganador) {
		// Ancho y alto iniciales:
		float ancho = 9.0f; // valor arbitrario
		float alto = ancho * (1024.0f / 1350.0f); // mantener proporción de la imagen

		// Dibujo del fondo
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/JAQUEMATE_Blancas_1.png").id);
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
	} else if (!ganador) {
		// Ancho y alto iniciales:
		float ancho = 9.0f; // valor arbitrario
		float alto = ancho * (1024.0f / 1408.0f); // mantener proporción de la imagen

		// Dibujo del fondo
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/JAQUEMATE_Negras_1.png").id);
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

