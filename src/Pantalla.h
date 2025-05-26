#pragma once
#include "Boton.h"
#include "ETSIDI.h"
#include "freeglut.h"
#include <string>

class Pantalla {
	Boton boton1, boton2, boton_salida;
	std::string ruta_pantalla;
	float dimX, dimY;
	
public:

	void inicializaMenu(int tipo);
	void dibujaPantalla();
	bool clic_b1(float posX, float posY) { return boton1.clic(posX, posY); }
	bool clic_b2(float posX, float posY) { return boton2.clic(posX, posY); }
	bool clic_sal(float posX, float posY) { return boton_salida.clic(posX, posY); }
};