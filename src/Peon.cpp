#include "Peon.h"
using namespace std;

vector<Posicion> Peon::movimientosValidos(Tablero_logica &tab) const {
    vector<Posicion> movs;  // Lista de movimientos validos

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
    if (adelante.esValida() && tab.obtenerPieza(adelante.fil, adelante.col) == nullptr) {
        movs.push_back(adelante);  
    }

    Posicion diagIzq = { f + dir, c - 1 };
    if (diagIzq.esValida()) {  // Solo si la posición está dentro del tablero
        Pieza* p = tab.obtenerPieza(diagIzq.fil, diagIzq.col);
        if (p != nullptr && p->getColor() != this->color) {
            movs.push_back(diagIzq);  // Solo si pieza de color contrario
        }
    }

    Posicion diagDer = { f + dir, c + 1 };
    if (diagDer.esValida()) {
        Pieza* p = tab.obtenerPieza(diagDer.fil, diagDer.col);
        if (p != nullptr && p->getColor() != this->color) {
            movs.push_back(diagDer);  
        }
    }

    // Devolvemos el vector con todos los movimientos validos encontrados
    return movs;
}
