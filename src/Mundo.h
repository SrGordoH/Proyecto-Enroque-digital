#pragma once
#include "Tablero.h"
#include "Menus.h"


class Mundo
{
	Tablero tablero;
	Menus menus;
	enum class rivalidad { J_VS_J, J_VS_IA, NULO };
	enum class modo {PETTY, OPUESTAS, NULO};
public:
	void clicPos(int button, int state, int x, int y);
	void displayMenuPrincipal();
	void displayMenuModo();
	void Inicializa(); 
	void Reshape(int width, int height);

};

