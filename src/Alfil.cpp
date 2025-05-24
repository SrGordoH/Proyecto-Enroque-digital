
#include "Alfil.h"

vector<Posicion> Alfil::movimientosValidos(Tablero_logica& tab)  {

    if (!pos.esValida()) return {};//para evitar piezas fuera del tablero o cualquier otro bug

    vector<Posicion> movs; // Vector de movimientos validos
    int f = pos.fil, c = pos.col; // Posicion actual alfil

    // Direcciones diagonales
    int dir[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

    // Recorremos cada direccion
    for (const auto& d : dir) {
        int nf = f + d[0], nc = c + d[1];
        Posicion p = { nf, nc };

        // Mientras casilla valida
        while (p.esValida()) {

            Pieza* otra = tab.obtenerPieza(p); // Verificamos si hay pieza

            if (otra == nullptr) {
                movs.push_back(p); // Casilla libre, movimiento valido
                nf += d[0]; nc += d[1]; // Avanzamos en la diagonal siguiente casilla posible
            }
            else {
                    movs.push_back(p);
                    break;   //No puedes capturar y seguir en esa misma direccion

            }
        }
    }
    movs_validos = movs;
    return movs;
}
