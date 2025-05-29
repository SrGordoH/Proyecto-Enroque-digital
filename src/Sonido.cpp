#include "Sonido.h"
#include "ETSIDI.h"

bool Sonido::musicaReproducida = false;

void Sonido::reproducirMovimiento() {
    ETSIDI::play("sonidos/movimiento.wav");
}

void Sonido::reproducirJaqueMate() {
    ETSIDI::play("sonidos/jaquemate.wav");
}

void Sonido::reproducirJaque() {
    ETSIDI::play("sonidos/jaque.wav");
}

void Sonido::iniciarMusicaMenu() {
    if (!musicaReproducida) {
        ETSIDI::playMusica("sonidos/menus.wav", true);
        musicaReproducida = true;
    }
}

void Sonido::detenerMusica() {
    ETSIDI::stopMusica();
    musicaReproducida = false;
}