#include "Rey.h"

vector<Posicion> Rey::movimientosValidos(Tablero_logica& tab, bool evitarJaque) {
    if (!pos.esValida()) return {};//para evitar piezas fuera del tablero o cualquier otro bug

    vector<Posicion> posibles; // Vector  movimientos validos
    int f = pos.fil, c = pos.col; // Posicion actual rey

    // Recorremos las 8 casillas que rodean al rey con dos bucles de tres casillas formando una cuadricula de nueve 3x3
    for (int df = -1; df <= 1; ++df) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (df == 0 && dc == 0) continue; // Obviamos el "no moverse"

            Posicion p = { f + df, c + dc }; // Nueva posicion

            if (p.esValida()) { // Aseguremos que este dentro del tablero
                posibles.push_back(p);
            }
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

Pieza* Rey::clonar() const {
    Rey* copia = new Rey(color);
    copia->SetPos(pos.fil, pos.col);
    return copia;
}

