#pragma once
class Sonido {
private:
    static bool musicaReproducida;
public:
    static void iniciarMusicaMenu();
    static void detenerMusica();
    static void reproducirJaque();
    static void reproducirMovimiento();
    static void reproducirJaqueMate();
};
