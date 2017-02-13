
#include "stdafx.h"
#include "M_HexTechTower.h"
#include "RanderProp.h"


C_M_HexTechTower::C_M_HexTechTower()
{
}



C_M_HexTechTower::~C_M_HexTechTower()
{
}

bool C_M_HexTechTower::Update(const float fTimeElapsed)
{
	m_gearangle += 60.0f * fTimeElapsed;
	if (m_gearangle > 360.0f) m_gearangle = 0.0f;
	return false;
}

void C_M_HexTechTower::Rander()
{
	float angle = sin(m_gearangle*PI / 180.0)*m_height;

	glPushMatrix();
	{
		// rand Core
		glPushMatrix();
		{
			glTranslatef(0, m_height*0.75, 0);
			glRotatef(m_gearangle, 0, 1, 0);
			glColor3f(1.0, 0.5, 0.3);
			glutSolidSphere(m_radius*0.2 - angle*0.01,20,20);
			glColor3f(1.0, 0.0, 1.0);
			glutWireTeapot(m_radius*0.5 + angle*0.02);
			glColor3f(1.0, 1.0, 1.0);
		}
		glPopMatrix();





		// rand Columns
		RandColumns();
		// rand floor
		glPushMatrix();
		{
			// top floor

			glTranslatef(0, m_height*0.5, 0);
			RandColumn(m_radius*1.4, m_height*0.02, COLOR_WINE, COLOR_BSILVER, COLOR_GOLD, 1.0);
			glPushMatrix();
			{
				// Rand rooftop
				glPushMatrix();
				{
					glColor3f(1.0,1.0,1.0);
					glRotatef(-90, 1, 0, 0);
					glRotatef(-45, 0, 0, 1);
					glLineWidth(3.0);
					glutWireCone(m_radius * 2, m_height*0.25, 4, 10);
					glLineWidth(1.0);
					glutSolidCone(m_radius * 1.95, m_height*0.25, 4, 10);

				}
				glPopMatrix();
			}
			glPopMatrix();

			// mid floor
			glPushMatrix();
			{
				glTranslatef(0, -m_height*0.02, 0);
				glRotatef(90, 1, 0, 0);
				RandGear(m_radius*0.6, m_gearangle, COLOR_GOLD, 1.0);
			}
			glPopMatrix();

			// bottom floor
			glTranslatef(0, -m_height, 0);
			RandColumn(m_radius*1.25, m_height*0.01, COLOR_WINE, COLOR_BSILVER, COLOR_GOLD, 1.0);
			glTranslatef(0, -m_height*0.5, 0);
			RandColumn(m_radius*1.25, m_height*0.01, COLOR_WINE, COLOR_BSILVER, COLOR_GOLD, 1.0);
		}
		glPopMatrix();

		// rand mid tower
		glPushMatrix();
		{
			glTranslatef(0, m_height*0.25, 0);
			RandWallGears();

			glTranslatef(0, -m_height*0.5, 0);
			// rand Energy Cube
			RandEnergyCubes(m_radius*0.2, m_gearangle, COLOR_JADE, 0.8);
			RandWallGears();
		}
		glPopMatrix();

		// randClock
		glPushMatrix();
		{
			glTranslatef(0, m_height*0.5, 0);
			glRotatef(90, 1, 0, 0);
			glRotatef(angle*0.015, 0, 1, 0);
			RandClock(m_height*0.3, m_radius, m_gearangle, COLOR_WOOD, COLOR_WINE, COLOR_GOLD, COLOR_RED, COLOR_YELLOW, 1.0);
		}
		glPopMatrix();

		// Rand Engine
		glPushMatrix();
		{

			glRotatef(90, 1, 0, 0);
			RandGear(m_radius*2.0, -m_gearangle, COLOR_GOLD, 0.5);
			glRotatef(-90, 1, 0, 0);
			glTranslatef(0, -m_height*0.5, 0);
			glRotatef(90, 1, 0, 0);
			RandGear(m_radius, m_gearangle, COLOR_GOLD, 1.0);
		}
		glPopMatrix();

		// rand bottom gears
		glPushMatrix();
		{
			glTranslatef(0, -m_height*0.75, 0);

			glRotatef(90, 1, 0, 0);
			RandPiston(m_height*0.25, m_radius, m_gearangle, COLOR_BSILVER, COLOR_GOLD, 1.0);
			RandPiston(m_height*0.2, m_radius*1.1, -m_gearangle, COLOR_BSILVER, COLOR_GOLD, 1.0);
			RandPiston(m_height*0.15, m_radius*1.2, m_gearangle, COLOR_BSILVER, COLOR_GOLD, 1.0);
			glRotatef(-90, 1, 0, 0);
			RandWallGears();

		}
		glPopMatrix();



	}
	glPopMatrix();







}


void C_M_HexTechTower::RandColumns()
{
	glPushMatrix();
	{
		glTranslatef(-m_radius, -m_height*0.25, m_radius);
		RandColumn(m_radius*0.2, m_height*0.75, COLOR_WINE, COLOR_BSILVER, COLOR_GOLD, 1.0);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(m_radius, -m_height*0.25, m_radius);
		RandColumn(m_radius*0.2, m_height*0.75, COLOR_WINE, COLOR_BSILVER, COLOR_GOLD, 1.0);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(-m_radius, -m_height*0.25, -m_radius);
		RandColumn(m_radius*0.2, m_height*0.75, COLOR_WINE, COLOR_BSILVER, COLOR_GOLD, 1.0);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(m_radius, -m_height*0.25, -m_radius);
		RandColumn(m_radius*0.2, m_height*0.75, COLOR_WINE, COLOR_BSILVER, COLOR_GOLD, 1.0);
	}
	glPopMatrix();
}

void C_M_HexTechTower::RandWallGears()
{
	float angle = sin(m_gearangle*PI / 180.0)*m_height;
	glPushMatrix();
	{
		glTranslatef(m_radius*0.9, 0, 0);
		glRotatef(90, 0, 1, 0);
		RandGear(m_radius * 2, m_gearangle, COLOR_BSILVER, 0.7);
		glRotatef(90, 1, 0, 0);
		//RandCurvedgrid(m_radius, m_radius, angle*0.1);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(-m_radius*0.9, 0, 0);
		glRotatef(90, 0, 1, 0);
		RandGear(m_radius*2, m_gearangle, COLOR_BSILVER, 0.7);
		glRotatef(90, 1, 0, 0);
		//RandCurvedgrid(m_radius, m_radius, angle*0.1);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(0, 0, m_radius*0.9);
		RandGear(m_radius * 2, m_gearangle, COLOR_BSILVER, 0.7);
		glRotatef(90, 1, 0, 0);
		//RandCurvedgrid(m_radius, m_radius, angle*0.05);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(0, 0, -m_radius*0.9);
		RandGear(m_radius * 2, m_gearangle, COLOR_BSILVER, 0.7);
		glRotatef(90, 1, 0, 0);
		//RandCurvedgrid(m_radius, m_radius, angle*0.05);
	}
	glPopMatrix();
}
