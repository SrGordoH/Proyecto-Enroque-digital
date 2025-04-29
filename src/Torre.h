#pragma once
#include "Pieza.h"

class Torre : public Pieza {
public:
    Torre(const Tablero& t, bool color)
        : Pieza(tipo_t::TORRE, t, color, 5) {}//Constructor con herencia de Pieza para un tablero y color constante
};

