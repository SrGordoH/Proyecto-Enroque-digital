#include "Sonido.h"
#include "ETSIDI.h"

void Sonido::reproducirMovimiento() {
    ETSIDI::play("sonidos/movimiento.wav");
}

void Sonido::reproducirJaqueMate() {
    ETSIDI::play("sonidos/jaquemate.wav");
}