#pragma once
#include "Boton.h"
#include "Pantalla.h"


enum tipo_menu { MENU_PPAL, MENU_MODO, MENU_IA, JUEGO};
enum  rivalidad { RIV_NULA, J_VS_J, J_VS_IA };
enum  modo { PETTY, OPUESTAS, MODO_NULO };
enum dificultad {FACIL, DIFICIL, DIF_NULA};


class Menus
{
	bool J_vs_J{}, J_vs_IA{};  // si vale 0: Jugador vs Jugador y si vale 1; Jugador vs IA
	tipo_menu t_menu{};
	modo modo_juego{};
	rivalidad riv{};
	dificultad modo_dif{};

	friend class Mundo;

public:
	Pantalla pant_menu;
	
	void Draw();
	void Reshape(int width, int height);
	void set_menu(tipo_menu men) { t_menu = men; }
	tipo_menu get_menu() { return t_menu; }
	void set_modo(modo mod) { modo_juego = mod; }
	modo get_modo() { return modo_juego; }
	void set_riv(rivalidad rival) { riv = rival; }
	rivalidad get_riv() { return riv; }
	void coor_menus(float posX, float posY);
	dificultad get_dificultad() { return modo_dif; }
	void set_dif(dificultad dificultad) {modo_dif = dificultad; }
};


