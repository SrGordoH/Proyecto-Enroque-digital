#pragma once
#include "Pieza.h"
#include "Tablero_logica.h"
#include <vector>
using namespace std;
class Tablero_logica;


class Dama : public Pieza {
public:
    Dama(bool color)
        : Pieza(tipo_t::DAMA, color, 10) {
        if (color)
            sprite = new ETSIDI::Sprite("imagenes/PiezasElectronicas/DamaAO_Blanca.png"); // dama blanca
        else
            sprite = new ETSIDI::Sprite("imagenes/PiezasElectronicas/DamaAO_Negra.png"); // dama negra
    }

    vector <Posicion> movimientosValidos(Tablero_logica& tab, bool evitarJaque = true) override;
    Pieza* clonar() const override;

};

