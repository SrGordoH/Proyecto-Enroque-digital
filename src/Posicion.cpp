#include "Posicion.h"

Coords2D Posicion::centro_en_coords() const {
	 float coorX = float(col - 0.5) * TAM_CASILLA;
	 float coorY = float(fil - 0.5) * TAM_CASILLA;
	 return { coorX, coorY };
	}