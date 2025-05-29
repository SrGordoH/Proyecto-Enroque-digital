
#include "Torre.h"
vector<Posicion> Torre::movimientosValidos(Tablero_logica& tab, bool evitarJaque) {
    if (!pos.esValida()) return {};//para evitar piezas fuera del tablero o cualquier otro bug

    vector<Posicion> posibles; // Vector de movimientos validos
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

            posibles.push_back(p); // se puede comer cualquier pieza

            if (otra != nullptr) break; // detenemos al encontrar pieza

            nf += d[0]; nc += d[1]; // Avanzamos en la misma direccion la siguiente casilla
        }
    }
    // Si no hace falta filtrar por jaque, devolvemos directamente
        if (!evitarJaque) {
            movs_validos = posibles;
            return posibles;
        }

    // Filtrado de movimientos que evitarían dejar al rey en jaque
    std::vector<Posicion> legales;
    for (const Posicion& mov : posibles) {
        Pieza* destino = tab.obtenerPieza(mov);
        if (this->esMovimientoLegalConJaque(destino, mov, tab)) {
            legales.push_back(mov);
        }
    }

    movs_validos = legales;
    return legales;
}

Pieza* Torre::clonar() const {
    Torre* copia = new Torre(color);
    copia->SetPos(pos.fil, pos.col);
    return copia;
}
