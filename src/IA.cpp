#include "IA.h"
#include <cmath>
#include <iostream>
#include <vector>
#include "Tablero_logica.h"

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

void IA::elegirMejorMovimientoFacil(bool color, Pieza*& mejorPieza, Posicion& mejorDestino) {
    int mejorPuntaje = -1000000;
    Pieza* mejorP = nullptr;
    Posicion mejorD{ -1, -1 };

    for (Pieza* p : logica->getPiezas()) {
        if (!p || p->getColor() != iaColor) continue;   //Evitamos piezas rivales piezas o puntero sin pieza
        auto movs = p->movimientosValidos(*logica);
        for (auto& d : movs) {                          //recorremos movimientos 
            if (!logica->moverPieza(p, d)) continue;    //Evitamos si el puntero al tablero logico no esta correctamente y movemos 
            int val = AnalisisBasico();                    
            logica->deshacerUltimoMovimiento();         //Deshacemos tras evaluar    
            if (val > mejorPuntaje) {
                mejorPuntaje = val;
                mejorP = p;
                mejorD = d;
            }
        }
    }
    if (mejorP) logica->moverPieza(mejorP, mejorD);    //Devolvemos lo mejor
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

int IA::AnalisisBasico() const {
    int score = 0;
    for (Pieza* p : logica->getPiezas()) {
        int v = valorPieza(p->getTipo());
        // sumamos valores piezas 
        if (p->getColor() == iaColor) score += v;
        else score -= v;   //asignamos puntuacion
    }
    for (Pieza* p : logica->getPiezas()) {
        if (!p || p->getColor() != iaColor) continue;               // solo enemigas
        auto posEnemiga = p->getPos();
        for (Pieza* mia : logica->getPiezas()) {
            if (!mia || mia->getColor() != iaColor) continue;      // solo propias
            auto posMia = mia->getPos();
            int df = abs(posMia.fil - posEnemiga.fil);
            int dc = abs(posMia.col - posEnemiga.col);
            float dist = df + dc;                                 // Distancia en 2 rectas

            int valorPresa = valorPieza(p->getTipo());
            score += (valorPresa * 2) / (1 + dist);               // Formula para aumentar valor segun te acercas a piezas valiosas  
        }
    }

    return score;
}

int IA::AnalisisProfundo(bool turno, int profundidad) {
   
        //2iteraciones de analisis basico
    return 0;
}
