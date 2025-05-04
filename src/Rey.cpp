#include "Rey.h"

vector<Posicion> Rey::movimientosValidos(Tablero_logica& tab) const {
    vector<Posicion> movs; // Vector  movimientos validos
    int f = pos.fil, c = pos.col; // Posicion actual rey

    // Recorremos las 8 casillas que rodean al rey con dos bucles de tres casillas formando una cuadricula de nueve 3x3
    for (int df = -1; df <= 1; ++df) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (df == 0 && dc == 0) continue; // Obviamos el "no moverse"

            Posicion p = { f + df, c + dc }; // Nueva posicion

            if (p.esValida()) { // Aseguremos que este dentro del tablero
                Pieza* otra = tab.obtenerPieza(p.fil, p.col); // Obtenemos pieza en esa posicion

                // Si no hay pieza o es del color opuesto, es valido
                if (otra == nullptr || otra->getColor() != this->color)
                    movs.push_back(p);
            }
        }
    }
    return movs; // Retornamos posiciones validas
}
