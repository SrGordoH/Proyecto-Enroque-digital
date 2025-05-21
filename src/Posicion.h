#pragma once
#include <string>
#include <iostream>

struct Coords2D;

constexpr int COLUMNAS = 5;
constexpr int FILAS = 6;
constexpr float TAM_CASILLA = 0.5;

// Clase para gestionar las posiciones del tablero
struct Posicion
{
	int fil, col; //filas y columnas, en nuestro caso 5 columnas y 6 filas

	bool esValida() const {
		return fil > 0 && fil <= FILAS && col > 0 && col <= COLUMNAS;  //devuelve true si está en el tablero
	}

	int indice() const {
		return (fil - 1) + COLUMNAS * (col - 1);  // devuelve un indice, siendo el indice 0 la casilla (1,1) y el indice 29 la casilla (5,6)
	}

	// Función que devuelve el centro de la posición en coordenadas de la pantalla/raton
	Coords2D centro_en_coords() const;
	// Dado un string te devuelve la posición. Ej: b3 es la fila 3 columna 2
	Posicion notacionToPosicion(const std::string& casilla);

	Posicion(int f, int c): fil{f}, col{c} {}
	Posicion() = default;

};


struct Coords2D {
	float x, y;


	Coords2D operator - (const Coords2D&) const;  //resta de Coordenadas
	Coords2D operator + (const Coords2D&) const; //suma de Coordenadas
	Coords2D operator *(float) const; // producto por un escalar

	Posicion coords_to_casilla() const {
		Posicion casilla{ };
		casilla.fil = int(y / TAM_CASILLA) + 1;
		casilla.col = int(x / TAM_CASILLA) + 1;

		if (!casilla.esValida()) return { -1,-1 }; // Cuando no esta dentro del tablero
		return casilla;
	}

	Coords2D(float coorX, float coorY) : x{ coorX }, y{ coorY } {}
	Coords2D() = default;
};




inline Coords2D Coords2D::operator - (const Coords2D& v) const {
	return { x - v.x , y - v.y };
}

inline Coords2D Coords2D::operator + (const Coords2D& v) const {
	return { x + v.x , y + v.y };
}

inline Coords2D Coords2D::operator *(float real) const {
	return { x * real, y * real };
}