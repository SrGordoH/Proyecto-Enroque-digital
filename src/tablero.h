#pragma once
#include "Posicion.h"

class Tablero
{
public: 
	double center_x{ }, center_y{}, dist{1}, ancho_casillas{0.1};
	int casillas[2]{ 6,5 }; //casillas: filas x columnas
	void Draw();
    void DrawGrid();
	void DrawCell(int i, int j);
	bool clicDentroTablero(float ogl_x, float ogl_y);
	void clicPos(int button, int state, int x, int y);
	//Constructor:
	Tablero(int filas, int columnas, double anchoCasillas, double centroX=0, double centroY=0)
		: ancho_casillas(anchoCasillas), center_x(centroX), center_y(centroY) {
		casillas[0] = filas;
		casillas[1] = columnas;
	}
	Tablero() = default;
};
