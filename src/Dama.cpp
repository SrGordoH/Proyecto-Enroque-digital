#include "Dama.h"

vector<Posicion> Dama::movimientosValidos(Tablero_logica& tab, bool evitarJaque) {
    if (!pos.esValida()) return {};//para evitar piezas fuera del tablero o cualquier otro bug

    vector<Posicion> posibles; // Vector de movimientos validos
    int f = pos.fil, c = pos.col; // Posicion actual de la Dama

    // Direcciones horizontales y verticales
    int dirLinea[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

    // Direcciones diagonales
    int dirDiagonal[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

    // Procesamos movimientos vertical y horizontal
    for (auto& d : dirLinea) {
        int nf = f + d[0], nc = c + d[1];

        // Mientras casilla valida
        while (true) {
            Posicion p = { nf, nc };
            if (!p.esValida()) break; // Si no es valida, detenemos

            Pieza* otra = tab.obtenerPieza(p); // Verificamos si hay pieza

            if (otra == nullptr) {
                posibles.push_back(p); // Casilla libre, movimiento valido
            }
            else {
                
                posibles.push_back(p); // Captura incluido tu color

                break; // Hay pieza y no puedes saltarla
            }

            nf += d[0]; nc += d[1]; // Avanzamos a la siguiente casilla en esa direccion
        }
    }

    // Procesamos movimientos en diagonal
    for (const auto& d : dirDiagonal) {
        int nf = f + d[0], nc = c + d[1];

        // Mientras casilla valida
        while (true) {
            Posicion p = { nf, nc };
            if (!p.esValida()) break; // Si no es valida, detenemos

            Pieza* otra = tab.obtenerPieza(p); // Verificamos si hay pieza

            if (otra == nullptr) {
                posibles.push_back(p); // Casilla libre, movimiento valido
            }
            else {
                posibles.push_back(p); // Captura cualquier color

                break; // Si hay pieza, no se puede avanzar mas
            }

            nf += d[0]; nc += d[1]; // Avanzamos en la diagonal siguiente casilla posible
        }
    }

    if (!evitarJaque) return posibles;

    std::vector<Posicion> legales;
    for (const Posicion& mov : posibles) {
        Pieza* destino = tab.obtenerPieza(mov);
        if (esMovimientoLegalConJaque(destino, mov, tab))
            legales.push_back(mov);
    }

    movs_validos = legales;
    return legales;
}

Pieza* Dama::clonar() const {
    Dama* copia = new Dama(color);
    copia->SetPos(pos.fil, pos.col);
    return copia;
}


