#include "Pieza.h"
#include "Tablero_logica.h"

void Pieza::SetPos(int fil, int col)
{
    pos.fil = fil;
    pos.col = col;
}

// PEGAR A CONTINUACIÓN:
bool Pieza::esMovimientoLegalConJaque(Pieza* piezaDestino, Posicion destino, Tablero_logica& tab) {
    Posicion posOriginal = pos;
    Pieza* piezaCapturada = tab.obtenerPieza(destino.fil, destino.col);
    this->SetPos(destino.fil, destino.col);

    if (estaEnJaque(tab)) {
        this->SetPos(posOriginal.fil, posOriginal.col);
        if (piezaCapturada != nullptr) {
            piezaCapturada->SetPos(destino.fil, destino.col);
        }
        return false;
    }

    this->SetPos(posOriginal.fil, posOriginal.col);
    if (piezaCapturada != nullptr) {
        piezaCapturada->SetPos(destino.fil, destino.col);
    }
    return true;
}

bool Pieza::estaEnJaque(Tablero_logica& tab) const {
    Posicion reyPos = tab.obtenerReyPos(color);
    for (Pieza* pieza : tab.obtenerPiezasOponente(color)) {
        auto posiblesMovs = pieza->movimientosValidos(tab);
        for (const Posicion& mov : posiblesMovs) {
            if (mov.fil == reyPos.fil && mov.col == reyPos.col) {
                return true;
            }
        }
    }
    return false;
}

bool Pieza::JaqueMate(Tablero_logica& tab) const {
    Posicion reyPos = tab.obtenerReyPos(color);
    for (int df = -1; df <= 1; ++df) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (df == 0 && dc == 0) continue;

            Posicion p = { reyPos.fil + df, reyPos.col + dc };
            if (p.esValida()) {
                Pieza* otraPieza = tab.obtenerPieza(p.fil, p.col);
                if (otraPieza == nullptr || otraPieza->getColor() != color) {
                    if (!estaEnJaque(tab)) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

void Pieza:: Dibuja(float ancho_casilla, float dx, float dy) const {
    if (!sprite) return;

    // Se calcula la posicion en pantalla usando la casilla del tablero y los desplazamientos
    float x = pos.col * ancho_casilla + ancho_casilla / 2.0f + dx;
    float y = pos.fil * ancho_casilla + ancho_casilla / 2.0f + dy;

    sprite->setPos(x, y);                        // posicion central del sprite
    sprite->setSize(ancho_casilla, ancho_casilla); // tamano acorde a casilla
    sprite->draw();                              // dibuja el sprite
}