#pragma once
#include "Tablero_logica.h"
#include "Pieza.h"
#include "Posicion.h"
#include <vector>

class IA {
private:
    Tablero_logica* logica;

    int valorPieza(Pieza::tipo_t tipo) const;
    float distancia(Posicion a, Posicion b) const;
    int evaluarMovimiento(Pieza* pieza, Posicion destino, bool color) const;
    bool esMovimientoDeCaptura(Pieza* pieza, Posicion destino) const;

public:
    void elegirMejorMovimiento(bool color, Pieza*& mejorPieza, Posicion& mejorDestino);
    bool hayCapturasDisponibles(bool color) const;
};
