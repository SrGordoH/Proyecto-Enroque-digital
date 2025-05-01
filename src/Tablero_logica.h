#pragma once
#include <vector>
#include "Peon.h"
#include "Torre.h"
#include "Caballo.h"
#include "Alfil.h"
#include "Dama.h"
#include "Rey.h"
#include "Pieza.h"
#include "Piezas.h"
#include "tablero.h"



class Tablero_logica {
	Tablero tablero;
	Piezas piezas(tablero); 
public:
	void inicializarTablero(const Tablero& tablero);

};