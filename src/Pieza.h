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
	virtual std::vector<Posicion> movimientosValidos(Tablero_logica& tab) = 0;

protected:                // El protected es como el private pero las clases que hereden de esta conservan las propiedades protected.
	const tipo_t tipo;						//Nombre para identificar a la pieza
	const Tablero& tablero;					//Referencia al tablero para que las piezas sepan en que tablero estan
	const bool color;						//True == Blancas <-> False == Negras
	const unsigned char valor;				//Valor de la pieza: Peón=>1, Caballo y alfil=> 3, Torre=>5 y Dama=>10.

	Posicion pos;
	Coords2D coords;
	ETSIDI::Sprite* sprite = nullptr; // sprite de la pieza
	std::vector<Posicion> movs_validos;  // La pieza almacena sus movimientos validos

public:
	Pieza() = default;
	Pieza(tipo_t tipo_, const Tablero& tablero_, bool color_, unsigned char valor_)
		: tipo(tipo_), tablero(tablero_), color(color_), valor(valor_) {}//Constructor para inicializar pieza con argumentos
	
	// Destructor para el new. Hace falta? si se hace slicing en el destructor, se destruye también lo generado en la clase derivada.
	/*~Pieza() {
		delete sprite;
	}*/
	void SetPos(int fil, int col);
	Posicion getPos() const { return pos; }
	Coords2D getCoords() const { return coords; }
	bool getColor() const { return color; }
	tipo_t getTipo() const { return tipo; }
	const Tablero& getTablero() const { return tablero; }


	bool esMovimientoLegalConJaque(Pieza* piezaDestino, Posicion destino, Tablero_logica& tab);
	bool estaEnJaque(Tablero_logica& tab) const;
	bool JaqueMate(Tablero_logica& tab) const;

	virtual void Dibuja(double ancho_casilla) const;
	void DibujaMovValidos(double ancho_casilla) const;

};
