#include "Tablero_logica.h"

void Tablero_logica::inicializarTablero(const Tablero& tablero) {  // Aquí agregamos el nombre de la clase
    // === PEONES ===
    for (int i = 0; i < 5; ++i) {
        piezas.push_back(new Peon(tablero, false)); // Negros
        piezas.push_back(new Peon(tablero, true));  // Blancos
    }

    // === TORRES ===
    piezas.push_back(new Torre(tablero, false)); // Negra
    piezas.push_back(new Torre(tablero, true));  // Blanca

    // === CABALLOS ===
    piezas.push_back(new Caballo(tablero, false));
    piezas.push_back(new Caballo(tablero, true));

    // === ALFILES ===
    piezas.push_back(new Alfil(tablero, false));
    piezas.push_back(new Alfil(tablero, true));

    // === DAMAS ===
    piezas.push_back(new Dama(tablero, false));
    piezas.push_back(new Dama(tablero, true));

    // === REYES ===
    piezas.push_back(new Rey(tablero, false));
    piezas.push_back(new Rey(tablero, true));
}
