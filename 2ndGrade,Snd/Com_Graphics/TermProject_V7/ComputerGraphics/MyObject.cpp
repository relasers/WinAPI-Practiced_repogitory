#include "stdafx.h"
#include "MyObject.h"


CMyObject::CMyObject()
{
	m_vCenter = { 0.0f ,0.0f, 0.0f };
	for (int i = 0; i < 16; i++) m_fRotateMatrix[i] = 0;
	for (int i = 0; i < 4; i++) m_fRotateMatrix[i * 4 + i] = 1;
}

CMyObject::~CMyObject()
{
}

void CMyObject::Rotate(const float angle, bool x, bool y, bool z)
{
	glPushMatrix();
	glLoadIdentity();
	if (x) 
	{
		glRotatef(angle, 1.0f, 0.0f, 0.0f);
		m_Angle.x += angle;
	}
	if (y) 
	{
		glRotatef(angle, 0.0f, 1.0f, 0.0f);
		m_Angle.y += angle;
	}
	if (z) 
	{
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		m_Angle.z += angle;
	}
	glMultMatrixf(m_fRotateMatrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_fRotateMatrix);
	glPopMatrix();
}
