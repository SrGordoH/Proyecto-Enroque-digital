#include "Peon.h"
using namespace std;

vector<Posicion> Peon::movimientosValidos(Tablero_logica &tab) {
    if (!pos.esValida()) return {};//para evitar piezas fuera del tablero o cualquier otro bug

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
    if (adelante.esValida() && tab.obtenerPieza(adelante) == nullptr) {
        movs.push_back(adelante);  
    }

    Posicion diagIzq = { f + dir, c - 1 };
    if (diagIzq.esValida()) {  // Solo si la posicion esta dentro del tablero
        Pieza* p = tab.obtenerPieza(diagIzq);
        if (p != nullptr) {
            movs.push_back(diagIzq);  //Puedes comerte tus piezas
        }
    }

    Posicion diagDer = { f + dir, c + 1 };
    if (diagDer.esValida()) {
        Pieza* p = tab.obtenerPieza(diagDer);
        if (p != nullptr) {
            movs.push_back(diagDer);  
        }
    }
    movs_validos = movs; 

    // Devolvemos el vector con todos los movimientos validos encontrados
    return movs;
}

Pieza* Peon::clonar() const {
    Peon* copia = new Peon(color);
    copia->SetPos(pos.fil, pos.col);
    return copia;
}

