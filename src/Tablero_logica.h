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


public:
	void inicializarTablero(const Tablero& tablero);

};