#pragma once
#include "stdafx.h"

class CCombatDrone
{
	Vec3f m_pt{};

	Vec3f m_gray{ 0.5f,0.5f,0.5f };
	Vec3f m_specref{ 1.0f,1.0f,1.0f };

	float m_size{ 32 };
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
};

