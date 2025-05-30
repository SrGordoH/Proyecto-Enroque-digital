#include "Pieza.h"
#include "Tablero_logica.h"

void Pieza::SetPos(int fil, int col)
{
    pos.fil = fil;
    pos.col = col;
    coords = pos.centro_en_coords();
}

std::string Pieza::nombrePieza(Pieza::tipo_t tipo) const {
    switch (tipo) {
    case Pieza::tipo_t::PEON: return "Peon";
    case Pieza::tipo_t::CABALLO: return "Caballo";
    case Pieza::tipo_t::ALFIL: return "Alfil";
    case Pieza::tipo_t::TORRE: return "Torre";
    case Pieza::tipo_t::DAMA: return "Dama";
    case Pieza::tipo_t::REY: return "Rey";
    default: return "Desconocida";
    }
}


bool Pieza::esMovimientoLegalConJaque(Pieza* piezaDestino, Posicion destino, Tablero_logica& tab) {
    Posicion origen = getPos(); // guardamos donde esta originalmente 
    Posicion posOriginalDestino; // por si hay una pieza en el destino

    // guardamos la posicion de la pieza que esta en destino si hay una
    if (piezaDestino) posOriginalDestino = piezaDestino->getPos();

    if (piezaDestino) piezaDestino->SetPos(-11, -111); // quitamosla pieza capturada 

    SetPos(destino.fil, destino.col); // movemos esta pieza a la nueva posicion

    bool enJaque = estaEnJaque(tab); // verificamos si tras mover, nuestro rey esta en jaque

    // revertimos los cambios de posicion
    SetPos(origen.fil, origen.col);
    if (piezaDestino) piezaDestino->SetPos(posOriginalDestino.fil, posOriginalDestino.col);

    return !enJaque;
}



bool Pieza::estaEnJaque(Tablero_logica& tab) const {
    Posicion reyPos = tab.obtenerReyPos(color);
    for (Pieza* pieza : tab.obtenerPiezasOponente(color)) {
        auto posiblesMovs = pieza->movimientosValidos(tab, false);
        for (const Posicion& mov : posiblesMovs) {
            if (mov.fil == reyPos.fil && mov.col == reyPos.col) {
                return true;
            }
        }
    }
    return false;
}



void Pieza::Dibuja(double ancho_casilla) const {
    if (!sprite) return;
    sprite->setPos((float)(coords.x - ancho_casilla / 2), (float)(coords.y - ancho_casilla / 2));
    sprite->setSize((float)ancho_casilla, (float)ancho_casilla); // tamano acorde a casilla
   
    sprite->draw();                              // dibuja el sprite
   // sprite->setCenter(0, 0);         // posicion central del sprite
   
}

void Pieza::DibujaMovValidos(double ancho_casilla) const {
    

    for (const auto& m : movs_validos) {
        Coords2D coord = m.esquinainf_en_coords();
        ETSIDI::Sprite sprite("imagenes/MovimientosValidos.png");
        sprite.setCenter(0, 0);
        sprite.setPos(coord.x, coord.y);
        sprite.setSize((float)ancho_casilla, (float)ancho_casilla);
        sprite.draw();
    }
}




