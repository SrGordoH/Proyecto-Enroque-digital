#pragma once
#include "Pieza.h"
#include "Tablero_logica.h"
#include <vector>
using namespace std;
class Tablero_logica;

class Rey : public Pieza {
public:
    Rey(const Tablero& t, bool color)
        : Pieza(tipo_t::REY, t, color, 0) {
        if (color)
            sprite = new ETSIDI::Sprite("imagenes/Chess_klt60.png"); // rey blanco
        else
            sprite = new ETSIDI::Sprite("imagenes/Chess_kdt60.png"); // rey negro
    }

    vector <Posicion> movimientosValidos(Tablero_logica& tab);

};

