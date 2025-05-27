#pragma once
#include "Tablero_logica.h"
#include "Pieza.h"
#include "Posicion.h"
#include <vector>

class IA {
private:
    Tablero_logica* logica;
    bool iaColor = 0;
    int valorPieza(Pieza::tipo_t tipo) const;
    float distancia(Posicion a, Posicion b) const;
    int AnalisisBasico() const;

public:
    void setLogica(Tablero_logica* log) { logica = log; }
    void elegirMejorMovimientoFacil(bool color);
    void elegirMejorMovimientoDificil(bool color);
};
