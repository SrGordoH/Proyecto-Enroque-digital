#pragma once
#include "Pieza.h"
#include "Posicion.h"

class Movimiento {
public:
    Pieza* pieza = nullptr;
    Posicion origen;
    Posicion destino;
    Pieza* capturada = nullptr;
    int indiceCapturada = -1;

    Movimiento() = default;

    Movimiento(Pieza* p, Posicion o, Posicion d, Pieza* c = nullptr, int idx = -1)
        : pieza(p), origen(o), destino(d), capturada(c), indiceCapturada(idx) {
    }

    bool esCaptura() const { return capturada != nullptr; }
};

