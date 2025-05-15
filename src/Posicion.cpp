#include "Posicion.h"
#include "Coords2D.h"

Coords2D Posicion::centro_en_coords() {
	 float coorX = float(col - 0.5) * TAM_CASILLA;
	 float coorY = float(fil - 0.5) * TAM_CASILLA;
	 return { coorX, coorY };
	}