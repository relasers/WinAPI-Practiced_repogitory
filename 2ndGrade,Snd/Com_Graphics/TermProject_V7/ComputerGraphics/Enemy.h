#pragma once
#include "MyObject.h"
#include "M_CombatDrone.h"
#define Turning_Speed 1.0f

class CLauncher;
class CEnemy : public CMyObject
{
private:
	C_M_CombatDrone m_Model;
	Vec3f m_vDirection;
	CCube m_BindingCube;

	CPlayer * m_Target;

	int m_Hp = 3;
	int m_Barrier = 10;
	float m_speed = 150;

	float m_Timer = 0.0f;
	float m_HitTimer = 0.0f;
	float m_RepairTimer = 0.0f;

	CLauncher * m_launcher;

public:
	CEnemy();
	CEnemy(Vec3f &pos, CPlayer * target, std::list<class Cbullet*>& bullets);
	~CEnemy();

	CCube& Get_BindCube() { return m_BindingCube; }
	void CollideEnv() { m_bDie = true; }
	void Hit(int damage);

	virtual void Update(const float fTimeElapsed);
	virtual void Rendering();

	virtual void Translate(const Vec3f move) { m_vCenter += move; }
	virtual void Rotate(const float angle, bool x, bool y, bool z);
};

