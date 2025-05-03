#pragma once
#include "Pieza.h"
#include "Tablero_logica.h"
#include <vector>
using namespace std;
class Tablero_logica;


class Alfil : public Pieza {

public:
    Alfil(const Tablero& t, bool color)
        : Pieza(tipo_t::ALFIL, t, color, 3) {}//Constructor con herencia de Pieza para un tablero y color constante

    vector <Posicion> movimientosValidos(Tablero_logica& tab) const;

};

