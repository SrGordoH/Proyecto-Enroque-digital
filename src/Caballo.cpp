#include "Caballo.h"

vector<Posicion> Caballo::movimientosValidos(Tablero_logica& tab, bool evitarJaque) {
    if (!pos.esValida()) return {};//para evitar piezas fuera del tablero o cualquier otro bug

    vector<Posicion> posibles; // Vector donde guardamos los movimientos validos
    int f = pos.fil, c = pos.col; // Obtenemos la fila y columna actual 

    // Vector de vectores con los movimientos del caballo
    int d[8][2] = { {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
                    {1, -2},  {1, 2},  {2, -1},  {2, 1} };

    // Recorremos cada desplazamiento
    for (auto& dxy : d) {
        // Calculamos la nueva posicion
        Posicion p = { f + dxy[0], c + dxy[1] };

        // Si la posicion esta dentro del tablero
        if (p.esValida()) {
            posibles.push_back(p); //puedes capturar cualquier pieza
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

Pieza* Caballo::clonar() const {
    Caballo* copia = new Caballo(color);
    copia->SetPos(pos.fil, pos.col);
    return copia;
}
