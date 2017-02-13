#pragma once
#include "stdafx.h"
#include "Camera.h"

CCamera::CCamera()
{
}


CCamera::~CCamera()
{
}

Vec3f CCamera::GetLookVector() const
{
	return Normalize( Vec3f{
		cos(DegreeToRadian(m_ptDelta.x)),
		tan(DegreeToRadian(m_ptDelta.y)),
		sin(DegreeToRadian(m_ptDelta.x))
	});
}

void CCamera::LookAt()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(60.0, m_faspect, 1.0, 10000);
	
	auto eye = m_ptPosition + GetLookVector() * m_fZoom;
	gluLookAt(
		eye.x,eye.y,eye.z,
		m_ptPosition.x, m_ptPosition.y, m_ptPosition.z,
		0,1,0
	);

	glMatrixMode(GL_MODELVIEW);
}
