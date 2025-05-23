#include "Boton.h"

bool Boton::clic(float posX, float posY) {
	return posX >= lim_i && posX <= lim_d && posY >= lim_bajo && posY <= lim_alto;
}