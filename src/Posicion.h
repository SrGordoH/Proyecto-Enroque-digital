#pragma once

constexpr int COLUMNAS = 5;
constexpr int FILAS = 6;


// Clase para gestionar las posiciones del tablero
struct Posicion
{
	int fil, col; //filas y columnas, en nuestro caso 5x6

	inline bool esValida() const {
		return fil > 0 && fil <= 5 && col > 0 && col <= 6;  //devuelve true si está en el tablero
	}

	inline int indice() const {
		return (fil - 1) + COLUMNAS * (col - 1);  // devuelve un indice, siendo el indice 0 la casilla (1,1) y el indice 29 la casilla (5,6)
	}

};