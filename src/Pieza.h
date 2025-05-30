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

protected:                // El protected es como el private pero las clases que hereden de esta conservan las propiedades protected.
	const tipo_t tipo;						//Nombre para identificar a la pieza
	const bool color;						//True == Blancas <-> False == Negras
	const unsigned char valor;				//Valor de la pieza: Peón=>1, Caballo y alfil=> 3, Torre=>5 y Dama=>10.

	Posicion pos;
	Coords2D coords;
	ETSIDI::Sprite* sprite = nullptr; // sprite de la pieza
	std::vector<Posicion> movs_validos;  // La pieza almacena sus movimientos validos

public:
	Pieza(tipo_t tipo_, bool color_, unsigned char valor_)
		: tipo(tipo_), color(color_), valor(valor_) {}//Constructor para inicializar pieza con argumentos
	
	virtual ~Pieza() {
		delete sprite;
	}
	void SetPos(int fil, int col);
	Posicion getPos() const { return pos; }
	Coords2D getCoords() const { return coords; }
	bool getColor() const { return color; }
	tipo_t getTipo() const { return tipo; }
	std::string nombrePieza(Pieza::tipo_t tipo) const;
	virtual std::vector<Posicion> movimientosValidos(Tablero_logica& tab, bool evitarJaque = true) = 0;


	virtual Pieza* clonar() const =0;

	bool esMovimientoLegalConJaque(Pieza* piezaDestino, Posicion destino, Tablero_logica& tab);
	bool estaEnJaque(Tablero_logica& tab) const;

	virtual void Dibuja(double ancho_casilla) const;
	void DibujaMovValidos(double ancho_casilla) const;

};
