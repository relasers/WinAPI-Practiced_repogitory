#pragma once
#include <cmath>
#include <gl/glut.h>

#ifndef PI
#define PI 3.141592f
#endif

#ifndef COLOR_TABLE
#define COLOR_TABLE
#define COLOR255 0.004f
#define COLOR_BLACK		{0.0f,0.0f,0.0f}
#define COLOR_WHITE		{1.0f,1.0f,1.0f}
#define COLOR_WINE		{COLOR255*110,COLOR255*47,COLOR255*59}
#define COLOR_GOLD		{COLOR255*253,COLOR255*217,COLOR255*120}
#define COLOR_WOOD		{COLOR255*96,COLOR255*85,COLOR255*66}
#define COLOR_BSILVER	{COLOR255*170,COLOR255*170,COLOR255*170}
#define COLOR_DSILVER	{COLOR255*187,COLOR255*187,COLOR255*187}
#define COLOR_JADE		{COLOR255*128,COLOR255*172,COLOR255*170}
#define COLOR_RED		{1.0,0.0,0.0}
#define COLOR_YELLOW	{1.0,1.0,0.0}
#define COLOR_EGGYOLK	{1.0,COLOR255*169,COLOR255*25}

#endif


#ifndef RANDER_FUNCTION
#define RANDER_FUNCTION
static void RandGear(float size, int gearangle,Vec3f color,float alpha) {

	glColor4f(color.x,color.y,color.z,alpha);

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
static void RandPropeller(float size,float sticklength, float canvaswidth,float canvasheight, int gearangle,
Vec3f stickcolor, Vec3f canvascolor, float alpha
) {
	glPushMatrix();
	{
		glPushMatrix();
		{
			glTranslatef(0, 0, sticklength/2);
			glScalef(1, 1, sticklength);
			glColor4f(stickcolor.x,stickcolor.y,stickcolor.z,alpha);
			glutSolidTorus(1, 2, 20, 20);
		}
		glPopMatrix();

		glColor4f(canvascolor.x, canvascolor.y, canvascolor.z, alpha);
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

static void RandGettling(float size, float barrellength,float barrelradius,int gearangle,
	Vec3f BaseColor,Vec3f WireColor, Vec3f Barrelcolor,Vec3f gearcolor,float alpha) {
	
	glPushMatrix();
	{
		glColor4f(WireColor.x,WireColor.y,WireColor.z,alpha);
		glutWireCube(size*0.5);
		glutWireCube(size*0.4);
		glColor4f(BaseColor.x, BaseColor.y, BaseColor.z, alpha);
		glutSolidCube(size*0.35);
		RandGear(size*0.35,gearangle,gearcolor,alpha);

		glPushMatrix();
		{
			glColor4f(gearcolor.x, gearcolor.y, gearcolor.z,alpha);
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

		glColor4f(Barrelcolor.x, Barrelcolor.y, Barrelcolor.z, alpha);

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

static void RandPiston(float barrellength,float barrelradius, float gearangle,Vec3f Basecolor,Vec3f Wirecolor,float alpha) {

	glPushMatrix();
	{
		glPushMatrix();
		glColor4f(Basecolor.x, Basecolor.y, Basecolor.z, alpha);
		glutWireCone(barrelradius, barrellength,8,8 );
		glutSolidCone(barrelradius*0.5, barrellength*1.5, 8, 8);
		glPopMatrix();
	

		glPushMatrix();
		glTranslatef(0,0,barrellength*0.25+sin(gearangle*PI/180.0)*barrellength*0.25);
		glRotatef(gearangle,0,0,1);
		glColor4f(Wirecolor.x, Wirecolor.y, Wirecolor.z,alpha);
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

static void RandClock(float stringlength, float clockradius, float gearangle,
	Vec3f stickcolor,Vec3f Bgearcolor,Vec3f Sgearcolor,Vec3f Corecolor,Vec3f CoreLinecolor, float alpha) {

	glPushMatrix();
	{
		float angle = sin(gearangle*PI / 180.0)*clockradius*0.5;
		glPushMatrix();
		{
			glTranslatef(0, 0, stringlength);
			glScalef(1, 1, stringlength);

			glColor4f(stickcolor.x,stickcolor.y,stickcolor.z,alpha);
			glutSolidTorus(1, 5, 20, 20);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(0, 0, stringlength + clockradius);
			glRotatef(90, 1, 0, 0);


			RandGear(clockradius, gearangle,Bgearcolor,alpha);
			RandGear(clockradius*0.7, -gearangle,Sgearcolor,alpha);

			// rand core
			glRotatef(gearangle, 0, 1, 0);
			glColor4f(Corecolor.x, Corecolor.y, Corecolor.z,alpha);
			glutSolidSphere(clockradius*0.5 - angle*0.01, 40, 40);
			glColor4f(CoreLinecolor.x, CoreLinecolor.y, CoreLinecolor.z,alpha);
			glLineWidth(5.0);
			glutWireSphere(clockradius*0.5 + angle*0.02, 8, 8);
			glLineWidth(1.0);
		}
		
		glPopMatrix();
			
	}
	glPopMatrix();
}

static void RandPipe(float length, float radius,Vec3f barrelcolor,Vec3f yokecolor,float alpha) {

	glPushMatrix();
	{
		glPushMatrix();
		{
			glScalef(1, 1, length);
			glColor4f(barrelcolor.x,barrelcolor.y,barrelcolor.z,alpha);
			glutSolidTorus(1, radius*0.8, 20, 20);
		}
		glPopMatrix();

		glColor4f(yokecolor.x, yokecolor.y, yokecolor.z, alpha);

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

static void RandColumn(float radius, float length,Vec3f columncolor,Vec3f barrelcolor,Vec3f yokecolor,float alpha){

	glPushMatrix();
	{
		glColor4f(columncolor.x,columncolor.y,columncolor.z,alpha);
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
			RandPipe(length, length*0.03,barrelcolor,yokecolor,alpha);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(-radius, 0, -radius);
			glRotatef(90, 1, 0, 0);
			RandPipe(length, length*0.03, barrelcolor, yokecolor, alpha);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(radius, 0, -radius);
			glRotatef(90, 1, 0, 0);
			RandPipe(length, length*0.03, barrelcolor, yokecolor, alpha);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(-radius, 0, radius);
			glRotatef(90, 1, 0, 0);
			RandPipe(length, length*0.03, barrelcolor, yokecolor, alpha);
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

static void RandEnergyCubes(float radius, int gearangle,Vec3f color, float alpha) {

	glPushMatrix();
	{
		glColor4f(color.x,color.y,color.z,alpha);
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

static void RandQuad(Vec3f pos, float fScale, bool isXY) {
	glPushMatrix();
	{
		glTranslatef(pos.x, pos.y, pos.z);

		float fx = fScale * 0.5f;
		float fy = (isXY) ? fScale * 0.5f : 0;
		float fz = (isXY) ? 0 : fScale * 0.5f;

		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-fx, +fy, -fz);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-fx, -fy, +fz);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(+fx, -fy, +fz);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(+fx, +fy, -fz);
		}
		glEnd();


	}
	glPopMatrix();
}


#endif