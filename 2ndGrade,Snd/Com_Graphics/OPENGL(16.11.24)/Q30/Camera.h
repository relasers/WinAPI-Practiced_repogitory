#pragma once
#include "Vec3D.h"

#ifndef PI
#define PI 3.141592
#endif

constexpr int Camera_Speed = 4;

class CCamera
{
private:
	Vec3i m_camera_angle{ 0,0,0 };
	Vec3i m_Up{ 0,1,0 };
	Vec3i m_At{ 0,0,0 };
	Vec3i m_Eye{};

	int m_distance = -1000;

	int m_phase{};
	enum Phase {
		Closer,
		Rotate1,
		Rotate2,
		Rotate3,
		Rotate4,
		FarAway,
		Counter
	};
public:
	CCamera();
	~CCamera();
	void Rander();
	bool Update();

	void KeyInput(unsigned char key,int x,int y);
	void ResetPos();
	void HandleDistance(int distance);
	void HandlePosition(int angle,Vec3i axis);
};

