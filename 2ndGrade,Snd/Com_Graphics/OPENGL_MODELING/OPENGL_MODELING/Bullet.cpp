#include "Bullet.h"
#include <cmath>
#include <gl/glut.h>


CBullet::CBullet()
{
}


CBullet::~CBullet()
{
}

bool CBullet::Update()
{
	(++m_gearangle) %= 360;
	return false;
}

void CBullet::Rander()
{
	glPushMatrix();
	{
		glTranslatef(m_pt.x, m_pt.y, m_pt.z); 
		glutSolidSphere(m_size,10,10);
		glRotatef(m_gearangle,1,1,1);
		glutWireCube(m_size*1.1);
	}
	glPopMatrix();
}
