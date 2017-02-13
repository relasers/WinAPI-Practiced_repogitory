//  ========================================================================
//  AUTHOR:  Ramakrishnan Mukundan
//  BOOK:    Advanced Methods in Computer Graphics 
//           - With examples in OpenGL,  Springer, 2012.
//
//  FILE NAME: CatmullRom.cpp
//  DESCRIPTION:
//		This code is part of the supplementary material for Chapter 7.
//		This program demonstrates the polynomial interpolation theorem
//		presented in Section 7.1. 
//      (Ref. Page 175)
//	        Interactively specify the points using the mouse. The curve 
//          is updated as and when a new point is input.
//          An existing point can be changed by clicking on it with the 
//          right mouse button and dragging it to a new location.
//          Press 'c' to clear the screen and start over again.
//          Maximum number of points  = 20.
//  ========================================================================
//  THE SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS",  WITHOUT WARRANTY OF ANY
//  KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//  MERCHANTABILITY, FITNESS FOR A  PARTICULAR PURPOSE AND  NONINFRINGEMENT.
//  IN NO EVENT SHALL  THE AUTHOR OR THE PUBLISHER BE LIABLE FOR  ANY CLAIM,
//  DAMAGES OR  OTHER LIABILITY,  WHETHER IN AN  ACTION OF CONTRACT, TORT OR
//  OTHERWISE, ARISING FROM,  OUT OF OR  IN CONNECTION  WITH THE SOFTWARE OR
//  THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//  ========================================================================

#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

int windowWidth = 800, windowHeight = 600;
float x[20], y[20];  //Maximum of 20 points
int numPts = 0, indx = -1;

//--Display: The main display module --------------------------------- 
void display(void)
{
	float xcr, ycr;   //Points on the Catmull-Rom spline
	float dx, dy;     //tangent components
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPointSize(6.0);
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < numPts; i++)
		glVertex2f(x[i], y[i]);
	glEnd();

	if (numPts > 3)
	{
		glColor3f(1., 0., 0.);
		glBegin(GL_LINES); //draw tangents
		for (int i = 1; i < numPts - 1; i++) {
			dx = 0.2*(x[i + 1] - x[i - 1]);
			dy = 0.2*(y[i + 1] - y[i - 1]);
			glVertex2f(x[i] - dx, y[i] - dy);
			glVertex2f(x[i] + dx, y[i] + dy);
		}
		glEnd();

		glColor3f(0., 0., 1.);
		glBegin(GL_LINE_STRIP);
		for (int i = 1; i < numPts - 2; i++)
		{
			for (int k = 0; k < 50; k++) {    //50 points
				float t = k*0.02;  //Interpolation parameter
								   //--Eq. (7.34)--
				xcr = x[i] + 0.5*t*(-x[i - 1] + x[i + 1])
					+ t*t*(x[i - 1] - 2.5*x[i] + 2 * x[i + 1] - 0.5*x[i + 2])
					+ t*t*t*(-0.5*x[i - 1] + 1.5*x[i] - 1.5*x[i + 1] + 0.5*x[i + 2]);
				ycr = y[i] + 0.5*t*(-y[i - 1] + y[i + 1])
					+ t*t*(y[i - 1] - 2.5*y[i] + 2 * y[i + 1] - 0.5*y[i + 2])
					+ t*t*t*(-0.5*y[i - 1] + 1.5*y[i] - 1.5*y[i + 1] + 0.5*y[i + 2]);
				glVertex2f(xcr, ycr);
			}
		}
		glEnd();
	}
	glFlush();
}
//---Returns the index of a point picked using the mouse---------------------
int picked(float xp, float yp)
{
	for (int i = 0; i < numPts; i++)
		if (fabs(xp - x[i]) < 0.2  &&  fabs(yp - y[i]) < 0.2) return i;
	return -1;
}

//---Mouse drag callback to modify an existing point on the curve ------------
void mouseDrag(int xp, int yp) {
	float xWorld = (float)(xp*8.0) / windowWidth;
	float yWorld = (float)(windowHeight - yp)*6.0 / windowHeight;
	if (indx > -1)
	{
		x[indx] = xWorld;
		y[indx] = yWorld;
	}
	glutPostRedisplay();
}

//----------- Mouse callback to accept input points ------------------------
void mouse(int button, int state, int xp, int yp)
{
	float xWorld = (float)(xp*8.0) / windowWidth;
	float yWorld = (float)(windowHeight - yp)*6.0 / windowHeight;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && numPts < 20)
	{
		x[numPts] = xWorld;
		y[numPts] = yWorld;
		numPts++;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)  //Pick
		indx = picked(xWorld, yWorld);
	glutPostRedisplay();
}

//---Keyboard event callback -----------------------------------------------
void keyboard(unsigned char key, int x, int y)
{
	if (key == 'c' || key == 'C') numPts = 0;
	glutPostRedisplay();
}

//-------Initializes drawing parameters ------------------------------------
void initialize(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 8.0, 0.0, 6.0);
}

//----------- Reshape function callback -----------------------------------
void reshape(int wid, int hgt)
{
	windowWidth = wid;
	windowHeight = hgt;
	glViewport(0, 0, wid, hgt);
}

//  ------- Main: Initialize glut window and register call backs ---------- 
void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Catmull-Rom Spline");
	initialize();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseDrag);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
}

