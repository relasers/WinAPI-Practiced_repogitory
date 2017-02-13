#pragma once

#ifndef MX_LIFETIME
#define MX_LIFETIME 300
#endif

class CParticle
{
private:
	Vec3f m_pt{};
	Vec3f m_dir{};
	float m_size{64};
	float m_speed{50};
	float m_alpha{1.0f};
	float m_lifetime{300};
	float m_angle{};
	bool m_bDie = false;

public:
	CParticle();
	CParticle(Vec3f pt);
	~CParticle();

	bool IsDie() { return m_bDie; }

	bool Update(const float fTimeElapsed);
	void Rander();

	float GetLife() const { return m_lifetime; }
};

