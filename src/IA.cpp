#include "IA.h"
#include <cmath>
#include <iostream>

int IA::valorPieza(Pieza::tipo_t tipo) const {
    if (tipo == Pieza::tipo_t::PEON) return 1;
    if (tipo == Pieza::tipo_t::CABALLO) return 3;
    if (tipo == Pieza::tipo_t::ALFIL) return 3;
    if (tipo == Pieza::tipo_t::TORRE) return 5;
    if (tipo == Pieza::tipo_t::DAMA) return 9;
    if (tipo == Pieza::tipo_t::REY) return 100;
    return 0;
}



float IA::distancia(Posicion a, Posicion b) const {
    int df = a.fil - b.fil;
    int dc = a.col - b.col;
    return std::sqrt(df * df + dc * dc);
}

bool IA::esMovimientoDeCaptura(Pieza* pieza, Posicion destino) const {
    Pieza* objetivo = logica->obtenerPieza(destino);
    return objetivo && objetivo->getColor() != pieza->getColor();
}

int IA::evaluarMovimiento(Pieza* pieza, Posicion destino, bool color) const {
    int puntaje = 0;

    Pieza* enDestino = logica->obtenerPieza(destino);
    if (enDestino && enDestino->getColor() != color) {
        puntaje += valorPieza(enDestino->getTipo()) * 10;
    }

    for (Pieza* otra : logica->getPiezas()) {
        if (!otra || otra->getColor() == color || !otra->getPos().esValida()) continue;
        float d = distancia(destino, otra->getPos());
        if (valorPieza(otra->getTipo()) >= 5 && d <= 3.0f) {
            puntaje += 5;
        }
    }

    if (!enDestino && valorPieza(pieza->getTipo()) >= 5) {
        puntaje -= 3;
    }

    return puntaje;
}

void IA::elegirMejorMovimiento(bool color, Pieza*& mejorPieza, Posicion& mejorDestino) {
    int mejorPuntaje = -10000;
    mejorPieza = nullptr;
    mejorDestino = { -1, -1 };

    for (Pieza* pieza : logica->getPiezas()) {
        if (!pieza || pieza->getColor() != color || !pieza->getPos().esValida()) continue;

        std::vector<Posicion> movimientos = pieza->movimientosValidos(*logica);

        for (const Posicion& destino : movimientos) {
            int puntaje = evaluarMovimiento(pieza, destino, color);
            if (puntaje > mejorPuntaje) {
                mejorPuntaje = puntaje;
                mejorPieza = pieza;
                mejorDestino = destino;
            }
        }
    }
}


bool IA::hayCapturasDisponibles(bool color) const {
    for (Pieza* pieza : logica->getPiezas()) {
        if (!pieza || pieza->getColor() != color || !pieza->getPos().esValida()) continue;

        std::vector<Posicion> movs = pieza->movimientosValidos(*logica);

        for (const Posicion& p : movs) {
            if (esMovimientoDeCaptura(pieza, p)) return true;
        }
    }
    return false;
}

