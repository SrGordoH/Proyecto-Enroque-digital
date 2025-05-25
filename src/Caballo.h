#pragma once
#include "Pieza.h"
#include "Tablero_logica.h"
#include <vector>
using namespace std;
class Tablero_logica;

class Caballo : public Pieza {
public:
    Caballo(bool color)
        : Pieza(tipo_t::CABALLO, color, 3) {
        if (color)
            sprite = new ETSIDI::Sprite("imagenes/Chess_nlt60.png"); // caballo blanco
        else
            sprite = new ETSIDI::Sprite("imagenes/Chess_ndt60.png"); // caballo negro
    }

    vector <Posicion> movimientosValidos(Tablero_logica& tab);
    Pieza* clonar() const override;

};

