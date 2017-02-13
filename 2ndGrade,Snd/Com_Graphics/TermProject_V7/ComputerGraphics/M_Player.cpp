#pragma once
#include "M_Player.h"
#include <cmath>
#include <gl/glut.h>
#include "RanderProp.h"

C_M_Player::C_M_Player()
{
}


C_M_Player::~C_M_Player()
{
}

bool C_M_Player::Update(const float fTimeElapsed)
{
	// for Working Clockwork
	m_gearangle += 60.0f * fTimeElapsed;
	if(m_gearangle > 360.0f)
	return false;
}

void C_M_Player::Rander(bool isShooting)
{
	glPushMatrix();
	{
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		GLfloat gray[] = { m_gray.x, m_gray.y, m_gray.z, 1.0f };
		GLfloat specref[] = { m_specref.x, m_specref.y, m_specref.z, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, gray);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specref);
		glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 128);
		// BaseFrame
		Vec3f WireColor = COLOR_GOLD;
		Vec3f CoreColor = COLOR_RED;
		glColor4f(WireColor.x, WireColor.y, WireColor.z,1.0);
		
		
		glutWireSphere(m_size,20,20);
		// Core

		glColor4f(CoreColor.x, CoreColor.y, CoreColor.z, 1.0);


		glutSolidSphere(m_size/5.0f, 20, 20);
		// Rand Main Gear
		RandGear(m_size-m_size/10.0f,m_gearangle,COLOR_GOLD,1.0);
		
		glPushMatrix();
		{
			glRotatef(90, 0, 1, 0);
			glTranslatef(0, 0, m_size);
			RandGear(m_size / 2.0f - m_size / 20.0f, -m_gearangle, COLOR_GOLD, 1.0);
			glTranslatef(0, 0, -m_size*2);
			RandGear(m_size / 2.0f - m_size / 20.0f, -m_gearangle, COLOR_GOLD, 1.0);

		}
		glPopMatrix();
		// RandPropeller
		
		glPushMatrix();
		{
			glRotatef(90, 1, 0, 0);
			glTranslatef(0, 0, -m_size*1.5f);
			RandPropeller(m_size,m_size/3.0f, m_size*1.5f, m_size*0.5f, m_gearangle*13.0f,COLOR_WOOD,COLOR_JADE,1.0);
		}
		glPopMatrix();
		
		// Rander Gettling Both side

		glPushMatrix();
		{
			// Left Gettling
			glPushMatrix();
			{
				glTranslatef(-m_size*1.35f,0,0);
				if(!isShooting)
					RandGettling(m_size, m_size, m_size / 20.0f, m_gearangle, COLOR_WOOD, COLOR_GOLD, COLOR_BSILVER, COLOR_GOLD, 1.0);
				if (isShooting)
					RandGettling(m_size, m_size, m_size / 20.0f, m_gearangle*7, COLOR_WOOD, COLOR_GOLD, COLOR_GOLD, COLOR_GOLD, 1.0);

				glTranslatef(0,0,-m_size*0.7);
				// booster
				RandPiston(m_size, m_size*0.25,m_gearangle*5,COLOR_WINE,COLOR_GOLD,1.0);
			}
			glPopMatrix();
			// Right Gettling
			glPushMatrix();
			{
				glTranslatef(m_size*1.35f, 0, 0);
				if (!isShooting)
					RandGettling(m_size, m_size, m_size / 20.0f, -m_gearangle, COLOR_WOOD, COLOR_GOLD, COLOR_BSILVER, COLOR_GOLD, 1.0);
				if (isShooting)
					RandGettling(m_size, m_size, m_size / 20.0f, -m_gearangle * 7, COLOR_WOOD, COLOR_GOLD, COLOR_GOLD, COLOR_GOLD, 1.0);
				glTranslatef(0, 0, -m_size*0.7);
				// booster
				RandPiston(m_size, m_size*0.25, m_gearangle * 5,COLOR_WINE, COLOR_GOLD, 1.0);
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

