#pragma once
#include "Vector3D.h"

#ifndef PI
#define PI 3.141592
#endif

class CCombatDrone
{
	Vec3f m_pt{};

	Vec3f m_gray{ 0.5f,0.5f,0.5f };
	Vec3f m_specref{ 1.0f,1.0f,1.0f };

	float m_size{ 64 };
	int m_angle{};
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
	CCombatDrone();
	~CCombatDrone();

	bool Update();
	void Rander();
	void RandArmor();

	Vec3f Getpt() const { return m_pt; }
	void Setpt(Vec3f pt) { m_pt = pt; }
	void SetAngle(float angle) { m_angle = angle; }
};

