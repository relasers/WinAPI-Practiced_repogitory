#pragma once
#include "stdafx.h"

class CCamera
{
private:
	Vec3f m_ptPosition;
	float m_fZoom = { 1.f };
	Point2f m_ptDelta = {90,0}; // beta and theta
	float m_faspect = { 1.f };
public:
	CCamera();
	~CCamera();

	void SetAspect(float aspect) { m_faspect = aspect; LookAt();}
	void Move(const Vec3f& pt) { m_ptPosition += pt; LookAt(); }
	void SetPosition(const Vec3f& pt) { m_ptPosition = pt; LookAt(); }
	const Vec3f& GetPosition() const { return m_ptPosition; };

	void Rotate(float x, float y) { m_ptDelta.x += x; m_ptDelta.y += y; LookAt();}
	void SetDelta(float x, float y) { m_ptDelta.x = x; m_ptDelta.y = y; LookAt();}

	Vec3f GetLookVector() const;
	void LookAt();
	
	void Zoom(bool In, float length = 0.1f) { m_fZoom += (In ? -1 : 1)*length; LookAt();}

};

