#pragma once
#include "Vec3D.h"
#include "stdafx.h"
class CBall
{
private:
	int m_size = 3;
	int m_speed = 2;
	
	
	Vec3f m_angle{};


	Vec3f m_pt{0,0,0};
public:
	CBall();
	~CBall();

	void Update();
	void Rander();
	int CollisionCheck(int size);
	
};

