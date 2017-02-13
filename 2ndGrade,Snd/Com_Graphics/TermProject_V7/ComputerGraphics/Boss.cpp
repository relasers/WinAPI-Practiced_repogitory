#include "stdafx.h"
#include "M_HexTechTower.h"
#include "Boss.h"


CBoss::CBoss()
{
}
CBoss::CBoss(CPlayer * target, std::list<class Cbullet*>& bullets, std::list<class CEnergyBolt*>& energy_bolts, std::list<class CEnemy*>& enemys)
{
	m_vCenter = {0.0f, 1024.0f, 0.0f};
	m_Target = target;
	m_BindingCube.Scale(Vec3f{ 200, 1024.0f, 200 });
	m_CoreBindCube.Scale(Vec3f{ 150, 200.0f, 150 });
	m_CoreBindCube.Translate(Vec3f{ 0.0f, 1000.0f, 0.0f });
	m_RoofBindCube.Scale(Vec3f{ 200, 200.0f, 200 });
	m_RoofBindCube.Translate(Vec3f{ 0.0f, 1624.0f, 0.0f });
	m_bullets = &bullets;
	m_EnemyList = &enemys;
	m_launcher = new CBossLauncher(bullets, energy_bolts,{0.0f,1536.f,0.0f}, m_Target);
	m_bDie = false;
	m_Hp = 1000;
	m_Barrier = 10;
}
CBoss::~CBoss()
{
}

void CBoss::Hit(int damage)
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

void CBoss::Update(const float fTimeElapsed)
{
	//m_launcher->SetPos(m_vCenter);
	if (500 < m_Hp && m_Hp < 750.0f) {
		m_launcher->SetCoolTime(7.5f);
	}
	else if (250 < m_Hp && m_Hp < 500.0f) {
		m_launcher->SetCoolTime(5.0f);
	}
	else if (m_Hp < 250.0f) {
		m_launcher->SetCoolTime(2.5f);
	}

	m_launcher->Update(fTimeElapsed);
	m_DroneCreateTimer += fTimeElapsed;
	if (m_DroneCreateTimer > Drone_Create_Tick) {
		Vec3f CreatePos = m_vCenter;
		CreatePos.y -= 256.f;
		m_EnemyList->push_back(new CEnemy(CreatePos, m_Target, *m_bullets));
		m_DroneCreateTimer = 0.0f;
	}

	m_Model.Update(fTimeElapsed);
	m_vDirection=Normalize(m_Target->GetCenter() - m_vCenter);

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
	if (m_Hp <= 0) m_bDie = true;
}

void CBoss::Rendering()
{
	glPushMatrix();
	glTranslatef(m_vCenter.x, m_vCenter.y, m_vCenter.z);
	glMultMatrixf(m_fRotateMatrix);
	m_Model.Rander();
	//glTranslatef(-m_vCenter.x, -m_vCenter.y, -m_vCenter.z);
	//m_CoreBindCube.Rend_BB();
	//m_BindingCube.Rend_BB();
	//m_RoofBindCube.Rend_BB();
	glPopMatrix();
}

void CBoss::Rotate(const float angle, bool x, bool y, bool z)
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
