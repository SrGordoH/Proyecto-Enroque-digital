#include "Caballo.h"

vector<Posicion> Caballo::movimientosValidos(Tablero_logica& tab) {
    vector<Posicion> movs; // Vector donde guardamos los movimientos validos
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
            movs.push_back(p); //puedes capturar cualquier pieza
        }
    }
    movs_validos = movs;

    return movs; // Devolvemos movimientos validos
}
