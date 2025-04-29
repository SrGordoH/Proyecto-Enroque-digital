#pragma once
#include "Pieza.h"

class Dama : public Pieza {
public:
    Dama(const Tablero& t, bool color)
        : Pieza(tipo_t::DAMA, t, color, 10) {}//Constructor con herencia de Pieza para un tablero y color constante
};

