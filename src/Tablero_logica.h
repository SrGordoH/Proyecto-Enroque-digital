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
	struct Movimiento {
		Pieza* pieza;
		Posicion origen;
		Posicion destino;
		Pieza* capturada;
	};
	std::vector<Movimiento> historial;
	int movimientosSinCaptura = 0;


public:
	void inicializarTablero(const Tablero& tablero);
	void setearPosicionesIniciales(int modo);
	Pieza* obtenerPieza(Posicion casilla) const;
	Posicion obtenerReyPos(bool color);
	vector<Pieza*> obtenerPiezasOponente(bool color) const;
	const vector<Pieza*>& getPiezas() const { return piezas; }
	bool estaEnJaqueMate(bool color);
	bool estaEnJaque(bool color);
	void guardarMovimiento(Pieza* p, Posicion origen, Posicion destino, Pieza* capturada);
	void deshacerUltimoMovimiento();
	void verificarCoronacion();
	bool esTablasPorAhogo(bool turnoColor);
	void notificarMovimiento(Pieza* piezaMovida, Pieza* capturada);
	bool reglaCincuentaMovimientos() const {return movimientosSinCaptura >= 50;}



	~Tablero_logica() {
		for (auto p : piezas) delete p;
	}

};