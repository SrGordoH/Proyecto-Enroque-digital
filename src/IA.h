#pragma once
#include "Tablero_logica.h"
#include "Pieza.h"
#include "Posicion.h"
#include "Movimiento.h"
#include <vector>

class IA {
private:
    Tablero_logica* logica;
    bool iaColor = 0;
    int valorPieza(Pieza::tipo_t tipo) const;
    float distancia(Posicion a, Posicion b) const;

public:
    void setLogica(Tablero_logica* log) { logica = log; }
    void elegirMejorMovimiento(bool color);
    void MovPiezaIA(bool color);
    Tablero_logica* crearTableroSimulado(Pieza* piezaOriginal, Posicion destino) const;
    int AnalisisBasico(Pieza* p, Posicion b, Tablero_logica* log) const;
    int AnalisisComplejo(Pieza* p, Posicion b, Tablero_logica* log) const;
    bool esCapturaAliada(Pieza* p, Posicion destino) const;
    bool intentarJaqueMate(bool color);
    vector<Movimiento> movimientosLegales(bool color);
    Movimiento mejorMovimientoSimple(bool color);  //Utiliza el analisis basico
    Movimiento mejorMovimientoComplejo(bool color); //Utiliza el analisis complejo
    void elegirMejorMovimientoSimple(bool color); // Utiliza el movimiento simple
    void elegirMejorMovimientoAvanzado(bool color);  // Utiliza el movimiento complejo
};

