
#include "Callbacks.h"

Tablero tablero;

void displayGrafico(int* argc, char** argv) {
	//Inicializar el gestor de ventanas GLUT
	//y crear la ventana
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Enroque Digital");


	//habilitar luces y definir perspectiva
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glLoadIdentity();

	tablero.Inicializa();

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


	tablero.Draw();
	//no borrar esta linea ni poner nada despues
	glutSwapBuffers();
}
void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{
	//poner aqui el código de teclado

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

	tablero.clicPos(button, state, x, y);
}


// Remodela la ventana si es necesario sin cambiar el tamaño de los objetos y manteniendo sus proporciones.
void OnReshape(int width, int height) {
	//if (width != 800 || height != 800) {
	//	glutReshapeWindow(800, 800); // Forzar que la ventana vuelva a 800x800
	//}
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (GLfloat)width / (GLfloat)height, 1.0, 200.0); //set the perspective (angle of sight, width, height, depth)
	glMatrixMode(GL_MODELVIEW);

}