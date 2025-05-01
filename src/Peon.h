#pragma once
#include "Pieza.h"
#include <vector>
#include "Tablero_logica.h"

using namespace std;
class Tablero_logica;
class Peon : public Pieza {
public:
    Peon(const Tablero& t, bool color)
        : Pieza(tipo_t::PEON, t, color, 1) {}//Constructor con herencia de Pieza para un tablero y color constante

    vector <Posicion> movimientosValidos(Tablero_logica &tab) const;

};




