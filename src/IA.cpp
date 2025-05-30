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


int IA::AnalisisBasico(Pieza* p, Posicion b, Tablero_logica* log, Pieza* capturada) const {
   
    int score = 0;

    if (capturada) {
        // Penalización extrema si se intenta capturar a su propio rey
        if (capturada->getColor() == p->getColor() && capturada->getTipo() == Pieza::tipo_t::REY) {
            return -100000;  // Movimiento suicida (solo caso extremo)
        }

        // Penalización por capturar aliada (más suave que rey)
        if (capturada->getColor() == p->getColor()) {
            return -1000;
        }
    }

    log->cambiarTurno(); // Simula que ahora le toca al rival

    //Si el movimiento deja al oponente en jaque, priorizar
    bool rivalColor = !iaColor;
    if (log->estaEnJaque(rivalColor)) {
        return 10000; // Prioridad: jaque 
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

int IA::AnalisisComplejo(Pieza* p, Posicion b, Tablero_logica* log, Pieza* capturada) const {

    int score = 0;

    if (capturada) {
        // Penalización extrema si se intenta capturar a su propio rey
        if (capturada->getColor() == p->getColor() && capturada->getTipo() == Pieza::tipo_t::REY) {
            return -100000;  // Movimiento suicida (solo caso extremo)
        }

        // Penalización por capturar aliada (más suave que rey)
        if (capturada->getColor() == p->getColor()) {
            return -1000;
        }

        // Captura enemiga: bonificación según el valor de la pieza capturada
        int valor = valorPieza(capturada->getTipo());
        score += valor * 30;  // Capturas bien recompensadas
    }

    log->moverPieza(p, b, true);
    log->cambiarTurno();  // Evaluamos el nuevo estado desde el turno del oponente

    // Jaque mate: prioridad máxima
    if (log->estaEnJaqueMate(!iaColor)) {
        return 100000;
    }

    //Bonificación por poner al rival en jaque
    if (log->estaEnJaque(!iaColor)) {
        score += 70;
    }

    //Bonificación adicional: acercarse a piezas valiosas enemigas
    for (Pieza* enemiga : log->getPiezas()) {
        if (!enemiga || enemiga->getColor() == iaColor) continue;

        Posicion posEnemiga = enemiga->getPos();
        for (Pieza* mia : log->getPiezas()) {
            if (!mia || mia->getColor() != iaColor) continue;

            Posicion posMia = mia->getPos();
            int df = abs(posMia.fil - posEnemiga.fil);
            int dc = abs(posMia.col - posEnemiga.col);
            float dist = df + dc;

            int valor = valorPieza(enemiga->getTipo());
            score += (valor * 2) / (1 + dist);  // Bono por presión
        }
    }

    return score;
}


Movimiento IA::mejorMovimientoSimple(bool color) {

    vector<Movimiento> opciones = movimientosLegales(color);

    if (opciones.empty()) {
        std::cout << "[IA] No hay movimientos legales disponibles.\n";
        return Movimiento();  // movimiento por defecto, con punteros nulos
    }

    Movimiento mejor = opciones[0];
    int mejorScore = -100000000;

    for (const Movimiento& m : opciones) {
        // Simular tablero con ese movimiento
        Tablero_logica* simulado = crearTableroSimulado(m.pieza, m.destino);
        Pieza* clon = simulado->obtenerPieza(m.destino);

        if (!clon) {
            delete simulado;
            continue;
        }

        int score = AnalisisBasico(clon, m.destino, simulado, m.capturada);
        delete simulado;

        if (score > mejorScore) {
            mejorScore = score;
            mejor = m;
        }
    }

    return mejor;
}

Movimiento IA::mejorMovimientoComplejo(bool color) { //Utiliza el analisis complejo

    vector<Movimiento> opciones = movimientosLegales(color);

    if (opciones.empty()) {
        std::cout << "[IA] No hay movimientos legales disponibles.\n";
        return Movimiento();  // movimiento por defecto, con punteros nulos
    }

    Movimiento mejor = opciones[0];
    int mejorScore = -100000000;

    for (const Movimiento& m : opciones) {
        // Simular tablero con ese movimiento
        Tablero_logica* simulado = crearTableroSimulado(m.pieza, m.destino);
        Pieza* clon = simulado->obtenerPieza(m.destino);

        if (!clon) {
            delete simulado;
            continue;
        }

        int score = AnalisisComplejo(clon, m.destino, simulado, m.capturada);
        delete simulado;

        if (score > mejorScore) {
            mejorScore = score;
            mejor = m;
        }
    }

    return mejor;
}

void IA::elegirMejorMovimientoSimple(bool color) {
    //if (intentarJaqueMate(color)) return;

    Movimiento mejor = mejorMovimientoSimple(color);

    if (mejor.pieza) {
        logica->moverPieza(mejor.pieza, mejor.destino, true);
    }
    else {
        std::cout << "[IA] No hay movimientos válidos para el color " << (color ? "blanco" : "negro") << ".\n";
    }
}

void IA::elegirMejorMovimientoAvanzado(bool color) { // Utiliza el movimiento complejo
    //if (intentarJaqueMate(color)) return;
    
    Movimiento mejor = mejorMovimientoComplejo(color);

    if (mejor.pieza) {
        logica->moverPieza(mejor.pieza, mejor.destino, true);
    }
    else {
        std::cout << "[IA] No hay movimientos válidos para el color " << (color ? "blanco" : "negro") << ".\n";
    }
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

bool IA::esCapturaAliada(Pieza* p, Posicion destino) const {
    Pieza* destinoPieza = logica->obtenerPieza(destino);
    return destinoPieza && destinoPieza->getColor() == p->getColor();
}

bool IA::intentarJaqueMate(bool color) {
    auto piezas = logica->getPiezas();

    for (int i = 0; i < piezas.size(); ++i) {
        if (!piezas[i] || piezas[i]->getColor() != color) continue;

        auto movs = piezas[i]->movimientosValidos(*logica);
        for (int j = 0; j < movs.size(); ++j) {
            Tablero_logica* copia = crearTableroSimulado(piezas[i], movs[j]);
            Pieza* clon = copia->obtenerPieza(movs[j]);

            if (!clon) {
                delete copia;
                continue;
            }

            copia->moverPieza(clon, movs[j], true);
            copia->cambiarTurno();

            if (copia->estaEnJaqueMate(!color)) {
                delete copia;
                logica->moverPieza(piezas[i], movs[j], true);
                return true;
            }

            delete copia;
        }
    }
    return false; // No encontró mate
}

vector<Movimiento> IA::movimientosLegales(bool color) {
    vector<Movimiento> resultado;
    auto piezas = logica->getPiezas();

    for (int i = 0; i < piezas.size(); ++i) {
        Pieza* p = piezas[i];
        if (!p || p->getColor() != color) continue;

        auto movs = p->movimientosValidos(*logica);

        for (const Posicion& destino : movs) {
            // Simular movimiento
            Tablero_logica* copia = crearTableroSimulado(p, destino);
            Pieza* clon = copia->obtenerPieza(destino);
            if (!clon) {
                delete copia;
                continue;
            }

            // Solo agregamos el movimiento si no deja al rey en jaque
            if (!clon->estaEnJaque(*copia)) {
                // Obtener pieza capturada real (si existe) en el tablero actual
                Pieza* capturada = logica->obtenerPieza(destino);
                int indiceCapturada = -1;
                if (capturada) {
                    for (int j = 0; j < piezas.size(); ++j) {
                        if (piezas[j] == capturada) {
                            indiceCapturada = j;
                            break;
                        }
                    }
                }

                resultado.emplace_back(p, p->getPos(), destino, capturada, indiceCapturada);
            }

            delete copia;
        }
    }

    return resultado;
}
