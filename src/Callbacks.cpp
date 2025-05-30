
#include "Callbacks.h"
#include "Mundo.h"
#include <stdlib.h> // Necesario para exit()
#include <iostream>

Mundo mundo;

void displayGrafico(int* argc, char** argv) {
	//Inicializar el gestor de ventanas GLUT
	//y crear la ventana
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1920, 1080); // Pantalla completa
	glutCreateWindow("Enroque Digital");


	//habilitar luces y definir perspectiva
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glLoadIdentity();

	mundo.Inicializa();

	registarCallbacks();


	//pasarle el control a GLUT,que llamara a los callbacks
	glutMainLoop();
}

void registarCallbacks() {

	//Registrar los callbacks
	glutDisplayFunc(OnDraw);
	glutTimerFunc(25, OnTimer, 0);//le decimos que dentro de 25ms llame 1 vez a la funcion OnTimer()
	glutKeyboardFunc(OnKeyboardDown);
	glutMouseFunc(OnMouseClick); // Registrar el callback para clics del mouse
	glutReshapeFunc(OnReshape);  //Mantener la ventana con las dimensiones dadas
}

void OnDraw(void)
{
	//Borrado de la pantalla	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Para definir el punto de vista
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	mundo.Draw();

	//no borrar esta linea ni poner nada despues
	glutSwapBuffers();
}
void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{
	//poner aqui el código de teclado
	if (key == 'E' || key == 'e') {
		std::cout << "FIN DEL PROGRAMA." << std::endl;
		exit(0); // Cierra el programa
	}

	mundo.OnKeyboardDown(key);

	glutPostRedisplay();
}

void OnTimer(int value)
{
	//poner aqui el código de animacion

		//no borrar estas lineas
	glutTimerFunc(25, OnTimer, 0);
	glutPostRedisplay();
}

//Trackea los clics del ratón
void OnMouseClick(int button, int state, int x, int y) {

	mundo.clicPos(button, state, x, y);
}


// Remodela la ventana si es necesario sin cambiar el tamaño de los objetos y manteniendo sus proporciones.
void OnReshape(int width, int height) {
	mundo.Reshape(width, height);
	
}