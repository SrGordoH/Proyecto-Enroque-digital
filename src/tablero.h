#pragma once
#include "Posicion.h"
#include "ETSIDI.h"
#include <iostream>

constexpr const int NUM_FILAS = 6;
constexpr const int NUM_COLUMNAS = 5;
constexpr const double DIST_PANTALLA = 1;
constexpr const double ANCHO_LARGO_CASILLAS = 0.5;

class Tablero_logica;
class Pieza;


class Tablero
{
	friend class Mundo;
	Tablero_logica* logica = nullptr;

public: 
	double center_x{ }, center_y{}, dist{}, ancho_casillas{};
	int casillas[2]; //casillas: filas x columnas
	float dx, dy;
	void Inicializa();
	void Draw();
    void DrawGrid();
	void DrawCell(int i, int j);
	bool clicDentroTablero(float ogl_x, float ogl_y);
	void clicPos(int button, int state, int x, int y);
	void reshape(int width, int heigth);
	void setLogica(Tablero_logica* log) { logica = log;    std::cout << "Logica asignada\n";}
	void DrawPiezas();

};
