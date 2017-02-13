#pragma once
#include "MyObject.h"

class Cbullet;
class CEnergyBolt : public CMyObject
{
private:
	Vec3f m_vDirection;
	CCube m_BindingCube;

	Vec3f m_color{};
	float m_size{ 128 };
	float m_speed{ 500 };

	int m_rotate_angle{};

	std::list<class Cbullet*>* m_bullets;
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
	CEnergyBolt();
	CEnergyBolt(Vec3f pt, Vec3f target
		, float speed, float size, Vec3f color, list<Cbullet*>& bullets);
	~CEnergyBolt();

	CCube& Get_BindCube() { return m_BindingCube; }
	void Collide() { m_bDie = true; }

	virtual void Update(const float fTimeElapsed);
	virtual void Rendering();
	const float GetSize() const { return m_size; }
};

