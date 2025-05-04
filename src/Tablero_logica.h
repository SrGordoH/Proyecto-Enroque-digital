#pragma once
#include <vector>
#include "Peon.h"
#include "Torre.h"
#include "Caballo.h"
#include "Alfil.h"
#include "Dama.h"
#include "Rey.h"
#include "Pieza.h"

class Tablero_logica {
	std::vector<Pieza*> piezas;  //vector de punteros a piezas para almacenar piezas
	bool modo;                   //TRUE para petty FALSE para reyes esquinas opuestas

public:
	void inicializarTablero(const Tablero& tablero);
	void setearPosicionesIniciales(int modo);
	Pieza* obtenerPieza(int fil, int col) const;
	Posicion obtenerReyPos(bool color);
	vector<Pieza*> obtenerPiezasOponente(bool color) const;


};