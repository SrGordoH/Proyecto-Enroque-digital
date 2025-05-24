#include "Tablero_logica.h"

void Tablero_logica::inicializarTablero(const Tablero& tablero) {  // Aqui agregamos el nombre de la clase
    // === PEONES ===
    for (int i = 0; i < 5; ++i) {
        piezas.push_back(new Peon(tablero, true));  // Blancos
        piezas.push_back(new Peon(tablero, false)); // Negros
    }

    // === TORRES ===
    piezas.push_back(new Torre(tablero, true));  // Blanca
    piezas.push_back(new Torre(tablero, false)); // Negra

    // === CABALLOS ===
    piezas.push_back(new Caballo(tablero, true));
    piezas.push_back(new Caballo(tablero, false));

    // === ALFILES ===
    piezas.push_back(new Alfil(tablero, true));
    piezas.push_back(new Alfil(tablero, false));

    // === DAMAS ===
    piezas.push_back(new Dama(tablero, true));
    piezas.push_back(new Dama(tablero, false));

    // === REYES ===
    piezas.push_back(new Rey(tablero, true));
    piezas.push_back(new Rey(tablero, false));

    //usamos un vector de piezas que guardamos usando memoria dinamica cada una al final de las que habia previamente
}

void Tablero_logica::setearPosicionesIniciales(int modo) {
    if (modo == 0) {
        //Modo Petty

        // === Peones ===
        for (int i = 0; i < 5; ++i) {
            piezas[i * 2]->SetPos(2, i + 1);     // Peones negros (fila 2)
            piezas[i * 2 + 1]->SetPos(5, i + 1); // Peones blancos (fila 5)
        }

        piezas[10]->SetPos(1, 5); // Torre negra
        piezas[11]->SetPos(6, 5); // Torre blanca

        piezas[12]->SetPos(1, 4); // Caballo negro
        piezas[13]->SetPos(6, 4); // Caballo blanco

        piezas[14]->SetPos(1, 3); // Alfil negro
        piezas[15]->SetPos(6, 3); // Alfil blanco

        piezas[16]->SetPos(1, 1); // Dama negra
        piezas[17]->SetPos(6, 1); // Dama blanca

        piezas[18]->SetPos(1, 2); // Rey negro
        piezas[19]->SetPos(6, 2); // Rey blanco

    }
    else if (modo == 1) {
        //Modo Reyes en esquinas opuestas

        // === Peones ===
        for (int i = 0; i < 5; ++i) {
            piezas[i * 2]->SetPos(2, i + 1);     // Peones negros (fila 2)
            piezas[i * 2 + 1]->SetPos(5, i + 1); // Peones blancos (fila 5)
        }

        piezas[10]->SetPos(1, 5); // Torre negra
        piezas[11]->SetPos(6, 1); // Torre blanca

        piezas[12]->SetPos(1, 4); // Caballo negro
        piezas[13]->SetPos(6, 2); // Caballo blanca

        piezas[14]->SetPos(1, 3); // Alfil negro
        piezas[15]->SetPos(6, 3); // Alfil blanco

        piezas[16]->SetPos(1, 2); // Dama negra
        piezas[17]->SetPos(6, 4); // Dama blanca

        piezas[18]->SetPos(1, 1); // Rey negro
        piezas[19]->SetPos(6, 5); // Rey blanco
    }
}


Pieza* Tablero_logica::obtenerPieza(Posicion casilla) const {
    for (Pieza* p : piezas) {
        if (!p) continue;  //verificamos que exista
        Posicion pos = p->getPos();
        if (pos.fil == casilla.fil && pos.col == casilla.col) {
            return p;
        }
    }
    return nullptr; // No hay pieza en esa posicion
}


Posicion Tablero_logica::obtenerReyPos(bool color) {
    // Recorremos todo el tablero para encontrar la pieza de tipo Rey con el color especificado
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 6; ++j) {
            Pieza* pieza = obtenerPieza(Posicion(i, j));  // Obtener la pieza en la posicion (i, j)

            if (pieza != nullptr && pieza->getColor() == color && pieza->getTipo() == Pieza::tipo_t::REY) {
                // Si encontramos una pieza del color buscado y es un Rey, retornamos su posicion
                return Posicion{ i, j };  // Posicion de la pieza encontrada
            }
        }
    }
    return Posicion{ -1, -1 };  // Posicion invalida si no se encuentra el rey


}

vector<Pieza*> Tablero_logica::obtenerPiezasOponente(bool color) const {
    vector<Pieza*> piezasOponente;

    for (Pieza* p : piezas) {
        if (p != nullptr && p->getColor() != color) {
            piezasOponente.push_back(p);
        }
    }

    return piezasOponente;
}


bool Tablero_logica::estaEnJaqueMate(bool color) {
    for (Pieza* p : piezas) {
        if (p->getColor() == color) {
            std::vector<Posicion> posibles = p->movimientosValidos(*this);
            for (const Posicion& destino : posibles) {
                Pieza* piezaDestino = obtenerPieza(destino);
                if (p->esMovimientoLegalConJaque(piezaDestino, destino, *this)) {
                    return false; // Si hay al menos un movimiento legal que evita el jaque, no es jaque mate
                }
            }
        }
    }
    return true; 
}

