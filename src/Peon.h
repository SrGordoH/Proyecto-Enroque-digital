#pragma once
#include "Pieza.h"
#include <vector>
#include "Tablero_logica.h"

using namespace std;
class Tablero_logica;
class Peon : public Pieza {
public:

    Peon(bool color)
        : Pieza(tipo_t::PEON, color, 1) {
        if (color)
            sprite = new ETSIDI::Sprite("imagenes/PiezasElectronicas/PeonRessitencia_Blanco_.png"); // peon blanco
        else
            sprite = new ETSIDI::Sprite("imagenes/PiezasElectronicas/PeonResistencia_Negro.png"); // peon negro
    }
    vector <Posicion> movimientosValidos(Tablero_logica &tab, bool evitarJaque = true) override;
    Pieza* clonar() const override;

};




