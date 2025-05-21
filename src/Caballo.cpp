#include "Caballo.h"

vector<Posicion> Caballo::movimientosValidos(Tablero_logica& tab) const {
    vector<Posicion> movs; // Vector donde guardamos los movimientos validos
    int f = pos.fil, c = pos.col; // Obtenemos la fila y columna actual 

    // Vector de vectores con los movimientos del caballo
    int d[8][2] = { {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
                    {1, -2},  {1, 2},  {2, -1},  {2, 1} };

    // Recorremos cada desplazamiento
    for (auto& dxy : d) {
        // Calculamos la nueva posicion
        Posicion p = { f + dxy[0], c + dxy[1] };

        // Si la posicion es valida dentro del tablero
        if (p.esValida()) {
            Pieza* otra = tab.obtenerPieza(p); // Obtenemos si hay una pieza

            // Si no hay pieza o hay una del color opuesto
            if (otra == nullptr || otra->getColor() != this->color)
                movs.push_back(p); // Agregamos movimiento valido
        }
    }
    return movs; // Devolvemos movimientos validos
}
