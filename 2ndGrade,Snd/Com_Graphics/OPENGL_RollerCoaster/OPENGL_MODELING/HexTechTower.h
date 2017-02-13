#pragma once
#include "Vector3D.h"


class CHexTechTower
{
private:
	Vec3f m_pt{};

	float m_radius{ 64 };
	float m_height{ 256 };

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
	CHexTechTower();
	CHexTechTower(Vec3f pt);
	~CHexTechTower();

	bool Update();
	void Rander();

	void RandColumns();
	void RandWallGears();

	bool CollisionCheck(Vec3f pt);

	Vec3f GetPt()const { return m_pt; }
	float Getradius() const { return m_radius; }
};

