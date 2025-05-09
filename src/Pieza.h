#pragma once
#include "Tablero.h"
#include "Posicion.h"
#include <vector>
#include "ETSIDI.h"

class Tablero_logica;


class Pieza
{
public:
	enum class tipo_t { PEON, CABALLO, ALFIL, TORRE, DAMA, REY, NULA };
	virtual std::vector<Posicion> movimientosValidos(Tablero_logica& tab) const = 0;

protected:                // El protected es como el private pero las clases que hereden de esta conservan las propiedades protected.
	const tipo_t tipo;						//Nombre para identificar a la pieza
	const Tablero& tablero;					//Referencia al tablero para que las piezas sepan en que tablero estan
	const bool color;						//True == Blancas <-> False == Negras
	const unsigned char valor;				//Valor de la pieza: Pe�n=>1, Caballo y alfil=> 3, Torre=>5 y Dama=>10.

	Posicion pos;
	ETSIDI::Sprite* sprite = nullptr; // sprite de la pieza


public:
	Pieza() = default;
	Pieza(tipo_t tipo_, const Tablero& tablero_, bool color_, unsigned char valor_)
		: tipo(tipo_), tablero(tablero_), color(color_), valor(valor_) {
	}      //Constructor para inicializar pieza con argumentos

	void SetPos(int fil, int col);
	Posicion getPos() const { return pos; }
	bool getColor() const { return color; }
	tipo_t getTipo() const { return tipo; }

	bool esMovimientoLegalConJaque(Pieza* piezaDestino, Posicion destino, Tablero_logica& tab);
	bool estaEnJaque(Tablero_logica& tab) const;
	bool JaqueMate(Tablero_logica& tab) const;

	virtual void Dibuja(float ancho_casilla, float dx, float dy) const;
};
