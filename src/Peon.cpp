#include "Peon.h"
using namespace std;

vector<Posicion> Peon::movimientosValidos(Tablero_logica &tab, bool evitarJaque) {
    if (!pos.esValida()) return {};//para evitar piezas fuera del tablero o cualquier otro bug

    vector<Posicion> posibles;  // Lista de movimientos validos

    // La dirección del peon depende del color:
    int dir = color;
    if (color == 1)
        dir = 1;
    else
        dir = -1;

    // Fila y columna actuales del peon
    int f = pos.fil;
    int c = pos.col;

    
    Posicion adelante = { f + dir, c };
    if (adelante.esValida() && tab.obtenerPieza(adelante) == nullptr) {
        posibles.push_back(adelante);  
    }

    Posicion diagIzq = { f + dir, c - 1 };
    if (diagIzq.esValida()) {  // Solo si la posicion esta dentro del tablero
        Pieza* p = tab.obtenerPieza(diagIzq);
        if (p != nullptr) {
            posibles.push_back(diagIzq);  //Puedes comerte tus piezas
        }
    }

    Posicion diagDer = { f + dir, c + 1 };
    if (diagDer.esValida()) {
        Pieza* p = tab.obtenerPieza(diagDer);
        if (p != nullptr) {
            posibles.push_back(diagDer);  
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

Pieza* Peon::clonar() const {
    Peon* copia = new Peon(color);
    copia->SetPos(pos.fil, pos.col);
    return copia;
}

