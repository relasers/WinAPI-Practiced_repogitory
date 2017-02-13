#pragma once
#include "Vector3D.h"

#ifndef PI
#define PI 3.141592
#endif



class CPlayer
{


private:
	Vec3f m_pt{};

	Vec3f m_gray{0.5f,0.5f,0.5f};
	Vec3f m_specref{1.0f,1.0f,1.0f};

	float m_size{32};
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
	CPlayer();
	~CPlayer();

	bool Update();
	void Rander();
};

