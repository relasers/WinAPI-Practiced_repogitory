#pragma once
#include "stdafx.h"
#include "BossLauncher.h"
#include "RanderProp.h"

CBossLauncher::CBossLauncher()
{
}

CBossLauncher::CBossLauncher(list<Cbullet*>& bullets, list<CEnergyBolt*>& energy_bolts, Vec3f pt, CPlayer * target)
{
	m_pt = pt;
	m_Target = target;
	m_bullets = &bullets;
	m_energybolts = &energy_bolts;
}


CBossLauncher::~CBossLauncher()
{

}

bool CBossLauncher::Update(const float fTimeElapsed)
{
	
	m_shoot_tick += fTimeElapsed;
	m_energybolt_tick += fTimeElapsed;

	if (m_shoot_tick > m_cooltime*0.1) {
		Vec3f target = m_Target->GetCenter();
		target.x += -128 + rand() % 256;
		target.y += -128 + rand() % 256;
		target.z += -128 + rand() % 256;

		m_bullets->push_back(new Cbullet(m_pt, target, m_speed, m_size, true, COLOR_EGGYOLK,false));
		//std::cout << "m_bullets :: " << m_bullets->size() << std::endl;
		m_shoot_tick = 0.0f;
	}

	if (m_energybolt_tick > m_cooltime) {

		for (int i = 0; i < 4; ++i) {
			Vec3f target = m_Target->GetCenter();
			target.x += -128 + rand() % 256 + cos(i * 90 * PI / 180.0) * 1280;
			target.y += -128 + rand() % 256;
			target.z += -128 + rand() % 256 + sin(i * 90 * PI / 180.0) * 1280;

			m_energybolts->push_back(new CEnergyBolt(m_pt, target, m_speed * 5, m_size, COLOR_RED, *m_bullets));

		}
				//std::cout << "m_bullets :: " << m_bullets->size() << std::endl;
		m_energybolt_tick = 0.0f;
	}
	return false;




}
