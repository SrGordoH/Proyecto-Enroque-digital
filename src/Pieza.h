#pragma once
#include "Tablero.h"
#include "Posicion.h"


class Pieza
{
public:
	enum class tipo_t { PEON, CABALLO, ALFIL, TORRE, DAMA, REY, NULA };

protected:                // El protected es como el private pero las clases que hereden de esta conservan las propiedades protected.
	const tipo_t tipo;						//Nombre para identificar a la pieza
	const Tablero& tablero;					//Referencia al tablero para que las piezas sepan en que tablero estan
	const bool color;						//True == Blancas <-> False == Negras
	const unsigned char valor;				//Valor de la pieza: Peón=>1, Caballo y alfil=> 3, Torre=>5 y Dama=>10.
	
	Posicion pos;	


public:
	Pieza() = default;
	Pieza(tipo_t tipo_, const Tablero& tablero_, bool color_, unsigned char valor_)
		: tipo(tipo_), tablero(tablero_), color(color_), valor(valor_) {}      //Constructor para inicializar pieza con argumentos
	void SetPos(int fil, int col);
	
};

