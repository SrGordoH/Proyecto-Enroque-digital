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
	double center_x{ }, center_y{}, dist{}, ancho_casillas{};
	int casillas[2]; //casillas: filas x columnas
	float dx{}, dy{};
	bool turno = 1;              //Turno vale 1 cuandole toca a blancas
	Pieza* pieza_selec = nullptr;
	bool sonidoFinReproducido = false;
	//Pantallas finales:
	ETSIDI::Sprite victoriaBlancas;  //Las nuevas imagenes las voy a considerar objetos con el Sprite
	ETSIDI::Sprite victoriaNegras;
	ETSIDI::Sprite tablasSprite;

public: 
	void Inicializa();
	void Draw();
    void DrawGrid();
	void DrawIndices();
	void DrawTurno();
	void DrawCell(int i, int j);
	bool clicDentroTablero(float ogl_x, float ogl_y);
	void clicPos(int button, int state, int x, int y);
	void reshape(int width, int heigth);
	void reshapePantallaFin(int width, int height);
	void setLogica(Tablero_logica* log) { logica = log;    std::cout << "Logica asignada\n";}
	void DrawPiezas();
	void DrawMovsValidos();
	void DrawFinPartida(bool ganador, bool tablas);
	double get_anchocas() const { return ancho_casillas; }
	Pieza* get_pieza_selec() const { return pieza_selec; }
	void set_pieza_selec(Pieza* p) { pieza_selec = p; }
	Posicion coor_to_casilla(float posX, float posY);


	Tablero(); //Declaro el constructor carga de sprites
	
	
};
