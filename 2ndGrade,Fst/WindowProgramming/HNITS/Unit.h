#pragma once
#include <Windows.h>
#include "SpriteImage.h"
#include "SoundManager.h"
#include "Vec2f.h"
#include "WarpList.h"

class CUnit
{
protected:

	CSoundManager		*m_pSound;

	POINT				m_ptCurrent{0, 0}; // ������ġ
	float				m_fCurrentUpdate{ 0 }; // ����ī����
	float				m_fCurrentAttack{ 0 }; // ����ī����
	float				m_fCurrentJump{ 0 }; // ����ī����
	float				m_fCurrentHit{ 0 }; // �ǰ�ī����
	float				m_fCurrentDie{ 0 }; // ���� �� ���������� ī����

	float				m_fMoveLength{ 0 }; // �����̵��Ÿ� < 1
	float				m_Gravity_AC{ 0 }; // �������ӵ�

	bool				m_Togle{ false }; // �����ڽ� on / off
	bool				m_Die{ false };
	// ���� �������� �ڽ�
	RECT m_bodybox{ 0, 0, 0, 0 };
	RECT m_atkbox{ 0, 0, 0, 0 };

	// ���� ���� �÷���
	bool m_Attack{ false };
	bool m_bJump{ false };
	bool m_bLeft{ false };
	bool m_Sound{ false };

	// ���� ���� �������ͽ�
	int m_MaxHP{ 0 };
	int m_prev_HP{ 0 };
	int m_HP{ 0 };
	int m_ATK{ 0 };
	int m_DEF{ 0 };
	float m_fSpeed{ 0 };

	// ���� ���� ����(millisec)
	float m_fFrequency = 1.0f / 60.0f;
	float m_fTick = 0.f;
public:

	CUnit(CSoundManager *sm, float fFrequency = 1.0f / 60.0f);
	virtual ~CUnit();

	virtual void OnDraw(HDC hDC);
	virtual void OnUpdate(float fTimeElapsed);
	virtual void Tageting() {}

	virtual void ReSet() = 0;

	void SetTogle(bool togle = false) { m_Togle = togle; }

	// ���� �������ͽ� ��ȯ
	const int GetMaxHP() const { return m_MaxHP; }
	const int GetHP() const { return m_HP; }
	int& GetHP() { return m_HP; }
	const int GetATK() const { return m_ATK; }
	const int GetDEF() const { return m_DEF; }

	// ���� ��ġ���� ��ȯ
	const POINT GetPos() const { return m_ptCurrent; }
	RECT GetBodybox() const { return m_bodybox; }
	RECT GetAtkbox() const { return m_atkbox; }

	const bool IsDie() const { return m_Die; }
protected:

	virtual void MoveToTaget(float fTimeElapsed);
};


