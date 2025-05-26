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
    int evaluarMovimiento(Pieza* pieza, Posicion destino, bool color) const;
    bool esMovimientoDeCaptura(Pieza* pieza, Posicion destino) const;
    int AnalisisBasico() const;
    int AnalisisProfundo(bool turno, int profundidad);


public:
    void elegirMejorMovimientoFacil(bool color, Pieza*& mejorPieza, Posicion& mejorDestino);
    void elegirMejorMovimientoDificil(bool color, Pieza*& mejorPieza, Posicion& mejorDestino);

    bool hayCapturasDisponibles(bool color) const;
};
