#include "RGB_CM.h"
#include <iostream>
#include <windows.h>
#include <gl/glut.h>
#include <cmath>
#include "Bitmap.h"


CRGB_CM::CRGB_CM()
{
}


CRGB_CM::~CRGB_CM()
{
}

void CRGB_CM::Rander()
{
	glRotated(30,1,0,0);
	glRotated(45+m_angle, 0, 1, 0);
	glPushMatrix();
	{
		RanderModel();
	}
	glPopMatrix();
	

}

void CRGB_CM::Update()
{
	(++m_angle) %= 360;

	if (m_up_open)
	{
		if (m_up_angle < 90) ++m_up_angle;
	}
	if (!m_up_open) 
	{
		if (m_up_angle > 0) --m_up_angle;
	}
	if (m_face_open)
	{
		if (m_face_angle < 90) ++m_face_angle;
	}
	if (!m_face_open)
	{
		if (m_face_angle > 0) --m_face_angle;
	}
}

void CRGB_CM::KeyInput(unsigned char key, int x, int y)
{
	if (key == 'q' || key == 'Q') 
	{
		m_rander_up = 1 - m_rander_up;
	}
	if (key == 'w' || key == 'W')
	{
		m_rander_face = 1 - m_rander_face;
	}
	if (key == 'a' || key == 'A')
	{
		m_up_open = 1 - m_up_open;
	}
	if (key == 's' || key == 'S')
	{
		m_face_open = 1 - m_face_open;
	}
}

void CRGB_CM::RanderModel()
{
	Vec3f Color[4];
	glPushMatrix();
	{
		glTranslated(-m_size, 0, 0);
		glRotatef(270, 0, 1, 0);
		Color[0] = { 1.0f,1.0f,0.0f };
		Color[1] = { 1.0f,1.0f,1.0f };
		Color[2] = { 1.0f,0.0f,1.0f };
		Color[3] = { 1.0f,0.0f,0.0f };
		glBindTexture(GL_TEXTURE_2D, texture_object[0]);
		RanderSurface(Color);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslated(m_size, 0, 0);
		glRotatef(90, 0, 1, 0);
		Color[0] = { 0.0f,1.0f,1.0f };
		Color[1] = { 0.0f,1.0f,0.0f };
		Color[2] = { 0.0f,0.0f,0.0f };
		Color[3] = { 0.0f,0.0f,1.0f };
		glBindTexture(GL_TEXTURE_2D, texture_object[1]);
		RanderSurface(Color);
	}
	glPopMatrix();

	glPushMatrix();
	if (m_rander_face)
	{
		glTranslated(0, 0, -m_size);
		glRotatef(180, 0, 1, 0);
		Color[0] = { 0.0f,1.0f,0.0f };
		Color[1] = { 1.0f,1.0f,0.0f };
		Color[2] = { 1.0f,0.0f,0.0f };
		Color[3] = { 0.0f,0.0f,0.0f };
		glTranslated(0, -m_size + cos(m_face_angle*PI / 180.0)*m_size, sin(m_face_angle*PI / 180.0)*m_size);
		glRotated(m_face_angle, 1, 0, 0);
		glBindTexture(GL_TEXTURE_2D, texture_object[2]);
		RanderSurface(Color);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslated(0, 0, m_size);
		Color[0] = { 1.0f,1.0f,1.0f };
		Color[1] = { 0.0f,1.0f,1.0f };
		Color[2] = { 0.0f,0.0f,1.0f };
		Color[3] = { 1.0f,0.0f,1.0f };
		glBindTexture(GL_TEXTURE_2D, texture_object[3]);
		RanderSurface(Color);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslated(0, -m_size, 0);
		glRotatef(90, 1, 0, 0);
		Color[0] = { 1.0f,0.0f,1.0f };
		Color[1] = { 0.0f,0.0f,1.0f };
		Color[2] = { 0.0f,0.0f,0.0f };
		Color[3] = { 1.0f,0.0f,0.0f };
		glBindTexture(GL_TEXTURE_2D, texture_object[4]);
		RanderSurface(Color);
	}
	glPopMatrix();

	glPushMatrix();
	if (m_rander_up)
	{
		glTranslated(0, m_size, 0);
		glRotatef(270, 1, 0, 0);
		Color[0] = { 1.0f,1.0f,0.0f };
		Color[1] = { 0.0f,1.0f,0.0f };
		Color[2] = { 0.0f,1.0f,1.0f };
		Color[3] = { 1.0f,1.0f,1.0f };
		glTranslated(0, -m_size + cos(m_up_angle*PI/180.0)*m_size, sin(m_up_angle*PI / 180.0)*m_size);
		glRotated(m_up_angle, 1, 0, 0);
		glBindTexture(GL_TEXTURE_2D, texture_object[5]);
		RanderSurface(Color);
	}
	glPopMatrix();
}

void CRGB_CM::RanderSurface(Vec3f color[4])
{
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glColor3f(color[0].x, color[0].y, color[0].z); //color_1
	glVertex3f(-m_size, m_size, 0.0);

	glTexCoord2f(1.0f, 1.0f);
	glColor3f(color[1].x, color[1].y, color[1].z); //color_2
	glVertex3f(m_size, m_size, 0.0);
	
	glTexCoord2f(1.0f, 0.0f);
	glColor3f(color[2].x, color[2].y, color[2].z); //color_3
	glVertex3f(m_size, -m_size, 0.0);
	
	glTexCoord2f(0.0f, 0.0f);
	glColor3f(color[3].x, color[3].y, color[3].z); //color_4
	glVertex3f(-m_size, -m_size, 0.0);
	glEnd();


}

void CRGB_CM::InitTexture()
{
	
	glGenTextures(6, texture_object);
	glBindTexture(GL_TEXTURE_2D, texture_object[0]);
	TexBits = LoadDIBitmap("Metal_1.bmp" , &m_bitInfo[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1024, 1024, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE,TexBits);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_REPLACE);
	
	glBindTexture(GL_TEXTURE_2D, texture_object[1]);
	TexBits = LoadDIBitmap("Metal_2.bmp", &m_bitInfo[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1024, 1024, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TexBits);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, texture_object[2]);
	TexBits = LoadDIBitmap("Metal_3.bmp", &m_bitInfo[2]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1024, 1024, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TexBits);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	
	glBindTexture(GL_TEXTURE_2D, texture_object[3]);
	TexBits = LoadDIBitmap("Metal_4.bmp", &m_bitInfo[3]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1024, 1024, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TexBits);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	
	
	glBindTexture(GL_TEXTURE_2D, texture_object[4]);
	TexBits = LoadDIBitmap("Metal_5.bmp", &m_bitInfo[4]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1024, 1024, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TexBits);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	
	glBindTexture(GL_TEXTURE_2D, texture_object[5]);
	TexBits = LoadDIBitmap("Metal_6.bmp", &m_bitInfo[5]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1024, 1024, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TexBits);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	
	
	
	

	cout << "Load Complete" << endl;
}
