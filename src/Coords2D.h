#pragma once
#include "Posicion.h"

constexpr const float ANCHO_CASILLAS = 0.5;

struct Coords2D {
	float x, y;


	Coords2D operator - (const Coords2D&) const;  //resta de Coordenadas
	Coords2D operator + (const Coords2D&) const; //suma de Coordenadas
	Coords2D operator *(float) const; // producto por un escalar

	Posicion coords_to_casilla() const{
		Posicion casilla{ };
		casilla.fil = int(y / ANCHO_CASILLAS) + 1;
		casilla.col = int(x / ANCHO_CASILLAS) + 1;

		if (!casilla.esValida()) return { -1,-1 }; // Cuando no esta dentro del tablero
		return casilla;
	}

	Coords2D(float coorX, float coorY): x{coorX} , y{coorY} {}
	Coords2D() = default;
};


//Posicion Coords2D::coords_to_pos() const {
//	int fil = y / (N_FIL * ANCHO_CASILLAS);
//	int col = x / (N_COL * ANCHO_CASILLAS);
//	return Posicion(fil,col);
//}



inline Coords2D Coords2D::operator - (const Coords2D& v) const {
	return { x - v.x , y - v.y };
}

inline Coords2D Coords2D::operator + (const Coords2D& v) const {
	return { x + v.x , y + v.y };
}

inline Coords2D Coords2D::operator *(float real) const {
	return { x * real, y * real };
}

