#pragma once
#include "Vector3D.h"

#ifndef PI
#define PI 3.141592f
#endif



class C_M_Player
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
	C_M_Player();
	~C_M_Player();

	bool Update(const float fTimeElapsed);
	void Rander(bool isShooting);

	const float GetSize() const{ return m_size; }
	Vec3f GetPos() const { return m_pt; }
	const float GetAngle() const { return m_gearangle; }
};

