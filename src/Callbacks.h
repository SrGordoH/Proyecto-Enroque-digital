#pragma once

#include "Tablero.h"
#include "freeglut.h"

void displayGrafico(int* argc, char** argv);

//los callback, funciones que seran llamadas automaticamente por la glut cuando sucedan eventos
//NO HACE FALTA LLAMARLAS EXPLICITAMENTE
void OnDraw(void); //esta funcion sera llamada para dibujar
void OnTimer(int value); //esta funcion sera llamada cuando transcurra una temporizacion
void OnKeyboardDown(unsigned char key, int x, int y); //cuando se pulse una tecla	
void OnMouseClick(int button, int state, int x, int y); // Función para el clic del mouse
void OnReshape(int width, int height); // función para que se mantenga la ventana con las dimensiones establecidas
void registarCallbacks();