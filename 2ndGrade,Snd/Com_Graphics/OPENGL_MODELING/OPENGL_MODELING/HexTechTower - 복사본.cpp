#pragma once
#include "HexTechTower.h"
#include <cmath>
#include <gl/glut.h>
#include "RanderProp.h"


CHexTechTower::CHexTechTower()
{
}


CHexTechTower::~CHexTechTower()
{
}

bool CHexTechTower::Update()
{
	(++m_gearangle) %= 360;
	return false;
}

void CHexTechTower::Rander()
{
	float angle = sin(m_gearangle*PI / 180.0)*m_height;

	glPushMatrix();
	{
		glTranslatef(m_pt.x, m_pt.y, m_pt.z);
		// rand Columns
		RandColumns();
		// rand floor
		glPushMatrix();
		{
			// top floor

			glTranslatef(0, m_height*0.5, 0);
			RandColumn(m_radius*1.4, m_height*0.02);
			glPushMatrix();
			{
				// Rand rooftop
				glPushMatrix();
				{
					glRotatef(-90,1,0,0);
					glRotatef(-45,0,0,1);
					glLineWidth(3.0);
					glutWireCone(m_radius*2,m_height*0.25,4,10);
					glLineWidth(1.0);
					glutSolidCone(m_radius * 1.95, m_height*0.25, 4, 10);

				}
				glPopMatrix();
				
				glTranslatef(0,-m_height*0.1,0);
				glRotatef(m_gearangle+angle,0,1,0);
				RandGear(m_radius*0.8, m_gearangle);
				glRotatef(90 , 0, 1, 0);
				RandGear(m_radius*0.8, m_gearangle);
			}
			glPopMatrix();

			// mid floor
			glPushMatrix();
			{
				glTranslatef(0, -m_height*0.02,0 );
				glRotatef(90,1,0,0);
				RandGear(m_radius*0.6,m_gearangle);
			}
			glPopMatrix();

			// bottom floor
			glTranslatef(0, -m_height, 0);
			RandColumn(m_radius*1.25, m_height*0.01);
			glTranslatef(0, -m_height*0.5, 0);
			RandColumn(m_radius*1.25, m_height*0.01);
		}
		glPopMatrix();
		
		// rand mid tower
		glPushMatrix();
		{
			glTranslatef(0,m_height*0.25,0);
			RandWallGears();
			
			glTranslatef(0, -m_height*0.5, 0);
			// rand Energy Cube
			RandEnergyCubes(m_radius*0.2, m_gearangle);
			RandWallGears();
		}
		glPopMatrix();

		// randClock
		glPushMatrix();
		{
		glTranslatef(0,m_height*0.5,0);
		glRotatef(90,1,0,0);
		glRotatef(angle*0.005,0,1,0);
		RandClock(m_height*0.25, m_height*0.25,m_gearangle);
		}
		glPopMatrix();

		// Rand Engine
		glPushMatrix();
		{
			
			glRotatef(90, 1, 0, 0);
			RandGear(m_radius, -m_gearangle);
			glRotatef(-90, 1, 0, 0);
			glTranslatef(0, -m_height*0.5, 0);
			glRotatef(90, 1, 0, 0);
			RandGear(m_radius,m_gearangle);
		}
		glPopMatrix();
		
		// rand bottom gears
		glPushMatrix();
		{
			glTranslatef(0, -m_height*0.75, 0);

			glRotatef(90,1,0,0);
			RandPiston(m_height*0.25,m_radius,m_gearangle);
			RandPiston(m_height*0.2, m_radius*1.1, -m_gearangle);
			RandPiston(m_height*0.15, m_radius*1.2, m_gearangle);
			glRotatef(-90, 1, 0, 0);
			RandWallGears();
			
		}
		glPopMatrix();



	}
	glPopMatrix();
	
	

	



}

void CHexTechTower::RandColumns()
{
	glPushMatrix();
	{
		glTranslatef(-m_radius, -m_height*0.25, m_radius);
		RandColumn(m_radius*0.2, m_height*0.75);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(m_radius, -m_height*0.25, m_radius);
		RandColumn(m_radius*0.2, m_height*0.75);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(-m_radius, -m_height*0.25, -m_radius);
		RandColumn(m_radius*0.2, m_height*0.75);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(m_radius, -m_height*0.25, -m_radius);
		RandColumn(m_radius*0.2, m_height*0.75);
	}
	glPopMatrix();
}

void CHexTechTower::RandWallGears()
{
	float angle = sin(m_gearangle*PI / 180.0)*m_height;
	glPushMatrix();
	{
		glTranslatef(m_radius*0.9, 0, 0);
		glRotatef(90, 0, 1, 0);
		RandGear(m_height*0.18, m_gearangle);
		glRotatef(90, 1, 0, 0);
		//RandCurvedgrid(m_radius, m_radius, angle*0.1);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(-m_radius*0.9, 0, 0);
		glRotatef(90, 0, 1, 0);
		RandGear(m_height*0.18, m_gearangle);
		glRotatef(90, 1, 0, 0);
		//RandCurvedgrid(m_radius, m_radius, angle*0.1);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(0, 0, m_radius*0.9);
		RandGear(m_height*0.18, m_gearangle);
		glRotatef(90, 1, 0, 0);
		//RandCurvedgrid(m_radius, m_radius, angle*0.05);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(0, 0, -m_radius*0.9);
		RandGear(m_height*0.18, m_gearangle);
		glRotatef(90, 1, 0, 0);
		//RandCurvedgrid(m_radius, m_radius, angle*0.05);
	}
	glPopMatrix();
}
