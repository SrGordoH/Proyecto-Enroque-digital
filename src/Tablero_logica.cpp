#include "Tablero_logica.h"

void Tablero_logica::inicializarTablero(const Tablero& tablero) {  // Aquí agregamos el nombre de la clase
    // === PEONES ===
    for (int i = 0; i < 5; ++i) {
        piezas.push_back(new Peon(tablero, false)); // Negros
        piezas.push_back(new Peon(tablero, true));  // Blancos
    }

    // === TORRES ===
    piezas.push_back(new Torre(tablero, false)); // Negra
    piezas.push_back(new Torre(tablero, true));  // Blanca

    // === CABALLOS ===
    piezas.push_back(new Caballo(tablero, false));
    piezas.push_back(new Caballo(tablero, true));

    // === ALFILES ===
    piezas.push_back(new Alfil(tablero, false));
    piezas.push_back(new Alfil(tablero, true));

    // === DAMAS ===
    piezas.push_back(new Dama(tablero, false));
    piezas.push_back(new Dama(tablero, true));

    // === REYES ===
    piezas.push_back(new Rey(tablero, false));
    piezas.push_back(new Rey(tablero, true));
}

void Tablero_logica::setearPosicionesIniciales(int modo) {
    if (modo == 0) {
        //Modo Petty

        // === Peones ===
        for (int i = 0; i < 5; ++i) {
            piezas[i * 2]->SetPos(2, i + 1);     // Peones negros (fila 2)
            piezas[i * 2 + 1]->SetPos(5, i + 1); // Peones blancos (fila 5)
        }

        piezas[10]->SetPos(1, 5); // Torre negra
        piezas[11]->SetPos(6, 5); // Torre blanca

        piezas[12]->SetPos(1, 4); // Caballo negro
        piezas[13]->SetPos(6, 4); // Caballo blanco

        piezas[14]->SetPos(1, 3); // Alfil negro
        piezas[15]->SetPos(6, 3); // Alfil blanco

        piezas[16]->SetPos(1, 1); // Dama negra
        piezas[17]->SetPos(6, 1); // Dama blanca

        piezas[18]->SetPos(1, 2); // Rey negro
        piezas[19]->SetPos(6, 2); // Rey blanco

    }
    else if (modo == 1) {
        //Modo Reyes en esquinas opuestas

        // === Peones ===
        for (int i = 0; i < 5; ++i) {
            piezas[i * 2]->SetPos(2, i + 1);     // Peones negros (fila 2)
            piezas[i * 2 + 1]->SetPos(5, i + 1); // Peones blancos (fila 5)
        }

        piezas[10]->SetPos(1, 5); // Torre negra
        piezas[11]->SetPos(6, 1); // Torre blanca

        piezas[12]->SetPos(1, 4); // Caballo negro
        piezas[13]->SetPos(6, 2); // Caballo blanca

        piezas[14]->SetPos(1, 3); // Alfil negro
        piezas[15]->SetPos(6, 3); // Alfil blanco

        piezas[16]->SetPos(1, 2); // Dama negra
        piezas[17]->SetPos(6, 4); // Dama blanca

        piezas[18]->SetPos(1, 1); // Rey negro
        piezas[19]->SetPos(6, 5); // Rey blanco
    }
}

Pieza* Tablero_logica::obtenerPieza(int fil, int col) const {
    for (Pieza* p : piezas) {
        Posicion pos = p->getPos();
        if (pos.fil == fil && pos.col == col) {
            return p;
        }
    }
    return nullptr; // No hay pieza en esa posición
}


