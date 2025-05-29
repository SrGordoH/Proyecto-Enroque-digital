#pragma once
#include "Pieza.h"
#include "Tablero_logica.h"
#include <vector>
using namespace std;
class Tablero_logica;

class Torre : public Pieza {
public:
    Torre(bool color)
        : Pieza(tipo_t::TORRE, color, 5) {
        if (color)
            sprite = new ETSIDI::Sprite("imagenes/PiezasElectronicas/TorreCondensador_Blanco.png"); // torre blanca
        else
            sprite = new ETSIDI::Sprite("imagenes/PiezasElectronicas/TorreCondensador_Negro.png"); // torre negra
    }
    vector <Posicion> movimientosValidos(Tablero_logica& tab);
    Pieza* clonar() const override;

};

