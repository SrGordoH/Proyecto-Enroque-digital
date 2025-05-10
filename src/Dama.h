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
        : Pieza(tipo_t::DAMA, t, color, 10) {
        if (color)
            sprite = new ETSIDI::Sprite("imagenes/Chess_qlt60.png"); // dama blanca
        else
            sprite = new ETSIDI::Sprite("imagenes/Chess_qdt60.png"); // dama negra
    }

    vector <Posicion> movimientosValidos(Tablero_logica& tab) const;

};

