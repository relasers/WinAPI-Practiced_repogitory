#pragma once
#include "MyObject.h"

using namespace std;

class Cbullet : public CMyObject
{
private:
	Vec3f m_vDirection;
	CCube m_BindingCube;

	Vec3f m_color{};
	float m_size{32};
	float m_speed{50};
	
	int m_rotate_angle{};

	bool m_isAlly = false;
	bool m_isaccelated = false;
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
	Cbullet();
	Cbullet(Vec3f pt,Vec3f target
		,float speed , float size,
		bool isaccel,Vec3f color,bool isally);
	~Cbullet();
	CCube& Get_BindCube() { return m_BindingCube; }

	void Collide() { m_bDie = true; }

	virtual void Update(const float fTimeElapsed);
	virtual void Rendering();
	const float GetSize() const { return m_size; }
};

