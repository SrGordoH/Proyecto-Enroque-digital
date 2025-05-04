#pragma once
enum tipo_menu {MENU_PPAL, MENU_MODO};

class Menus
{
	bool J_vs_J{}, J_vs_IA{};  // si vale 0: Jugador vs Jugador y si vale 1; Jugador vs IA
	float dimX, dimY; // Dimensiones de la imagen
	tipo_menu menu{};
public:
	void Inicializa();
	void Draw();
	void Reshape(int width, int height);
};


