#include "IA.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
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


int IA::AnalisisBasico(Pieza* p, Posicion b, Tablero_logica* log) const {
    int score = 0;
    log->moverPieza(p, b);
    for (Pieza* p1 : log->getPiezas()) {
        int v = valorPieza(p1->getTipo());
        // sumamos valores piezas 
        if (p1->getColor() == iaColor) score += v;
        else score -= v;   //asignamos puntuacion
    }
    for (Pieza* p2 : log->getPiezas()) {
        if (!p2 || p2->getColor() != iaColor) continue;               // solo enemigas
        auto posEnemiga = p2->getPos();
        for (Pieza* mia : log->getPiezas()) {
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

void IA::elegirMejorMovimiento(bool color) {
    int indexp=0;
    int indexm=0;
    int scorefinal = -100000000000;

    for (int i = 0; i < 10; i++) {
        auto piezas = logica->getPiezas();
        int x = 0;
        if (piezas.size())
            x = std::rand() % piezas.size();  //pieza aleatoria
        else x = 0;
        while (piezas[x]->getColor() != color || !(piezas[x]->movimientosValidos(*logica)).size())x = std::rand() % piezas.size();//que tenga movimientos y sea del color adecuado 
        auto movs = piezas[x]->movimientosValidos(*logica);
        int indicem = std::rand() % (movs.size()); //movimiento aleatorio
        Tablero_logica* copia = crearTableroSimulado(piezas[x], movs[indicem]);
        auto aux = copia->getPiezas();
        int score = AnalisisBasico(aux[x], movs[indicem], copia);
        if (score > scorefinal) {
            scorefinal = score;
            indexp = x;
            indexm = indicem;
        }

    }
    auto piezas = logica->getPiezas();
    auto movs = piezas[indexp]->movimientosValidos(*logica);
    logica->moverPieza(piezas[indexp], movs[indexm]);


}



void IA::Movimiento(bool color) {
    auto piezas = logica->getPiezas();
    int x = std::rand() % piezas.size();  //pieza aleatoria
    while (piezas[x]->getColor() != color || !(piezas[x]->movimientosValidos(*logica)).size())x = std::rand() % piezas.size();//que tenga movimientos y sea del color adecuado
    auto movs = piezas[x]->movimientosValidos(*logica);
    int indicem = std::rand() % (movs.size());//movimiento aleatorio
       
    logica->moverPieza(piezas[x], movs[indicem]);
    
}


Tablero_logica* IA::crearTableroSimulado(Pieza* piezaOriginal, Posicion destino) const {
    Tablero_logica* simulado = new Tablero_logica();

    auto piezas = logica->getPiezas();
    for (int i = 0; i < piezas.size(); ++i) {
        Pieza* p = piezas[i];
        if (!p) continue;

        Pieza* clon = p->clonar();
        if (p == piezaOriginal) clon->SetPos(destino.fil, destino.col); // simula movimiento
        else clon->SetPos(p->getPos().fil, p->getPos().col);

        simulado->agregarPieza(clon);

    }
    return simulado;
}

