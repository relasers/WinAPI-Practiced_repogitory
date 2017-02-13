#pragma once
#include "stdafx.h"
#include "CombatDrone.h"
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
		glutSolidSphere(m_size*0.1,20,20);
		glutWireCube(m_size);
		
		float angle = sin(m_gearangle*PI / 180.0)*m_size*0.1;

		glTranslatef(0, 0, m_size*0.5 + angle);
		RandArmor();
		glTranslatef(0, 0, -m_size - angle*2);
		RandArmor();



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
