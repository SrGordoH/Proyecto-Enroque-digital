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
	friend class Mundo;

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
	bool turno = true;              //Turno vale 1 cuandole toca a blancas
	bool finPartida = false;
	bool ganador;   // True cuando gana blancas y false cuando gana negras

public:
	void inicializarTablero();
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
	void eliminarPieza(Pieza* p);
	void cambiarTurno() { turno = !turno; }
	bool moverPieza(Pieza* pieza, Posicion destino);
	void printHistorial() const;
	


	~Tablero_logica() {
		for (auto p : piezas) delete p;
	}

};