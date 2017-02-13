#pragma once
#include "Vector3D.h"

#ifndef PI
#define PI 3.141592
#endif


class CFirstcamera
{
private:

	Vec3i m_camera_angle{ 0,50,0 };
	Vec3i m_Up{ 0,1,0 };
	Vec3i m_At{ 0,0,0 };
	Vec3i m_Eye{};
public:
	CFirstcamera();
	~CFirstcamera();

	void Rander();
	bool Update();

	void SetEye(Vec3i eye) { m_Eye = eye; }
	void SetAt(Vec3i at) { m_At = at; }
};

