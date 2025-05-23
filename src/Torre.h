#pragma once
#include "Pieza.h"
#include "Tablero_logica.h"
#include <vector>
using namespace std;
class Tablero_logica;

class Torre : public Pieza {
public:
    Torre(const Tablero& t, bool color)
        : Pieza(tipo_t::TORRE, t, color, 5) {
        if (color)
            sprite = new ETSIDI::Sprite("imagenes/Chess_rlt60.png"); // torre blanca
        else
            sprite = new ETSIDI::Sprite("imagenes/Chess_rdt60.png"); // torre negra
    }

    vector <Posicion> movimientosValidos(Tablero_logica& tab);


};

