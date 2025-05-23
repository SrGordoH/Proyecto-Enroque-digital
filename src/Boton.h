#pragma once


struct Boton {
	float lim_i;  // limite izquierdo
	float lim_d;  // limite derecho
	float lim_bajo;  // limite bajo
	float lim_alto;  // limit alto

	bool clic(float posX, float posY);  // devulelve true si se ha hecho clic en el botón

};

