#include "stdafx.h"
#include "Player.h"
#include "RanderProp.h"
CPlayer::CPlayer()
{
	m_vDirection = { 0.0f, 0.0f, 1.0f };
	m_bDie = false;
	m_Barrier = 100;
	m_Hp = 100;
}
CPlayer::CPlayer(std::list<Cbullet*>& ally_bullets)
{
	m_vCenter = { 0.0f, 1000.0f, -1024.0f };
	m_ally_bullets = &ally_bullets;
	m_vDirection = { 0.0f, 0.0f, 1.0f };
	m_bDie = false;
	m_Barrier = 100;
	m_Hp = 5;
}
CPlayer::~CPlayer()
{
}

void CPlayer::Hit(int damage)
{
	if (m_Barrier <= 0)
	{
		m_Hp--;
		m_Barrier = 0;
		if (m_Hp < 0) m_Hp = 0;
	}
	else m_Barrier -= damage;
	m_HitTimer = 0.0f;
}

void CPlayer::Reset()
{
	m_bDie = false;
	m_Hp = 5;
	m_Barrier = 100;
}

void CPlayer::RotateToDirection(Vec3f & look, Vec3f& angle)
{
	m_Angle = angle;
	m_Angle.y -= PI * 0.5f;

	for (int i = 0; i < 16; i++) m_fRotateMatrix[i] = 0;
	for (int i = 0; i < 4; i++) m_fRotateMatrix[i * 4 + i] = 1;
	glPushMatrix();
	glLoadIdentity();
	glRotatef(-m_Angle.x*degree_per_one_radius, 1.0f, 0.0f, 0.0f);
	glMultMatrixf(m_fRotateMatrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_fRotateMatrix);
	glPopMatrix();
	glPushMatrix();
	glLoadIdentity();
	glRotatef(-m_Angle.y*degree_per_one_radius, 0.0f, 1.0f, 0.0f);
	glMultMatrixf(m_fRotateMatrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_fRotateMatrix);
	glPopMatrix();
	m_vDirection = look;
}

void CPlayer::Update(const float fTimeElapsed)
{
	m_Model.Update(fTimeElapsed);

	if (m_shoot_tick < P_SHOOTTICK) m_shoot_tick += fTimeElapsed;
	if (m_isShooting && m_shoot_tick >= P_SHOOTTICK) {

		Vec3f dir = { m_vDirection.z, m_vDirection.y, -m_vDirection.x };

		Vec3f launchPos{};
		
		launchPos.x = m_Model.GetSize()*1.70f*dir.x;
		launchPos.z = m_Model.GetSize()*1.70f*dir.z;

		m_ally_bullets->push_back(new Cbullet(m_vCenter + launchPos, m_vCenter + launchPos + m_vDirection, 1600, m_Model.GetSize()*0.25, true, COLOR_JADE, true));
		m_ally_bullets->push_back(new Cbullet(m_vCenter - launchPos, m_vCenter - launchPos + m_vDirection, 1600, m_Model.GetSize()*0.25, true, COLOR_JADE, true));
		m_shoot_tick = 0.0f;
	}
	if (m_bBoost)
	{
		if(m_Boost > 0)
			m_Speed = 600.0f;
		m_BoostTimer += fTimeElapsed;
		if (m_BoostTimer > BOOSTTIME)
		{
			m_Boost--;
			m_BoostTimer = 0.0f;
			if (m_Boost < 0) m_Boost = 0;
		}
		
	}
	else
	{
		m_Speed = 200.0f;
		m_BoostTimer += fTimeElapsed;
		if (m_BoostTimer > BOOSTTIME * 10)
		{
			m_Boost++;
			m_BoostTimer = 0.0f;
			if (m_Boost > 100) m_Boost = 100;
		}
	}
	m_HitTimer += fTimeElapsed;
	if (m_HitTimer > HitTime)
	{
		m_RepairTimer += fTimeElapsed;
		if (m_RepairTimer > BarrierRepair)
		{
			m_RepairTimer = 0.0f;
			m_Barrier++;
			if (m_Barrier > 100) m_Barrier = 100;
		}
	}
		
	if (m_Hp <= 0) m_bDie = true;
}

void CPlayer::Rendering()
{
	glPushMatrix();
	glTranslatef(m_vCenter.x, m_vCenter.y, m_vCenter.z);
	glMultMatrixf(m_fRotateMatrix);
	m_Model.Rander(m_isShooting);
	//glTranslatef(-m_vCenter.x, -m_vCenter.y, -m_vCenter.z);
	//m_BindingCube.Rend_BB();
	glPopMatrix();
}

void CPlayer::Rotate(const float angle, bool x, bool y, bool z)
{
	glPushMatrix();
	glLoadIdentity();
	if (x)
	{
		glRotatef(angle, 1.0f, 0.0f, 0.0f);
		m_Angle.x += angle;
	}
	if (y)
	{
		glRotatef(angle, 0.0f, 1.0f, 0.0f);
		m_Angle.y += angle;
	}
	if (z)
	{
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		m_Angle.z += angle;
	}
	glMultMatrixf(m_fRotateMatrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_fRotateMatrix);
	glPopMatrix();
}
