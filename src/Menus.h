#pragma once
enum tipo_menu {MENU_PPAL, MENU_MODO, JUEGO};
enum  rivalidad { RIV_NULA, J_VS_J, J_VS_IA };
enum  modo { MODO_NULO, PETTY, OPUESTAS };

class Menus
{
	bool J_vs_J{}, J_vs_IA{};  // si vale 0: Jugador vs Jugador y si vale 1; Jugador vs IA
	float dimX, dimY; // Dimensiones de la imagen
	tipo_menu menu{};
	modo modo_juego{};
	rivalidad riv{};
public:
	void Inicializa();
	void Draw();
	void Reshape(int width, int height);
	void set_menu(tipo_menu men) { menu = men; }
	tipo_menu get_menu() { return menu; }
	void set_modo(modo mod) { modo_juego = mod; }
	modo get_modo() { return modo_juego; }
	void set_riv(rivalidad rival) { riv = rival; }
	rivalidad get_riv() { return riv; }
};


