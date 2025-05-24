#pragma once
#include "Pieza.h"
#include <vector>
#include "Tablero_logica.h"

using namespace std;
class Tablero_logica;
class Peon : public Pieza {
public:

    Peon(const Tablero& t, bool color)
        : Pieza(tipo_t::PEON, t, color, 1) {
        if (color)
            sprite = new ETSIDI::Sprite("imagenes/Chess_plt60.png"); // peon blanco
        else
            sprite = new ETSIDI::Sprite("imagenes/Chess_pdt60.png"); // peon negro
    }

    vector <Posicion> movimientosValidos(Tablero_logica &tab);

};