bool Tablero_logica::estaEnJaque(bool color) {
    // Se obtiene la posicion del rey del jugador del color actual
    Posicion reyPos = obtenerReyPos(color);

    // Se recorre la lista de piezas del oponente
    for (Pieza* pieza : piezas) {
        if (!pieza || pieza->getColor() == color)
            continue; // Se ignoran piezas del mismo color

        // Se obtienen los movimientos validos de la pieza enemiga
        vector<Posicion> amenazas = pieza->movimientosValidos(*this);

        // Se verifica si alguna pieza enemiga puede atacar al rey
        for (const Posicion& p : amenazas) {
            if (p.fil == reyPos.fil && p.col == reyPos.col) {
                return true; // El rey esta siendo amenazado
            }
        }
    }

    return false; // No hay amenazas, el rey no esta en jaque
}


void Tablero_logica::guardarMovimiento(Pieza* p, Posicion origen, Posicion destino, Pieza* capturada) {
    Movimiento m;
    m.pieza = p;
    m.origen = origen;
    m.destino = destino;
    m.capturada = capturada;
    historial.push_back(m);
}

void Tablero_logica::deshacerUltimoMovimiento() {
    if (historial.empty()) return;

    Movimiento m = historial.back();
    historial.pop_back();

    // Revertimos la pieza movida
    m.pieza->SetPos(m.origen.fil, m.origen.col);

    // Restauramos la pieza capturada si habia
    if (m.capturada) {
        piezas.push_back(m.capturada);
    }
}

void Tablero_logica::verificarCoronacion() {
    for (int i = 0; i < piezas.size(); ++i) {
        Pieza* p = piezas[i];

        // Si la pieza es un peon
        if (p && p->getTipo() == Pieza::tipo_t::PEON) {
            Posicion pos = p->getPos();

            // Si el peon blanco llega a la fila 1 o el negro a la fila 6
            if ((p->getColor() && pos.fil == 1) || (!p->getColor() && pos.fil == 6)) {
                const Tablero& t = p->getTablero(); // obtener referencia al tablero

                // Se elimina el peon y se sustituye por una dama
                delete piezas[i];
                piezas[i] = new Dama(t, p->getColor());
                piezas[i]->SetPos(pos.fil, pos.col);
            }
        }
    }
}

bool Tablero_logica::esTablasPorAhogo(bool turnoColor) {
    if (estaEnJaque(turnoColor)) return false;

    for (Pieza* p : piezas) {
        if (p->getColor() == turnoColor) {
            auto movs = p->movimientosValidos(*this);
            for (Posicion& d : movs) {
                Pieza* destino = obtenerPieza(d);
                if (p->esMovimientoLegalConJaque(destino, d, *this)) {
                    return false; // hay al menos un movimiento legal
                }
            }
        }
    }

    return true; // no hay movimientos legales y no esta en jaque
}

void Tablero_logica::notificarMovimiento(Pieza* piezaMovida, Pieza* capturada) {
    if (capturada || piezaMovida->getTipo() == Pieza::tipo_t::PEON)
        movimientosSinCaptura = 0;
    else
        movimientosSinCaptura++;
}


void Tablero_logica::eliminarPieza(Pieza* p) {
    for (auto it = piezas.begin(); it != piezas.end(); ++it) {  //recorremos el vector con indices
        if (*it == p) {  //Pieza encontrada
            delete* it;
            piezas.erase(it);  
            break;       //Salimos tras eliminar
        }
    }
}

bool Tablero_logica::moverPieza(Pieza* pieza, Posicion destino) {
    if (!pieza ) return false; //Si no hay pieza no movemos nada

    std::vector<Posicion> movs = pieza->movimientosValidos(*this);

    // Verificamos si el destino esta en los movimientos validos
    bool esMovimientoValido = false;
    for (const Posicion& p : movs) {
        if (p.fil == destino.fil && p.col == destino.col) {
            esMovimientoValido = true;
            break;
        }
    }

    if (!esMovimientoValido) return false;

    // Obtener la pieza en la posicion de destino
    Pieza* piezaDestino = obtenerPieza(destino);

    // Guardar el movimiento antes de eliminar
    if (piezaDestino && piezaDestino != pieza)
        guardarMovimiento(pieza, pieza->getPos(), destino, piezaDestino);
    else
        guardarMovimiento(pieza, pieza->getPos(), destino, nullptr);


    // Si hay una pieza en destino eliminarla aunque sea de su color
    if(piezaDestino && piezaDestino != pieza) {
        eliminarPieza(piezaDestino);
    }

    pieza->SetPos(destino.fil, destino.col);
    verificarCoronacion();
    cambiarTurno();

    return true; //Devolvemos true si hacemos ese movimiento
}

