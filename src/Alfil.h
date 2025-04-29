#pragma once
#include "Pieza.h"

class Alfil : public Pieza {

public:
    Alfil(const Tablero& t, bool color)
        : Pieza(tipo_t::ALFIL, t, color, 3) {}//Constructor con herencia de Pieza para un tablero y color constante

};

