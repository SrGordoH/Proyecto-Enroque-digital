#include "tablero.h"
#include "Pieza.h"
#include "Tablero_logica.h"

#include "freeglut.h"
#include <iostream>  // Impresi�n por pantalla para hacer pruebas y debugs

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

	glClearColor(1, 1, 1, 1); // fondo blanco
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_LIGHTING); // Si solo hay colores planos, no hace falta luz

	// Dibuja la cuadr�cula y las piezas
	DrawGrid();
	for (int i = 0; i < casillas[0]; i++) {
		for (int j = 0; j < casillas[1]; j++) {
			DrawCell(i, j);
		}
	}
	DrawPiezas();
}

void Tablero::DrawGrid() {
	glColor3f(0.0f, 0.0f, 0.0f);

	float ancho = casillas[1] * ancho_casillas;
	float alto = casillas[0] * ancho_casillas;

	glLineWidth(1.0f);

	for (int i = 0; i <= casillas[1]; ++i) {
		glLineWidth((i == 0 || i == casillas[1]) ? 3.0f : 1.0f);
		glBegin(GL_LINES);
		glVertex3f(i * ancho_casillas + dx, dy, 0.0f);
		glVertex3f(i * ancho_casillas + dx, alto + dy, 0.0f);
		glEnd();
	}

	for (int i = 0; i <= casillas[0]; ++i) {
		glLineWidth((i == 0 || i == casillas[0]) ? 3.0f : 1.0f);
		glBegin(GL_LINES);
		glVertex3f(dx, i * ancho_casillas + dy, 0.0f);
		glVertex3f(ancho + dx, i * ancho_casillas + dy, 0.0f);
		glEnd();
	}

	glLineWidth(1.0f);
}


void Tablero::DrawCell(int i, int j) {
	if ((i + j) % 2 == 0)
		glColor3f(0.0f, 1.0f, 0.0f); // Verde claro
	else
		glColor3f(0.0f, 0.5f, 0.0f); // Verde oscuro

	float x = j * ancho_casillas + dx;
	float y = i * ancho_casillas + dy;

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
		gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ); // Conversi�n coordenadas de la pantalla a coordenadas del mundo

		// Mostrar coordenadas en consola
		std::cout << "Clic 2D en: (" << posX << ", " << posY << ")\n"; // La coordenada 0,0 es la esquina inferior izquierda del tablero

		// Comprobaci�n de si est� dentro del tablero
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


void Tablero::reshape(int width, int height) {
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Tama�o del tablero
	float tableroAncho = casillas[1] * ancho_casillas;
	float tableroAlto = casillas[0] * ancho_casillas;

	// M�rgenes en porcentaje
	float margen = 0.1f; // 10% de margen
	float worldAncho = tableroAncho * (1.0f + margen * 2.0f);
	float worldAlto = tableroAlto * (1.0f + margen * 2.0f);

	// Relaci�n de aspecto
	float aspectWin = (float)width / (float)height;
	float aspectWorld = worldAncho / worldAlto;

	float viewLeft, viewRight, viewBottom, viewTop;

	if (aspectWin > aspectWorld) {
		// La ventana es m�s ancha -> ajustamos horizontalmente
		float visibleAncho = worldAlto * aspectWin;
		float offsetX = (visibleAncho - worldAncho) / 2.0f;
		viewLeft = -offsetX;
		viewRight = worldAncho + offsetX;
		viewBottom = 0.0f;
		viewTop = worldAlto;
	}
	else {
		// La ventana es m�s alta -> ajustamos verticalmente
		float visibleAlto = worldAncho / aspectWin;
		float offsetY = (visibleAlto - worldAlto) / 2.0f;
		viewLeft = 0.0f;
		viewRight = worldAncho;
		viewBottom = -offsetY;
		viewTop = worldAlto + offsetY;
	}

	dx = viewLeft + (viewRight - viewLeft - tableroAncho) / 2.0f;
	dy = viewBottom + (viewTop - viewBottom - tableroAlto) / 2.0f;


	//Centramos tablero en ambos casos
	glOrtho(viewLeft, viewRight, viewBottom, viewTop, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Tablero::DrawPiezas() {
	glEnable(GL_DEPTH_TEST);
	if (logica == nullptr) {
		std::cout << "logica es nullptr" << std::endl;
		return;
	}
	if (logica != nullptr) {
		auto piezas = logica->getPiezas();
		std::cout << "N�mero de piezas: " << piezas.size() << std::endl;

		for (Pieza* p : piezas) {
			if (!p) continue;

			Posicion pos = p->getPos();
			float x = pos.col * ancho_casillas + ancho_casillas / 2.0f + dx;
			float y = pos.fil * ancho_casillas + ancho_casillas / 2.0f + dy;
			float r = ancho_casillas / 3.0f;
			float z = 0.01f;  // Altura m�nima para que la pieza se vea sobre el tablero
			std::cout << "Pieza en fila " << pos.fil << ", col " << pos.col << std::endl;

			// Color seg�n el jugador
			if (p->getColor())
				glColor3f(1.0f, 0.0f, 0.0f);  // Rojo para test
			else
				glColor3f(1.0f, 0.0f, 0.0f);  // Rojo para test

			switch (p->getTipo()) {
			case Pieza::tipo_t::PEON:
				glBegin(GL_TRIANGLE_FAN);  // Pe�n: c�rculo
				for (int i = 0; i <= 20; ++i) {
					float theta = 2.0f * 3.14159f * float(i) / 20.0f;
					glVertex3f(x + r * cosf(theta), y + r * sinf(theta), z);
				}
				glEnd();
				break;
			case Pieza::tipo_t::TORRE:
				glBegin(GL_QUADS);  // Torre: cuadrado
				glVertex3f(x - r, y - r, z);
				glVertex3f(x + r, y - r, z);
				glVertex3f(x + r, y + r, z);
				glVertex3f(x - r, y + r, z);
				glEnd();
				break;
			case Pieza::tipo_t::CABALLO:
				glBegin(GL_POLYGON);  // Caballo: rombo
				glVertex3f(x, y + r, z);
				glVertex3f(x + r, y, z);
				glVertex3f(x, y - r, z);
				glVertex3f(x - r, y, z);
				glEnd();
				break;
			case Pieza::tipo_t::ALFIL:
				glBegin(GL_TRIANGLES);  // Alfil: tri�ngulo
				glVertex3f(x, y + r, z);
				glVertex3f(x - r, y - r, z);
				glVertex3f(x + r, y - r, z);
				glEnd();
				break;
			case Pieza::tipo_t::DAMA:
				glBegin(GL_POLYGON);  // Dama: hex�gono
				for (int i = 0; i < 6; ++i) {
					float angle = i * 2.0f * 3.14159f / 6;
					glVertex3f(x + r * cos(angle), y + r * sin(angle), z);
				}
				glEnd();
				break;
			case Pieza::tipo_t::REY:
				glBegin(GL_LINES);  // Rey: cruz
				glVertex3f(x - r, y, z);
				glVertex3f(x + r, y, z);
				glVertex3f(x, y - r, z);
				glVertex3f(x, y + r, z);
				glEnd();
				break;
			}
		}
		std::cout << "Piezas dibujadas\n";
	}
}

