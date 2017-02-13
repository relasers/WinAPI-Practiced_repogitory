#include "DropCube.h"
#include "stdafx.h"
#include <gl/glut.h>


CDropCube::CDropCube()
{
}

CDropCube::CDropCube(int size, int depth,Vec3f Color)
{
	m_size = size;
	m_pt.z = depth;
	m_color = Color;
}


CDropCube::~CDropCube()
{
}

void CDropCube::Rander()
{
	glPushMatrix();
	{
		glColor3f(m_color.x,m_color.y,m_color.z);
		glTranslatef(m_pt.x,m_pt.y, m_pt.z);
		glutWireCube(m_size);
	}
	glPopMatrix();
}

void CDropCube::Update()
{
	m_pt += m_mvector*m_speed;

}

void CDropCube::SetDirection(int x)
{
	Vec3f Target = { (float)cos(x*PI / 180.0) * 200,(float)sin(x*PI / 180.0) * 200,m_pt.z };
	m_mvector = Target - m_pt;
	m_mvector.Normalize();

}

void CDropCube::CollisionCheck(int cubesize)
{
	if (m_pt.x + m_size/2 > cubesize)
	{
		m_pt.x = cubesize - m_size / 2;
	}
	if (m_pt.x - m_size / 2 < -cubesize)
	{
		m_pt.x = -cubesize + m_size / 2;
	}
	if (m_pt.y + m_size / 2 > cubesize)
	{
		m_pt.y = cubesize - m_size / 2;
	}
	if (m_pt.y - m_size / 2 < -cubesize)
	{
		m_pt.y = -cubesize + m_size / 2;
	}
	if (m_pt.z + m_size / 2 > cubesize)
	{
		m_pt.z = cubesize - m_size / 2;
	}
	if (m_pt.z - m_size / 2 < -cubesize)
	{
		m_pt.z = -cubesize + m_size / 2;
	}
}
