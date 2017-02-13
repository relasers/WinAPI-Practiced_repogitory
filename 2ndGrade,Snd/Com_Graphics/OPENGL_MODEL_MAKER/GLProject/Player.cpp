#pragma once
#include "stdafx.h"
#include "Player.h"
#include "RanderProp.h"

CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

bool CPlayer::Update()
{
	// for Working Clockwork
	(++m_gearangle) %= 360;
	return false;
}

void CPlayer::Rander()
{
	glPushMatrix();
	{
		glTranslatef(m_pt.x,m_pt.y,m_pt.z);
		GLfloat gray[] = { m_gray.x, m_gray.y, m_gray.z, 1.0f };
		GLfloat specref[] = { m_specref.x, m_specref.y, m_specref.z, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, gray);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specref);
		glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 128);
		// BaseFrame
		glutWireSphere(m_size,20,20);
		// Core
		glutSolidSphere(m_size/5.0f, 20, 20);
		// Rand Main Gear
		RandGear(m_size-m_size/10.0f,m_gearangle);
		
		glPushMatrix();
		{
			glRotatef(90, 0, 1, 0);
			glTranslatef(0, 0, m_size);
			RandGear(m_size / 2.0f - m_size / 20.0f, -m_gearangle);
			glTranslatef(0, 0, -m_size*2);
			RandGear(m_size / 2.0f - m_size / 20.0f, -m_gearangle);

		}
		glPopMatrix();
		// RandPropeller
		
		glPushMatrix();
		{
			glRotatef(90, 1, 0, 0);
			glTranslatef(0, 0, -m_size*1.5f);
			RandPropeller(m_size,m_size/3.0f, m_size*1.5f, m_size*0.5f, m_gearangle*13.0f);
		}
		glPopMatrix();
		
		// Rander Gettling Both side

		glPushMatrix();
		{
			// Left Gettling
			glPushMatrix();
			{
				glTranslatef(-m_size*1.35f,0,0);
				RandGettling(m_size,m_size, m_size / 20.0f, m_gearangle);
				glTranslatef(0,0,-m_size*0.7);
				// booster
				RandPiston(m_size, m_size*0.25,m_gearangle*5);
			}
			glPopMatrix();
			// Right Gettling
			glPushMatrix();
			{
				glTranslatef(m_size*1.35f, 0, 0);
				RandGettling(m_size,m_size, m_size / 20.0f, -m_gearangle);
				glTranslatef(0, 0, -m_size*0.7);
				// booster
				RandPiston(m_size, m_size*0.25, m_gearangle * 5);
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

