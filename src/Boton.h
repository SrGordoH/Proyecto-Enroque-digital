#pragma once


struct Boton {
	float lim_i;  // limite izquierdo
	float lim_d;  // limite derecho
	float lim_bajo;  // limite bajo
	float lim_alto;  // limit alto

	bool clic(float posX, float posY);  // devulelve true si se ha hecho clic en el botón

};

inline bool Boton::clic(float posX, float posY) {
	return posX >= lim_i && posX <= lim_d && posY >= lim_bajo && posY <= lim_alto;
}
