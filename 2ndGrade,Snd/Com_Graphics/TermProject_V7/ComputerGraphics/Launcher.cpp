#pragma once

#include "stdafx.h"
#include "Launcher.h"
#include "RanderProp.h"

CLauncher::CLauncher()
{

}


CLauncher::CLauncher(list<Cbullet*>& bullets,Vec3f pt, CPlayer * target)
{
	m_pt = pt;
	m_Target = target;
	m_bullets = &bullets;
}



CLauncher::~CLauncher()
{
}

bool CLauncher::Update(const float fTimeElapsed)
{
	m_shoot_tick += 1.f*fTimeElapsed;

	if (m_shoot_tick > m_cooltime) {
		m_bullets->push_back(new Cbullet(m_pt, m_Target->GetCenter(),m_speed, m_size,false, COLOR_WINE,false));
		//std::cout << "m_bullets :: " << m_bullets->size() << std::endl;
		m_shoot_tick = 0.0f;
	}
	return false;
}

void CLauncher::Rander()
{
}
