#pragma once
#include "Vector3D.h"

#ifndef PI
#define PI 3.141592
#endif



class CPlayer
{


private:
	Vec3f m_pt{};
	Vec3f m_dir{};


	Vec3f m_gray{ 0.5f,0.5f,0.5f };
	Vec3f m_specref{ 1.0f,1.0f,1.0f };

	float m_size{ 32 };
	int m_gearangle{};
	int m_angle{};
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
	Vec3f Getpt() const { return m_pt; }
	void Setpt(Vec3f pt) { m_pt = pt; }
	void SetAngle(float angle) { m_angle = angle; }
	void SetDir(Vec3f dir) { m_dir = dir; }
	Vec3f GetDir() { return m_dir; }
};

