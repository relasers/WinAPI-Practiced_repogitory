#pragma once
#include <cmath>
#include <gl/glut.h>

#ifndef PI
#define PI 3.141592
#endif

static void RandGear(float size, int gearangle) {

	glPushMatrix();
	{
		glRotatef(gearangle, 0, 0, 1);
		glutSolidTorus(size / 10, size - size / 10, 20, 20);
	}
	glPopMatrix();
	
	for (int i = 0; i < 12; ++i) {
		int angle = 360 / 12 * i + gearangle;
		glPushMatrix();
		{
			glRotatef(angle, 0, 0, 1);
			glTranslatef(size,0,0);
			glutSolidCube(size / 5);
		}
		glPopMatrix();
	}
}
static void RandPropeller(float size,float sticklength, float canvaswidth,float canvasheight, int gearangle) {
	glPushMatrix();
	{
		glPushMatrix();
		{
			glTranslatef(0, 0, sticklength/2);
			glScalef(1, 1, sticklength);
			glutSolidTorus(1, 2, 20, 20);
		}
		glPopMatrix();

		for (int i = 0; i < 6; ++i) {
			int angle = 360 / 6 * i + gearangle;

			glPushMatrix();
			{
				glRotatef(angle, 0, 0, 1);
				glTranslatef(canvaswidth /2, 0, 0);
				glScalef(canvaswidth,1, canvasheight);
				glRotatef(90,1,0,0);
				glutSolidCube(1);
				glutWireCube(1);
			}
			glPopMatrix();
		}


	}
	glPopMatrix();
}

static void RandGettling(float size, float barrellength,float barrelradius,int gearangle) {
	
	glPushMatrix();
	{
		glutWireCube(size*0.5);
		glutWireCube(size*0.4);
		glutSolidCube(size*0.35);
		RandGear(size*0.35,gearangle);

		glPushMatrix();
		{
			glTranslatef(0, 0, barrellength/2);
			glRotatef(gearangle,0,0,1);
			glutSolidTorus(1, barrelradius*3.5, 20, 20);
			glRotatef(-gearangle, 0, 0, 1);
			glTranslatef(0, 0, barrellength / 2);
			glRotatef(gearangle, 0, 0, 1);
			glutSolidTorus(1, barrelradius * 3.5, 20, 20);
			glRotatef(-gearangle, 0, 0, 1);
			glTranslatef(0, 0, barrellength / 2);
			glRotatef(gearangle, 0, 0, 1);
			glutSolidTorus(2, barrelradius * 3.5, 20, 20);
			glRotatef(-gearangle, 0, 0, 1);
		}
		glPopMatrix();

		for (int i = 0; i < 6; ++i) {
			glPushMatrix();
			{
				int angle = 60*i + gearangle;
				glTranslatef(0, 0, barrellength);
				glRotatef(angle,0,0,1);
				glTranslatef(barrelradius*2,0,0);
				glScalef(1, 1, barrellength);
				glutSolidTorus(1, barrelradius, 20, 20);
			}
			glPopMatrix();

		}
		
	}
	glPopMatrix();
}

static void RandPiston(float barrellength,float barrelradius, float gearangle) {

	glPushMatrix();
	{
		glPushMatrix();
		glutWireCone(barrelradius, barrellength,8,8 );
		//glutSolidCone(barrelradius*0.75, barrellength*1.25, 8, 8);
		glutSolidCone(barrelradius*0.5, barrellength*1.5, 8, 8);
		glPopMatrix();
	

		glPushMatrix();
		glTranslatef(0,0,barrellength*0.25+sin(gearangle*PI/180.0)*barrellength*0.25);
		glRotatef(gearangle,0,0,1);
		glutSolidTorus(1,barrelradius,20,6);
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(0, 0, barrellength*0.25 + cos(gearangle*PI / 180.0)*barrellength*0.25);
		glRotatef(-gearangle, 0, 0, 1);
		glutSolidTorus(1, barrelradius*0.75, 20, 6);
		glPopMatrix();
	}
	glPopMatrix();
}

static void RandClock(float stringlength, float clockradius, float gearangle) {

	glPushMatrix();
	{
		float angle = sin(gearangle*PI / 180.0)*clockradius*0.5;
		glPushMatrix();
		{
			glTranslatef(0, 0, stringlength);
			glScalef(1, 1, stringlength);
			glutSolidTorus(1, 5, 20, 20);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(0, 0, stringlength + clockradius);
			glRotatef(90, 1, 0, 0);
			glPushMatrix();
			{

			}
			glPopMatrix();

			RandGear(clockradius, gearangle);
			RandGear(clockradius*0.7, -gearangle);

			// rand core
			glRotatef(gearangle, 0, 1, 0);
			glColor3f(1.0, 0.0, 0.0);
			glutSolidSphere(clockradius*0.5 - angle*0.01, 40, 40);
			glColor3f(1.0, 1.0, 0.5);
			glLineWidth(5.0);
			glutWireSphere(clockradius*0.5 + angle*0.02, 8, 8);
			glLineWidth(1.0);
			glColor3f(1.0, 1.0, 1.0);
		}
		
		glPopMatrix();
			
	}
	glPopMatrix();
}

