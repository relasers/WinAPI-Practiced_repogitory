#include "RGB_CM.h"
#include <iostream>
#include <gl/glut.h>
#include <cmath>


CRGB_CM::CRGB_CM()
{
}


CRGB_CM::~CRGB_CM()
{
}

void CRGB_CM::Rander()
{
	
	//glRotated(30,1,0,0);
	//glRotated(45+m_angle, 0, 1, 0);
	glPushMatrix();
	{
		RanderModel();

		for (auto &p : m_ball) {
			p.Rander();
		}

		for (auto &p : m_cube) {
			p.Rander();
		}

	}
	glPopMatrix();
	

}

void CRGB_CM::Update(int camera_angle)
{
	(++m_angle) %= 360;

	for (auto &p : m_cube) {
		p.SetDirection(-camera_angle+270);
		p.Update();
		p.CollisionCheck(m_size);
	}

	for (auto &p : m_ball) {
		p.Update();
		switch (p.CollisionCheck(m_size)) 
		{
		case Dir::Left:
			ChangeColor(0);
			break;
		case Dir::Right:
			ChangeColor(1);
			break;
		case Dir::Top:
			ChangeColor(5);
			break;
		case Dir::Bottom:
			ChangeColor(4);
			break;
		case Dir::Near:
			ChangeColor(2);
			break;
		case Dir::Far:
			ChangeColor(3);
			break;
		case Dir::None:
			break;
		}
	}





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
	if (key == 'd' || key == 'D') {
		if(m_ball.size() < 5)
		m_ball.push_back(CBall());
	}
	if (key == 'f' || key == 'F') {
		m_cube.push_back(CDropCube(10, -70, {1.0f,0.0f,0.0f}));
		m_cube.push_back(CDropCube(20, 0, { 0.0f,1.0f,0.0f }));
		m_cube.push_back(CDropCube(30, 70, { 0.0f,0.0f,1.0f }));
	}
}

void CRGB_CM::RanderModel()
{
	glPushMatrix();
	{
		glTranslated(-m_size, 0, 0);
		glRotatef(270, 0, 1, 0);
		RanderSurface(Color[0]);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslated(m_size, 0, 0);
		glRotatef(90, 0, 1, 0);
		RanderSurface(Color[1]);
	}
	glPopMatrix();

	glPushMatrix();
	if (m_rander_face)
	{
		glTranslated(0, 0, -m_size);
		glRotatef(180, 0, 1, 0);
		glTranslated(0, -m_size + cos(m_face_angle*PI / 180.0)*m_size, sin(m_face_angle*PI / 180.0)*m_size);
		glRotated(m_face_angle, 1, 0, 0);
		RanderSurface(Color[2]);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslated(0, 0, m_size);
		RanderSurface(Color[3]);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslated(0, -m_size, 0);
		glRotatef(90, 1, 0, 0);
		RanderSurface(Color[4]);
	}
	glPopMatrix();

	glPushMatrix();
	if (m_rander_up)
	{
		glTranslated(0, m_size, 0);
		glRotatef(270, 1, 0, 0);
		glTranslated(0, -m_size + cos(m_up_angle*PI/180.0)*m_size, sin(m_up_angle*PI / 180.0)*m_size);
		glRotated(m_up_angle, 1, 0, 0);
		RanderSurface(Color[5]);
	}
	glPopMatrix();
}

void CRGB_CM::RanderSurface(Vec3f color[4])
{

	glBegin(GL_QUADS);
	glColor3f(color[0].x, color[0].y, color[0].z); //color_1
	glVertex3f(-m_size, m_size, 0.0);
	glColor3f(color[1].x, color[1].y, color[1].z); //color_2
	glVertex3f(m_size, m_size, 0.0);
	glColor3f(color[2].x, color[2].y, color[2].z); //color_3
	glVertex3f(m_size, -m_size, 0.0);
	glColor3f(color[3].x, color[3].y, color[3].z); //color_4
	glVertex3f(-m_size, -m_size, 0.0);
	glEnd();


}

void CRGB_CM::ChangeColor(int x)
{
	for (int i = 0; i < 4; ++i) {
		Color[x][i].x = (float)(rand() % 100) / 100.0f;
		Color[x][i].y = (float)(rand() % 100) / 100.0f;
		Color[x][i].z = (float)(rand() % 100) / 100.0f;
	}

}
