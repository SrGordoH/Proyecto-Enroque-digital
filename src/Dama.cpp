#include "Dama.h"

vector<Posicion> Dama::movimientosValidos(Tablero_logica& tab) const {
    vector<Posicion> movs; // Vector de movimientos validos
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

            Pieza* otra = tab.obtenerPieza(nf, nc); // Verificamos si hay pieza

            if (otra == nullptr) {
                movs.push_back(p); // Casilla libre, movimiento valido
            }
            else {
                if (otra->getColor() != this->color)
                    movs.push_back(p); // Captura valida

                break; // Hay pieza
            }

            nf += d[0]; nc += d[1]; // Avanzamos a la siguiente casilla en esa direccion
        }
    }

    // Procesamos movimientos en diagonal
    for (auto& d : dirDiagonal) {
        int nf = f + d[0], nc = c + d[1];

        // Mientras casilla vlida
        while (true) {
            Posicion p = { nf, nc };
            if (!p.esValida()) break; // Si no es vlida, detenemos

            Pieza* otra = tab.obtenerPieza(nf, nc); // Verificamos si hay pieza

            if (otra == nullptr) {
                movs.push_back(p); // Casilla libre, movimiento valido
            }
            else {
                if (otra->getColor() != this->color)
                    movs.push_back(p); // Captura valida

                break; // Si hay pieza, no se puede avanzar mas
            }

            nf += d[0]; nc += d[1]; // Avanzamos en la diagonal siguiente casilla posible
        }
    }

    return movs; // Devolvemos los movimientos validos
}
