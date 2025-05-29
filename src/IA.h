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

public:
    void setLogica(Tablero_logica* log) { logica = log; }
    void elegirMejorMovimiento(bool color);
    void Movimiento(bool color);
    Tablero_logica* crearTableroSimulado(Pieza* piezaOriginal, Posicion destino) const;
    int AnalisisBasico(Pieza* p, Posicion b, Tablero_logica* log) const;


};
