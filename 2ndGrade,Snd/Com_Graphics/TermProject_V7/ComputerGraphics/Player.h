#pragma once
#include "MyObject.h"
#include "M_Player.h"

#define P_SHOOTTICK 0.1f
#define BOOSTTIME 0.1f

class CPlayer : public CMyObject
{
private:
	C_M_Player m_Model;
	Vec3f m_vDirection;
	CCube m_BindingCube;


	int m_Hp = 5;
	int m_Barrier = 100;
	int m_Boost = 100;
	float m_Speed = 200.0f;

	float m_shoot_tick = 0.0f;

	float m_BoostTimer = 0.0f;
	float m_HitTimer = 0.0f;
	float m_RepairTimer = 0.0f;

	bool m_isShooting = false;
	bool m_bBoost = false;

	std::list<class Cbullet*>* m_ally_bullets;
public:
	CPlayer();
	CPlayer(std::list<Cbullet*>& ally_bullets);
	~CPlayer();

	const int GetHP() { return m_Hp; }
	const int GetBarrier() { return m_Barrier; }
	const int GetBoost() { return m_Boost; }
	const C_M_Player GetModel() { return m_Model; }
	const float GetSpeed() const { return m_Speed; }
	CCube& Get_BindCube() { return m_BindingCube; }

	void CollideEnv() { m_bDie = true; m_Barrier = 0; m_Hp = 0; }
	void Hit(int damage);

	void Reset();

	void SetPos(Vec3f& pos) 
	{
		m_vCenter = pos;
		m_BindingCube.SetPos(m_vCenter);
	}
	void RotateToDirection(Vec3f& look, Vec3f& angle);

	void SetisShooting(bool isShoot) { m_isShooting = isShoot; }
	void Boost(bool boost) { m_bBoost = boost; if (m_Boost <= 0) m_bBoost = false; }

	virtual void Update(const float fTimeElapsed);
	virtual void Rendering();

	virtual void Translate(const Vec3f move) { m_vCenter += move; }
	virtual void Rotate(const float angle, bool x, bool y, bool z);
};

