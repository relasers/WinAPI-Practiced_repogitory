#include "stdafx.h"
#include "M_CombatDrone.h"
#include "Enemy.h"


CEnemy::CEnemy()
{
}

CEnemy::CEnemy(Vec3f &pos, CPlayer * target, std::list<class Cbullet*>& bullets)
{
	m_vCenter = pos;
	m_Target = target;
	m_BindingCube.Scale(Vec3f{42, 42, 42});
	m_launcher = new CLauncher(bullets, m_vCenter, m_Target);
}
CEnemy::~CEnemy()
{
}

void CEnemy::Hit(int damage)
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

void CEnemy::Update(const float fTimeElapsed)
{
	m_launcher->SetPos(m_vCenter);
	m_launcher->Update(fTimeElapsed);

	m_Model.Update(fTimeElapsed);
	m_BindingCube.SetPos(m_vCenter);
	m_Timer += fTimeElapsed;
	if (m_Timer > Turning_Speed)
	{
		m_vDirection = Normalize(m_vDirection + Normalize(m_Target->GetCenter() - m_vCenter));
		m_Timer = 0.0f;
	}
	m_HitTimer += fTimeElapsed;
	if (m_HitTimer > HitTime)
	{
		m_RepairTimer += fTimeElapsed;
		if (m_RepairTimer > BarrierRepair)
		{
			m_RepairTimer = 0.0f;
			m_Barrier++;
		}
	}
	m_vCenter += m_speed * m_vDirection * fTimeElapsed;
	if (m_Hp <= 0) m_bDie = true;
}

void CEnemy::Rendering()
{
	glPushMatrix();
	glTranslatef(m_vCenter.x, m_vCenter.y, m_vCenter.z);
	glMultMatrixf(m_fRotateMatrix);
	m_Model.Rander();
	//glTranslatef(-m_vCenter.x, -m_vCenter.y, -m_vCenter.z);
	//m_BindingCube.Rend_BB();
	glPopMatrix();
}

void CEnemy::Rotate(const float angle, bool x, bool y, bool z)
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
