#pragma once
#include "freeglut.h"
#include "ETSIDI.h"
#include "Posicion.h"
#include <string>
using std::string;


class ModeloPieza {
	ETSIDI::Sprite* sprite;
	Posicion pos;
	string ruta_imagen;
	float tamano;
	bool color;
public:
	void inicializa();
	void draw();

};