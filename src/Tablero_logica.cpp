#include "Tablero_logica.h"

void Tablero_logica::inicializarTablero(const Tablero& tablero) {
    for (int i = 0; i < 5; ++i) {
        piezas.peonesblancos[i].SetPos(4, i + 1);
    }

    // Peones negros en fila 3
    for (int i = 0; i < 5; ++i) {
        peonesnegros[i].SetPos(3, i + 1);
    }
}

