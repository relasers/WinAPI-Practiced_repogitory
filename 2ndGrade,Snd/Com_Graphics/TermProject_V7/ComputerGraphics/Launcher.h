#pragma once

class Cbullet;
class CLauncher
{
protected:

	Vec3f m_pt{};
	CPlayer * m_Target;

	float m_shoot_tick{};
	float m_speed{ 512 };
	float m_size{ 16 };

	// 간격 조절용
	float m_cooltime = 10;

	std::list<class Cbullet*>* m_bullets;

public:
	CLauncher();
	CLauncher(std::list<class Cbullet*>& bullets,Vec3f pt, CPlayer * m_Target);
	~CLauncher();
	
	virtual bool Update(const float fTimeElapsed);
	virtual void Rander();
	
	void SetPos(Vec3f pt) { m_pt = pt; }

};

