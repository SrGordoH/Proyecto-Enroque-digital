
#include "Alfil.h"

vector<Posicion> Alfil::movimientosValidos(Tablero_logica& tab) const {
    vector<Posicion> movs; // Vector de movimientos validos
    int f = pos.fil, c = pos.col; // Posicion actual alfil

    // Direcciones diagonales
    int dir[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

    // Recorremos cada direccion
    for (auto& d : dir) {
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

                break; 
            }

            nf += d[0]; nc += d[1]; // Avanzamos en la diagonal siguiente casilla posible
        }
    }
    return movs;
}
