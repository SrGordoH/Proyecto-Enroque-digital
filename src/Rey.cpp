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
                Pieza* otra = tab.obtenerPieza(p); // Obtenemos pieza en esa posicion

                // Si no hay pieza o es del color opuesto, es valido
                if (otra == nullptr || otra->getColor() != this->color)
                    movs.push_back(p);
            }
        }
    }
    return movs; // Retornamos posiciones validas
}

vector<Pieza*> Rey::puedeComer(Tablero_logica& tab) const {
    vector<Pieza*> comibles; // Vector de punteros a piezas que puede comer
    int f = pos.fil, c = pos.col; // Posición actual del rey

    // Recorremos las 8 casillas adyacentes
    for (int df = -1; df <= 1; ++df) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (df == 0 && dc == 0) continue; // Ignoramos la posición actual

            Posicion p = { f + df, c + dc };

            if (p.esValida()) {
                Pieza* otra = tab.obtenerPieza(p);

                // Si hay una pieza del color opuesto, se puede comer
                if (otra != nullptr && otra->getColor() != this->color)
                    comibles.push_back(otra);
            }
        }
    }

    return comibles; // Retornamos punteros a las piezas comestibles
}
