#include "Func.h"


//

void main(int argc, char *argv[])
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("4section");

	glutDisplayFunc(drawScene);

	glutMouseFunc(Mouse);

	glutTimerFunc(100, TimerFunction, 1);

	glutReshapeFunc(Reshape);
	glutMainLoop();
}

