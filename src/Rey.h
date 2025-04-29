#pragma once
#include "Pieza.h"

class Rey : public Pieza {
public:
    Rey(const Tablero& t, bool color)
        : Pieza(tipo_t::REY, t, color, 0) {}//Constructor con herencia de Pieza para un tablero y color constante
};

