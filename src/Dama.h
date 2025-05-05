#pragma once
#include "Pieza.h"
#pragma once
#include "Tablero_logica.h"
#include <vector>
using namespace std;
class Tablero_logica;


class Dama : public Pieza {
public:
    Dama(const Tablero& t, bool color)
        : Pieza(tipo_t::DAMA, t, color, 10) {}//Constructor con herencia de Pieza para un tablero y color constante

    vector <Posicion> movimientosValidos(Tablero_logica& tab) const;

};

