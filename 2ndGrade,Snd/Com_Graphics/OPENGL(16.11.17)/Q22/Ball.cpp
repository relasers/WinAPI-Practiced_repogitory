#include "Ball.h"
#include <gl/glut.h>
#include <cmath>

CBall::CBall()
{
	m_angle.x = rand() % 50 - 100;
	m_angle.y = rand() % 50 - 100;
	m_angle.z = rand() % 50 - 100;

	m_angle.Normalize();
}


CBall::~CBall()
{
}

void CBall::Update()
{
	m_pt += m_angle*m_speed;
	cout << m_angle;

}

void CBall::Rander()
{
	glPushMatrix();
	{
		glTranslatef(m_pt.x,m_pt.y,m_pt.z);
		glColor3f(1.0f,1.0f,1.0f);
		glutSolidSphere(m_size,30,30);
	}
	glPopMatrix();

}

int CBall::CollisionCheck(int size)
{
	if (m_pt.x+m_size > size) {
		m_pt.x = size - m_size;
		Vec3f Normal{-1,0,0};
		m_angle = m_angle + 2 * Normal*(-1*m_angle * Normal);

		return Dir::Right;
	}
	if (m_pt.x - m_size < -size) {
		m_pt.x = -size + m_size;

		Vec3f Normal{ 1,0,0 };
		m_angle = m_angle + 2 * Normal*(-1 * m_angle * Normal);

		return Dir::Left;
	}
	if (m_pt.y + m_size > size) {
		m_pt.y = size - m_size;

		Vec3f Normal{ 0,-1,0 };
		m_angle = m_angle + 2 * Normal*(-1 * m_angle * Normal);
		return Dir::Top;
	}
	if (m_pt.y - m_size < -size) {
		m_pt.y = -size + m_size;

		Vec3f Normal{ 0,1,0 };
		m_angle = m_angle + 2 * Normal*(-1 * m_angle * Normal);
		return Dir::Bottom;
	}
	if (m_pt.z + m_size > size) {
		m_pt.z = size - m_size;

		Vec3f Normal{ 0,0,-1 };
		m_angle = m_angle + 2 * Normal*(-1 * m_angle * Normal);
		return Dir::Far;
	}
	if (m_pt.z - m_size < -size) {
		m_pt.z = -size + m_size;

		Vec3f Normal{ 0,0,1 };
		m_angle = m_angle + 2 * Normal*(-1 * m_angle * Normal);
		return Dir::Near;
	}
	return Dir::None;


	
}
