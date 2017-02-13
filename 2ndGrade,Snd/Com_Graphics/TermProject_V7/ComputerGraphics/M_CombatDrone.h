#pragma once
#include "Vector3D.h"

#ifndef PI
#define PI 3.141592
#endif

class C_M_CombatDrone
{
	Vec3f m_pt{};

	Vec3f m_gray{ 0.5f,0.5f,0.5f };
	Vec3f m_specref{ 1.0f,1.0f,1.0f };

	float m_size{ 64 };
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
	C_M_CombatDrone();
	~C_M_CombatDrone();

	bool Update(const float fTimeElapsed);
	void Rander();
	void RandArmor();

	Vec3f GetPos() const { return m_pt; }
};

