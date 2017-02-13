#pragma once
#include "CombatDrone.h"
#include <cmath>
#include <gl/glut.h>
#include "RanderProp.h"

CCombatDrone::CCombatDrone()
{
}


CCombatDrone::~CCombatDrone()
{
}

bool CCombatDrone::Update()
{
	// for Working Clockwork
	(++m_gearangle) %= 360;
	return false;
}

void CCombatDrone::Rander()
{
	glPushMatrix();
	{
		glTranslatef(m_pt.x, m_pt.y, m_pt.z);
		GLfloat gray[] = { m_gray.x, m_gray.y, m_gray.z, 1.0f };
		GLfloat specref[] = { m_specref.x, m_specref.y, m_specref.z, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, gray);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specref);
		glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 128);
		float angle = sin(m_gearangle*PI / 180.0)*m_size*0.1;

		
		
		glRotatef(m_gearangle,1,1,1);
		glutSolidSphere(m_size*0.1, 10, 12);
		glutWireSphere(m_size*0.2 + angle, 6, 6);
		glRotatef(-m_gearangle, 1, 1, 1);

		glutWireCube(m_size+angle);
		
		

		glPushMatrix();
		{
			glTranslatef(0, 0, m_size*0.5 + angle);
			RandArmor();
			glTranslatef(0, 0, -m_size - angle * 2);
			RandArmor();
		}
		glPopMatrix();
		
		/*
		glPushMatrix();
		{
			glTranslatef(m_size + angle, 0, 0);
			glRotatef(90,0,1,0);
			RandGear(m_size*0.5, m_gearangle);
			glRotatef(-90, 0, 1, 0);
			glTranslatef(-m_size*2 - angle * 2, 0,0 );
			glRotatef(90, 0, 1, 0);
			RandGear(m_size*0.5, m_gearangle);
			glRotatef(-90, 0, 1, 0);
		}
		glPopMatrix();
		*/
		






	}
	glPopMatrix();
}

void CCombatDrone::RandArmor()
{
	float angle = sin(m_gearangle*PI / 180.0)*m_size*0.1;

	glPushMatrix();
	{
		glPushMatrix();
		{
			glTranslatef(m_size*0.5+ angle, m_size*0.5 + angle, 0);
			glutSolidCube(m_size*0.5);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(m_size*0.5 + angle, -m_size*0.5 - angle, 0);
			glutSolidCube(m_size*0.5);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(-m_size*0.5 - angle, m_size*0.5 + angle, 0);
			glutSolidCube(m_size*0.5);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(-m_size*0.5 - angle, -m_size*0.5 - angle, 0);
			glutSolidCube(m_size*0.5);
		}
		glPopMatrix();
	}
	glPopMatrix();
	

}
