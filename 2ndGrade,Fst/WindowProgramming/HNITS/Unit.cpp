#include "stdafx.h"
#include "Unit.h"

CUnit::CUnit(CSoundManager *sm , float fFrequency)
{
	m_pSound = sm;
	// 1ȸ ȣ�� �� ������ �ӷ�
	m_fSpeed = 4.0f;
	
	m_fFrequency = fFrequency;
	m_fTick = 0.f;
}
CUnit::~CUnit()
{
}

void CUnit::OnDraw(HDC hDC)
{
}

void CUnit::OnUpdate(float fTimeElapsed)
{
	m_fTick += fTimeElapsed;
	if (m_fTick < m_fFrequency) return;
	m_fTick -= m_fFrequency;

}

void CUnit::MoveToTaget(float fTimeElapsed)
{
	// move ���·� ����
	//m_sprite.UpdateState(CAnimationSprite::SpriteState::sprite_state_move);
	// ���� ������ ��쿡�� ����(�غ� �ڼ��̱� ����)
	//if (m_sprite.GetCurrentStateState() == CAnimationSprite::StateState::state_state_excute) return;

	// �̵�
	//POINT Enemy_Pos = m_ClosedEnemy->Get_UnitStatus_Pos();

	if (true)// Ÿ�ٰ��� �Ÿ�
	{
		m_fMoveLength += m_fSpeed * fTimeElapsed;

		if (m_fMoveLength >= 1)
		{
			m_ptCurrent.x++;
			m_fMoveLength = 0;
		}
		if (m_fMoveLength <= -1)
		{
			m_ptCurrent.x--;
			m_fMoveLength = 0;
		}
	}
	if (m_ptCurrent.x < 0) m_ptCurrent.x = 0;
	if (m_ptCurrent.y < 0) m_ptCurrent.y = 0;
}


