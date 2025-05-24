#include "Pieza.h"
#include "Tablero_logica.h"

void Pieza::SetPos(int fil, int col)
{
    pos.fil = fil;
    pos.col = col;
    coords = pos.centro_en_coords();
}


bool Pieza::esMovimientoLegalConJaque(Pieza* piezaDestino, Posicion destino, Tablero_logica& tab) {
    Posicion posOriginal = pos;
    Pieza* piezaCapturada = tab.obtenerPieza(destino);
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
                Pieza* otraPieza = tab.obtenerPieza(p);
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

void Pieza::Dibuja(float ancho_casilla) const {
    if (!sprite) return;
    sprite->setPos(coords.x-ancho_casilla/2, coords.y - ancho_casilla / 2);
    sprite->setSize(ancho_casilla, ancho_casilla); // tamano acorde a casilla
   
    sprite->draw();                              // dibuja el sprite
   // sprite->setCenter(0, 0);         // posicion central del sprite
   
}

void Pieza::DibujaMovValidos(float ancho_casilla) const {
    std::vector<ETSIDI::Sprite*> sprites_mov;
    std::vector<Coords2D> coordsValidas;

    for (const auto& m : movs_validos) {
        coordsValidas.push_back(m.esquinainf_en_coords());
        sprites_mov.push_back(new ETSIDI::Sprite("imagenes/MovimientosValidos.png"));
    }

    for (int i = 0; i < movs_validos.size(); i++) {
        sprites_mov[i]->setCenter(0, 0);
        sprites_mov[i]->setPos(coordsValidas[i].x, coordsValidas[i].y);
        sprites_mov[i]->setSize(ancho_casilla, ancho_casilla);
        sprites_mov[i]->draw();
    }

    for (auto s : sprites_mov) delete s;

}




