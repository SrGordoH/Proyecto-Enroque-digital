#pragma once
#include "Peon.h"
#include "Torre.h"
#include "Caballo.h"
#include "Alfil.h"
#include "Dama.h"
#include "Rey.h"
#include "Pieza.h"
#include "tablero.h"


class Piezas
{
	Peon peonesblancos[5];
	Peon peonesnegros[5];
	Rey reyblanco;
	Rey reynegro;
	Dama damablanca;
	Dama damanegra;
	Torre torreblanca;
	Torre torrenegra;
	Alfil alfilblanco;
	Alfil alfilnegro;
	Caballo caballoblanco;
	Caballo caballonegro;

	Piezas(const Tablero& tablero)
		: peonesblancos{
			Peon(tablero, true),
			Peon(tablero, true),
			Peon(tablero, true),
			Peon(tablero, true),
			Peon(tablero, true)
		},
		peonesnegros{
		  Peon(tablero, false),
		  Peon(tablero, false),
		  Peon(tablero, false),
		  Peon(tablero, false),
		  Peon(tablero, false)
		},
		reyblanco(tablero, true),
		reynegro(tablero, false),
		damablanca(tablero, true),
		damanegra(tablero, false),
		torreblanca(tablero, true),
		torrenegra(tablero, false),
		alfilblanco(tablero, true),
		alfilnegro(tablero, false),
		caballoblanco(tablero, true),
		caballonegro(tablero, false)
	{
	}
		
	

};

