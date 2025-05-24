
#include "Torre.h"
vector<Posicion> Torre::movimientosValidos(Tablero_logica& tab) {
    vector<Posicion> movs; // Vector de movimientos validos
    int f = pos.fil, c = pos.col; // Posicion actual de la torre

    // Direcciones de movimiento
    int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

    // Recorremos cada direccion
    for (auto& d : dir) {
        int nf = f + d[0], nc = c + d[1]; // Primera casilla en esa direccion

        // Mientras la casilla sea valida
        while (true) {
            Posicion p = { nf, nc };
            if (!p.esValida()) break; // Si no es valida, detenemos la busqueda

            Pieza* otra = tab.obtenerPieza(p); // Verificamos si hay una pieza

            if (otra == nullptr) {
                movs.push_back(p); // Si no hay pieza movimiento valido
            }
            else {
                movs.push_back(p); // Capturamos sea cual sea el color
                break; 
            }

            nf += d[0]; nc += d[1]; // Avanzamos en la misma direccion la siguiente casilla
        }
    }
    movs_validos = movs;

    return movs; // Retornamos movimientos validos
}
