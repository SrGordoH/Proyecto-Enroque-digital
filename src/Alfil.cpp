
#include "Alfil.h"

vector<Posicion> Alfil::movimientosValidos(Tablero_logica& tab)  {

    if (!pos.esValida()) return {};//para evitar piezas fuera del tablero o cualquier otro bug

    vector<Posicion> movs; // Vector de movimientos validos
    int f = pos.fil, c = pos.col; // Posicion actual alfil

    // Direcciones diagonales
    int dir[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

    // Procesamos movimientos en diagonal
    for (const auto& d : dir) {
        int nf = f + d[0], nc = c + d[1];

        // Mientras casilla valida
        while (true) {
            Posicion p = { nf, nc };
            if (!p.esValida()) break; // Si no es valida, detenemos

            Pieza* otra = tab.obtenerPieza(p); // Verificamos si hay pieza

            if (otra == nullptr) {
                movs.push_back(p); // Casilla libre, movimiento valido
            }
            else {
                movs.push_back(p); // Captura cualquier color

                break; // Si hay pieza, no se puede avanzar mas
            }

            nf += d[0]; nc += d[1]; // Avanzamos en la diagonal siguiente casilla posible
        }
    }
    movs_validos = movs;
    return movs;
}

Pieza* Alfil::clonar() const {
    return new Alfil(*this);
}

