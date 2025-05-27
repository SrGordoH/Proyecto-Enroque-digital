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

void IA::elegirMejorMovimientoFacil(bool color) {
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

void IA::elegirMejorMovimientoDificil(bool iaColor) {
    int mejorScoreGlobal = -1000000;
    Pieza* mejorP = nullptr;
    Posicion mejorD{ -1, -1 };
    auto piezas1 = logica->getPiezas();  //guardamos piezas

    // Para cada jugada posible de la IA
    for (Pieza* p : piezas1) {
        if (!p || p->getColor() != iaColor) continue;  //Evitamos punteros vacios o piezas rivales
        auto movs = p->movimientosValidos(*logica);    //Guardamos movimientos
        for (auto& d1 : movs) {
            // Simular primer movimiento
            if (!logica->moverPieza(p, d1)) continue;
            int score1 = AnalisisBasico();
            auto piezas2 = logica->getPiezas();

            // Evaluar la mejor respuesta del oponente
            int peorScoreParaIA = 1000000;
            for (Pieza* q : piezas2) {
                if (!q || q->getColor() == iaColor) continue;    //evitamos piezas ia o punteros sin pieza
                auto respuestas = q->movimientosValidos(*logica); 
                for (auto& d2 : respuestas) {
                    if (!logica->moverPieza(q, d2)) continue;   //salimos si no hay tablero logico y si si lo hay movemos
                    int score2 = AnalisisBasico();
                    logica->deshacerUltimoMovimiento();
                    logica->cambiarTurno();  // volver al turno del rival

                    // Suponemos que el oponente hace el mejor movimiento para si mismo
                    if (score2 < peorScoreParaIA) {
                        peorScoreParaIA = score2;
                    }
                }
            }

            // Sumamos ambas jugadas
            int scoreGlobal = score1 + peorScoreParaIA;

            // Deshacemos jugada
            logica->deshacerUltimoMovimiento();
            logica->cambiarTurno();

            // Guardamos si es la mejor secuencia
            if (scoreGlobal > mejorScoreGlobal) {
                mejorScoreGlobal = scoreGlobal;
                mejorP = p;
                mejorD = d1;
            }
        }
    }

    // Ejecutamos la mejor jugada
    if (mejorP) {
        logica->moverPieza(mejorP, mejorD);
    }
}