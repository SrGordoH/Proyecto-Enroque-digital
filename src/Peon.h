#pragma once
#include "Pieza.h"

class Peon : public Pieza {
public:
    Peon(const Tablero& t, bool color)
        : Pieza(tipo_t::PEON, t, color, 1) {}//Constructor con herencia de Pieza para un tablero y color constante
};


