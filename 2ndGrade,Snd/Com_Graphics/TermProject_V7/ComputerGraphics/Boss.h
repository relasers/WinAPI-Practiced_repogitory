#pragma once
#include "MyObject.h"
#include "M_HexTechTower.h"

#define Drone_Create_Tick 4

class CEnemy;
class Cbullet;
class CBossLauncher;
class CBoss : public CMyObject
{
private:
	C_M_HexTechTower m_Model;

	Vec3f m_vDirection;
	CCube m_BindingCube;
	CCube m_CoreBindCube;
	CCube m_RoofBindCube;

	CPlayer * m_Target;

	int m_Hp = 1000;
	int m_Barrier = 10;
	float m_DroneCreateTimer = 0.0f;

	float m_HitTimer = 0.0f;
	float m_RepairTimer = 0.0f;

	CBossLauncher * m_launcher;
	std::list<class Cbullet*>* m_bullets;
	std::list<class CEnemy*>* m_EnemyList;
public:
	CBoss();
	CBoss(CPlayer * target, std::list<class Cbullet*>& bullets, std::list<class CEnergyBolt*>& energy_bolts, std::list<class CEnemy*>& enemys);
	~CBoss();

	CCube& Get_BindCube() { return m_BindingCube; }
	CCube& Get_CoreBindCube() { return m_CoreBindCube; }
	CCube& Get_RoofBindCube() { return m_RoofBindCube; }

	const int GetHP() const { return m_Hp; }

	void Hit(int damage);

	virtual void Update(const float fTimeElapsed);
	virtual void Rendering();

	virtual void Translate(const Vec3f move) { m_vCenter += move; }
	virtual void Rotate(const float angle, bool x, bool y, bool z);
};

