#pragma once
#include "Tablero.h"
#include "Menus.h"



class Mundo
{
	Tablero tablero;
	Menus menus;
	
public:
	
	void clicPos(int button, int state, int x, int y);
	void Draw();
	void Inicializa(); 
	void Reshape(int width, int height);

};

