#pragma once
#include "Tablero.h"
#include "Menus.h"
#include "Tablero_logica.h"
#include "Posicion.h"
#include"IA.h"



class Mundo
{
	Tablero tablero;
	Menus menus;
	Tablero_logica logica;
	bool modoia=1; //==1 si es dificil
	IA ia;
	
public:
	
	void clicPos(int button, int state, int x, int y);
	void Draw();
	void Inicializa(); 
	void Reshape(int width, int height);
	void OnKeyboardDown(unsigned char key);

	Coords2D coorClics_to_cords2D(int x, int y);

};