static void RandPipe(float length, float radius) {

	glPushMatrix();
	{
		glPushMatrix();
		{
			glScalef(1, 1, length);
			glutSolidTorus(1, radius*0.8, 20, 20);
		}
		glPopMatrix();

		glutSolidTorus(radius*0.5, radius, 20, 20);
		glTranslatef(0, 0, length*0.5);
		glutSolidTorus(radius*0.5, radius, 20, 20);
		glTranslatef(0, 0, length*0.5);
		glutSolidTorus(radius*0.5, radius, 20, 20);

		glTranslatef(0, 0, -length*1.5);
		glutSolidTorus(radius*0.5, radius, 20, 20);
		glTranslatef(0, 0, -length*0.5);
		glutSolidTorus(radius*0.5, radius, 20, 20);
	}
	glPopMatrix();


}

static void RandColumn(float radius, float length){

	glPushMatrix();
	{
		glBegin(GL_QUADS);
		//Top
		glNormal3f(0,1,0);
		glVertex3f(radius, length, -radius);
		glVertex3f(-radius, length, -radius);
		glVertex3f(-radius, length, radius);
		glVertex3f(radius, length, radius);
		//bottom
		glNormal3f(0, -1, 0);
		glVertex3f(radius, -length, radius);
		glVertex3f(-radius, -length, radius);
		glVertex3f(-radius, -length, -radius);
		glVertex3f(radius, -length, -radius);
		// near
		glNormal3f(0, 0, 1);
		glVertex3f(radius, length, radius);
		glVertex3f(-radius, length, radius);
		glVertex3f(-radius, -length, radius);
		glVertex3f(radius, -length, radius);
		//far
		glNormal3f(0, 0, -1);
		glVertex3f(radius, -length, -radius);
		glVertex3f(-radius, -length, -radius);
		glVertex3f(-radius, length, -radius);
		glVertex3f(radius, length, -radius);
		//left
		glNormal3f(-1, 0, 0);
		glVertex3f(-radius, length, radius);
		glVertex3f(-radius, length, -radius);
		glVertex3f(-radius, -length, -radius);
		glVertex3f(-radius, -length, radius);
		//right
		glNormal3f(1, 0, 0);
		glVertex3f(radius, length, -radius);
		glVertex3f(radius, length, radius);
		glVertex3f(radius, -length, radius);
		glVertex3f(radius, -length, -radius);

		glEnd();
	

		glPushMatrix();
		{
			glTranslatef(radius, 0, radius);
			glRotatef(90, 1, 0, 0);
			RandPipe(length, length*0.03);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(-radius, 0, -radius);
			glRotatef(90, 1, 0, 0);
			RandPipe(length, length*0.03);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(radius, 0, -radius);
			glRotatef(90, 1, 0, 0);
			RandPipe(length, length*0.03);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(-radius, 0, radius);
			glRotatef(90, 1, 0, 0);
			RandPipe(length, length*0.03);
		}
		glPopMatrix();
		
	
	}
	glPopMatrix();


}

static void RandCurvedgrid(float x, float z, float height)
{

	float points[3][4][3] = {
		{
			{ -x,		0,-z },
			{ -x / 2 ,	height,-z },
			{ x / 2,	height,-z },
			{ x,		0,-z }
		},
		{
			{ -x,		0,0 },
			{ -x / 2,	height,0 },
			{ x / 2,	height,0 },
			{ x,		0,0 }
		},
		{
			{ -x,		0,z },
			{ -x / 2,	height,z },
			{ x / 2,	height,z },
			{ x,		0,z }
		}

	};

	glMap2f(GL_MAP2_VERTEX_3,
		0.0, 1.0, 3, 4,
		0.0, 1.0, 12, 3,
		&points[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	// grid for curve drawing
	glMapGrid2f(10, 0.0, 1.0,
		10, 0.0, 1.0);

	// connect line to grid
	glEvalMesh2(GL_LINE, 0, 10, 0, 10);

}

static void RandEnergyCubes(float radius, int gearangle) {

	glPushMatrix();
	{
		float angle = sin(gearangle*PI / 180.0)*radius*0.5;
		glLineWidth(2.0);
		glTranslatef(radius, radius, radius);
		glRotatef(gearangle, 1, 1, 1);
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				for (int k = 0; k < 3; ++k) {
					glutWireCube(-radius + angle);
					glTranslatef(-radius, 0, 0);
				}
				glTranslatef(radius*3, 0, -radius);
			}
			glTranslatef(0, -radius, radius*3);
		}
		glLineWidth(1.0);
	}
	glPopMatrix();

}