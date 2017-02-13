#pragma once
#include "Vector3D.h"

class CBullet
{
private:
	Vec3f m_pt{};

	float m_size{ 32 };

	Point2i m_angle{ 0,0 };

	Vec3f m_gray{ 0.5f,0.5f,0.5f };
	Vec3f m_specref{ 1.0f,1.0f,1.0f };

	int m_gearangle{};
public:
	enum class CubePos {
		LTF = 0
		, LTB
		, RTF
		, RTB
		, LBF
		, LBB
		, RBF
		, RBB
	};
public:
	CBullet();
	~CBullet();

	bool Update();
	void Rander();
};

