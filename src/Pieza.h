#pragma once
#include "Tablero.h"



class Pieza
{
public:
	enum class tipo_t { PEON, CABALLO, ALFIL, TORRE, DAMA, REY, NULA };

protected:                // El protected es como el private pero las clases que hereden de esta conservan las propiedades protected.
	const tipo_t tipo;						//Nombre para identificar a la pieza
	const Tablero& tablero;					//Referencia al tablero para que las piezas sepan en que tablero estan
	const bool color;						//True == Blancas <-> False == Negras
	const unsigned char valor;				//Valor de la pieza: Peón=>1, Caballo y alfil=> 3, Torre=>5 y Dama=>10.
};

