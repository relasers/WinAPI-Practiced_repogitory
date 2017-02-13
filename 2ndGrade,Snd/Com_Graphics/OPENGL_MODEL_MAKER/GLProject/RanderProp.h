#pragma once
#include "stdafx.h"

#ifndef PI
#define PI					3.141592f
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
		glTranslatef(0,0,barrellength*0.25+sin(gearangle*PI /180.0)*barrellength*0.25);
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