#include "Posicion.h"


Coords2D Posicion::centro_en_coords() const {
	 float coorX = float(col - 0.5) * TAM_CASILLA;
	 float coorY = float(fil - 0.5) * TAM_CASILLA;
	 return { coorX, coorY };
}

Coords2D Posicion::esquinainf_en_coords() const {
	float coorX = float(col - 1) * TAM_CASILLA;
	float coorY = float(fil - 1) * TAM_CASILLA;
	return { coorX, coorY };
}

Posicion Posicion::notacionToPosicion(const std::string& casilla) {
	if (casilla.length() != 2 || !isalpha(casilla[0]) || !isdigit(casilla[1])) {
		std::cout << "Formato inválido." << std::endl;
		return {-1, -1};
	}

	char columnaChar = tolower(casilla[0]); // Convertimos a minúscula por si es mayúscula
	int fila = casilla[1] - '0'; // '3' -> 3
	int columna = columnaChar - 'a' + 1; // 'a' -> 1, 'b' -> 2, etc.

	if (columna < 1 || columna > 5 || fila < 1 || fila > 6) {
		std::cout << "Fila o columna fuera del rango del tablero." << std::endl;
		return { -1, -1 };
	}

	std::cout << "Fila: " << fila << "  Columna: " << columna << std::endl;

	return { fila, columna };
}

Posicion Posicion::operator - (const Posicion& v) const {
	return { col - v.col , fil - v.fil };
}

Posicion Posicion::operator + (const Posicion& v) const {
	return { col + v.col , fil + v.fil };
}

