#pragma once
#include "Pieza.h"
#include "Tablero_logica.h"
#include <vector>
using namespace std;
class Tablero_logica;


class Alfil : public Pieza {

public:
    Alfil(const Tablero& t, bool color)
        : Pieza(tipo_t::ALFIL, t, color, 3) {
        if (color)
            sprite = new ETSIDI::Sprite("imagenes/Chess_blt60.png"); // alfil blanco
        else
            sprite = new ETSIDI::Sprite("imagenes/Chess_bdt60.png"); // alfil negro
    }

    vector <Posicion> movimientosValidos(Tablero_logica& tab);
    Pieza* clonar() const override;
};

