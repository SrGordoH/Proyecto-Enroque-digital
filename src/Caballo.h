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
            sprite = new ETSIDI::Sprite("imagenes/PiezasElectronicas/CaballoTransistor_Blanco.png"); // caballo blanco
        else
            sprite = new ETSIDI::Sprite("imagenes/PiezasElectronicas/CaballoTransistor_Negro.png"); // caballo negro
    }

    vector <Posicion> movimientosValidos(Tablero_logica& tab, bool evitarJaque = true) override;
    Pieza* clonar() const override;

};

