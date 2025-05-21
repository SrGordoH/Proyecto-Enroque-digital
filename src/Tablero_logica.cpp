#include "Tablero_logica.h"

void Tablero_logica::inicializarTablero(const Tablero& tablero) {  // Aqui agregamos el nombre de la clase
    // === PEONES ===
    for (int i = 0; i < 5; ++i) {
        piezas.push_back(new Peon(tablero, true));  // Blancos
        piezas.push_back(new Peon(tablero, false)); // Negros
    }

    // === TORRES ===
    piezas.push_back(new Torre(tablero, true));  // Blanca
    piezas.push_back(new Torre(tablero, false)); // Negra

    // === CABALLOS ===
    piezas.push_back(new Caballo(tablero, true));
    piezas.push_back(new Caballo(tablero, false));

    // === ALFILES ===
    piezas.push_back(new Alfil(tablero, true));
    piezas.push_back(new Alfil(tablero, false));

    // === DAMAS ===
    piezas.push_back(new Dama(tablero, true));
    piezas.push_back(new Dama(tablero, false));

    // === REYES ===
    piezas.push_back(new Rey(tablero, true));
    piezas.push_back(new Rey(tablero, false));
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


Pieza* Tablero_logica::obtenerPieza(Posicion casilla) const {
    for (Pieza* p : piezas) {
        Posicion pos = p->getPos();
        if (pos.fil == casilla.fil && pos.col == casilla.col) {
            return p;
        }
    }
    return nullptr; // No hay pieza en esa posicion
}


Posicion Tablero_logica::obtenerReyPos(bool color) {
    // Recorremos todo el tablero para encontrar la pieza de tipo Rey con el color especificado
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 6; ++j) {
            Pieza* pieza = obtenerPieza(Posicion(i, j));  // Obtener la pieza en la posicion (i, j)

            if (pieza != nullptr && pieza->getColor() == color && pieza->getTipo() == Pieza::tipo_t::REY) {
                // Si encontramos una pieza del color buscado y es un Rey, retornamos su posicion
                return Posicion{ i, j };  // Posicion de la pieza encontrada
            }
        }
    }
    return Posicion{ -1, -1 };  // Posicion invalida si no se encuentra el rey


}

vector<Pieza*> Tablero_logica::obtenerPiezasOponente(bool color) const {
    vector<Pieza*> piezasOponente;

    for (Pieza* p : piezas) {
        if (p != nullptr && p->getColor() != color) {
            piezasOponente.push_back(p);
        }
    }

    return piezasOponente;
}


bool Tablero_logica::estaEnJaqueMate(bool color) {
    for (Pieza* p : piezas) {
        if (p->getColor() == color) {
            std::vector<Posicion> posibles = p->movimientosValidos(*this);
            for (const Posicion& destino : posibles) {
                Pieza* piezaDestino = obtenerPieza(destino);
                if (p->esMovimientoLegalConJaque(piezaDestino, destino, *this)) {
                    return false; // Si hay al menos un movimiento legal que evita el jaque, no es jaque mate
                }
            }
        }
    }
    return true; 
}
