#include "stdafx.h"
#include "Particle.h"


CParticle::CParticle()
{
}

CParticle::CParticle(Vec3f pt)
{
	m_pt = pt;
	Vec3f dir{ -128 + float(rand() % 256),-128 + float(rand() % 256),-128 + float(rand() % 256) };
	m_dir = dir - m_pt;
	Normalize(m_dir);
	m_speed = 50 + rand() % 32;
}


CParticle::~CParticle()
{
}

bool CParticle::Update(const float fTimeElapsed)
{
	m_lifetime -= 400.0f*fTimeElapsed;
	m_alpha -= 0.003;
	m_angle += 60.0f * fTimeElapsed;

	m_pt += m_dir*m_speed*fTimeElapsed;
	m_speed = max(1, m_speed - 0.01*fTimeElapsed);
	if (m_lifetime <= 0) m_bDie = true;
	return false;
}

void CParticle::Rander()
{
	glPushMatrix();
	{
		glTranslatef(m_pt.x, m_pt.y, m_pt.z);
		glColor4f(rand() % 10 * 0.1f, rand() % 10 * 0.1f, rand() % 10 * 0.1f,m_alpha);
		glRotatef(m_angle, 1, 1, 1);
		glutWireCube(m_lifetime*0.6);
		glutSolidSphere(m_lifetime*0.3, 6, 6);
	}
	glPopMatrix();
}
