#pragma once

struct Coords2D;

constexpr int COLUMNAS = 5;
constexpr int FILAS = 6;
constexpr float TAM_CASILLA = 0.5;

// Clase para gestionar las posiciones del tablero
struct Posicion
{
	int fil, col; //filas y columnas, en nuestro caso 5x6

	bool esValida() const {
		return fil > 0 && fil <= FILAS && col > 0 && col <= COLUMNAS;  //devuelve true si está en el tablero
	}

	int indice() const {
		return (fil - 1) + COLUMNAS * (col - 1);  // devuelve un indice, siendo el indice 0 la casilla (1,1) y el indice 29 la casilla (5,6)
	}

	// Función que devuelve el centro de la posición en coordenadas de la pantalla/raton
	Coords2D centro_en_coords();

	Posicion(int f, int c): fil{f}, col{c} {}
	Posicion() = default;

};