#pragma once
#include "Pieza.h"
#include "Tablero_logica.h"
#include <vector>
using namespace std;
class Tablero_logica;

class Rey : public Pieza {
public:
    Rey(bool color)
        : Pieza(tipo_t::REY, color, 0) {
        if (color)
            sprite = new ETSIDI::Sprite("imagenes/PiezasElectronicas/ReyMCU_Blanco.png"); // rey blanco
        else
            sprite = new ETSIDI::Sprite("imagenes/PiezasElectronicas/ReyMCU_Negro.png"); // rey negro
    }

    vector <Posicion> movimientosValidos(Tablero_logica& tab, bool evitarJaque = true) override;
    Pieza* clonar() const override;

};

