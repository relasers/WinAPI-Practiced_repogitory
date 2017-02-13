#pragma once
#include "stdafx.h"
#include "bullet.h"


Cbullet::Cbullet()
{
}

Cbullet::Cbullet(Vec3f pt, Vec3f target
	, float speed, float size, bool isaccel,Vec3f color,bool isally)
{
	m_vCenter = pt;
	m_color = color;
	m_vDirection = target - pt;
	Normalize(m_vDirection);
	m_speed = speed;
	m_size = size;
	m_isaccelated = isaccel;
	m_isAlly = isally;
}


Cbullet::~Cbullet()
{
}

void Cbullet::Update(const float fTimeElapsed)
{

	if (m_isaccelated) m_speed += 1.f * fTimeElapsed;

	m_vCenter += m_vDirection * m_speed * fTimeElapsed;
	m_BindingCube.SetPos(m_vCenter);
	m_rotate_angle += 60.0f * fTimeElapsed;
	if (m_rotate_angle > 360.0f) m_rotate_angle= 0.0f;




}

void Cbullet::Rendering()
{
	if (!m_isAlly) {
		glPushMatrix();
		{
			glLineWidth(3.0);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glTranslatef(m_vCenter.x, m_vCenter.y, m_vCenter.z);
			glRotatef(m_rotate_angle, 1, 1, 1);
			glutWireCube(m_size);
			glColor3f(m_color.x, m_color.y, m_color.z);
			glRotatef(m_rotate_angle, 1, 1, 1);
			glutWireSphere(m_size*0.5, 6, 6);
			glRotatef(m_rotate_angle, 1, 1, 1);
			glutSolidSphere(m_size*0.25, 6, 6);
			glLineWidth(1.0);
		}
		glPopMatrix();
	}

	if (m_isAlly) {
		glPushMatrix();
		{
			glLineWidth(3.0);
			
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glTranslatef(m_vCenter.x, m_vCenter.y, m_vCenter.z);
			glColor3f(m_color.x, m_color.y, m_color.z);
			glRotatef(m_rotate_angle*2, 1, 1, 1);
			glutWireSphere(m_size, 6, 6);
			glRotatef(m_rotate_angle*3, 1, 1, 1);
			glutSolidSphere(m_size*0.8, 6, 6);
			glLineWidth(1.0);
		}
		glPopMatrix();
	}
	
}
