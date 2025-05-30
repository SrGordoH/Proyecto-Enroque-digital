#include "Tablero_logica.h"
#include "Sonido.h"


void Tablero_logica::inicializarTablero() {  // Aqui agregamos el nombre de la clase
    // Reinicializar partida
    finPartida = false; 
    tablas = false;
    turno = true;

    // === PEONES ===
    for (int i = 0; i < 5; ++i) {
        piezas.push_back(new Peon(true));  // Blancos
        piezas.push_back(new Peon( false)); // Negros
    }

    // === TORRES ===
    piezas.push_back(new Torre(true));  // Blanca
    piezas.push_back(new Torre(false)); // Negra

    // === CABALLOS ===
    piezas.push_back(new Caballo(true));
    piezas.push_back(new Caballo(false));

    // === ALFILES ===
    piezas.push_back(new Alfil(true));
    piezas.push_back(new Alfil(false));

    // === DAMAS ===
    piezas.push_back(new Dama(true));
    piezas.push_back(new Dama(false));

    // === REYES ===
    piezas.push_back(new Rey( true));
    piezas.push_back(new Rey( false));

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
    // Recorremos todas las piezas para encontrar la pieza de tipo Rey con el color especificado
    for (Pieza* p : piezas) {
        if (!p) continue;
        // Si es rey del color dado, devolvemos su posición
        if (p->getTipo() == Pieza::tipo_t::REY && p->getColor() == color) {
            return p->getPos();
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
    if (!estaEnJaque(color)) return false;

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
    Sonido::reproducirJaqueMate();
    printHistorial();  // Cuando se acaba la partida se imprime el historial de la partida
    return true; // NO hay ningún movmiento legal y está en jaque
}

bool Tablero_logica::estaEnJaque(bool color) {
    // Se obtiene la posicion del rey del jugador del color actual
    Posicion reyPos = obtenerReyPos(color);

    // Se recorre la lista de piezas
    for (Pieza* pieza : piezas) {
        if (!pieza || pieza->getColor() == color)
            continue; // Se ignoran piezas del mismo color

        // Se obtienen los movimientos validos de la pieza enemiga
        vector<Posicion> amenazas = pieza->movimientosValidos(*this);

        // Se verifica si alguna pieza enemiga puede atacar al rey
        for (const Posicion& p : amenazas) {
            if (p.fil == reyPos.fil && p.col == reyPos.col) {
                Sonido::reproducirJaque();
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
    if (capturada) {
        for (int i = 0; i < (int)piezas.size(); ++i) {
            if (piezas[i] == capturada) {
                m.indiceCapturada = i;
                piezas[i] = nullptr;      
                break;
            }
        }
    }
    else {
        m.indiceCapturada = -1;
    }

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
        // Insertar en el indice original, o al final si algo raro pasara
        if (m.indiceCapturada >= 0 && m.indiceCapturada <= (int)piezas.size()) {
            piezas.insert(piezas.begin() + m.indiceCapturada, m.capturada);
        }
        else {
            piezas.push_back(m.capturada);
        }
    }
}

void Tablero_logica::verificarCoronacion(bool esIA) {
    for (int i = 0; i < piezas.size(); ++i) {
        Pieza* p = piezas[i];
        
        // Si la pieza es un peon
        if (p && p->getTipo() == Pieza::tipo_t::PEON) {
            Posicion pos = p->getPos();
            bool color = p->getColor();
            // Si el peon blanco llega a la fila 1 o el negro a la fila 6
            if ((!p->getColor() && pos.fil == 1) || (p->getColor() && pos.fil == 6)) {
                if (esIA) {
                    delete piezas[i];
                    piezas[i] = new Dama(false);
                    piezas[i]->SetPos(pos.fil, pos.col);
                } else {
                    // Guardamos la coronación pendiente
                    coronacion = { i, pos, p->getColor(), true };
                }
            }
        }
    }
}

void Tablero_logica::realizarCoronacion(Pieza::tipo_t tipo) {
    if (!coronacion.activa) return;

    int i = coronacion.indexPieza;
    delete piezas[i];

    switch (tipo) {
    case Pieza::tipo_t::DAMA:
        piezas[i] = new Dama(coronacion.color); break;
    case Pieza::tipo_t::TORRE:
        piezas[i] = new Torre(coronacion.color); break;
    case Pieza::tipo_t::ALFIL:
        piezas[i] = new Alfil(coronacion.color); break;
    case Pieza::tipo_t::CABALLO:
        piezas[i] = new Caballo(coronacion.color); break;
    default:
        piezas[i] = new Dama(coronacion.color); // Por defecto una dama
    }

    piezas[i]->SetPos(coronacion.pos.fil, coronacion.pos.col);
    coronacion.activa = false;  // Reseteo 

    cambiarTurno(); // El turno cambia tras coronar
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

bool Tablero_logica::moverPieza(Pieza* pieza, Posicion destino, bool esIA) {
    if (pieza) {

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

        //Comprobacion jaque
        bool legalconJaque = (pieza->esMovimientoLegalConJaque(piezaDestino, destino, *this));
        if (!legalconJaque) return false;

        // Guardar el movimiento antes de eliminar
        guardarMovimiento(pieza, pieza->getPos(), destino,
            piezaDestino ? piezaDestino->clonar() : nullptr); // Si el movimiento es válido se guarda una copia y si no nullptr

        //Comprobar si es el rey del mismo color
        if (piezaDestino != nullptr && piezaDestino->getTipo() == Pieza::tipo_t::REY && piezaDestino->getColor() == pieza->getColor()) {
            eliminarPieza(piezaDestino);
            finPartida = true;
            ganador = !pieza->getColor();
            std::cout << "¡Te comiste a tu propio rey! Ganan las " << (ganador ? "blancas" : "negras") << "\n";
            for (auto& p : piezas) delete p;
            piezas.clear();
            Sonido::reproducirJaqueMate();                //SONIDO DE JAQUE MATE
            return true; // Puede o no mover, pero termina
        }

        // Si hay una pieza en destino eliminarla aunque sea de su color
        if (piezaDestino && piezaDestino != pieza) {
            eliminarPieza(piezaDestino);
        }

        pieza->SetPos(destino.fil, destino.col);
        verificarCoronacion(esIA);
        if (!coronacion.activa)
            cambiarTurno();

        // Evaluamos si el nuevo jugador está en jaque mate
        if (estaEnJaqueMate(turno)) {
            finPartida = true;
            ganador = !turno; // Gana el jugador que acaba de mover
            std::cout << "¡Jaque mate! Ganan las " << (ganador ? "blancas" : "negras") << "\n";
            for (auto& p : piezas) delete p;
            piezas.clear();
        }
        else if (esTablasPorAhogo(turno)) {    // Evaluamos si hay tablas por ahogado
            finPartida = true;
            tablas = true;
            std::cout << "TABLAS. Por rey ahogado." << "\n";
            for (auto& p : piezas) delete p;
            piezas.clear();
        }
        Sonido::reproducirMovimiento();


        return true; //Devolvemos true si hacemos ese movimiento
    }
    else return false;
}

void Tablero_logica::printHistorial() const {
    std::cout << "=== Historial de movimientos ===\n";

    for (size_t i = 0; i < historial.size(); ++i) {
        const Movimiento& m = historial[i];
        std::string tipo = m.pieza->nombrePieza(m.pieza->getTipo());
        std::string color = m.pieza->getColor() ? "Blanca" : "Negra";

        std::cout << i + 1 << ". " << tipo << " " << color
            << " de (" << m.origen.fil << "," << m.origen.col << ")"
            << " a (" << m.destino.fil << "," << m.destino.col << ")";

        if (m.capturada) {
            std::string tipoCapt = m.pieza->nombrePieza(m.capturada->getTipo());
            std::string colorCapt = m.capturada->getColor() ? "Blanca" : "Negra";
            std::cout << " [Captura: " << tipoCapt << " " << colorCapt << "]";
        }

        std::cout << "\n";
    }
}




