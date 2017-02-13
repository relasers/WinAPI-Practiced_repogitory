#pragma once
#include "Launcher.h"

class CBossLauncher : public CLauncher
{
private:
	float m_size{ 32 };
	float m_energybolt_tick = 0.0f;
	int m_state{0};
	std::list<class CEnergyBolt*>* m_energybolts;
public:
	CBossLauncher();
	CBossLauncher(list<Cbullet*>& bullets, list<CEnergyBolt*>& energy_bolts, Vec3f pt, CPlayer * target);
	~CBossLauncher();

	virtual bool Update(const float fTimeElapsed);

	void SetPos(Vec3f pt) { m_pt = pt; }
	void SetCoolTime(float cooltime) { m_cooltime = cooltime; }
};

