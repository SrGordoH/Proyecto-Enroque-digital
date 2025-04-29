#pragma once
#include "Pieza.h"

class Caballo : public Pieza {
public:
    Caballo(const Tablero& t, bool color)
        : Pieza(tipo_t::CABALLO, t, color, 3) {}//Constructor con herencia de Pieza para un tablero y color constante
};

