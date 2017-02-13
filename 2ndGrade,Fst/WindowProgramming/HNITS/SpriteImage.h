#pragma once

#include <windows.h>
#include <atlImage.h>

class CSpriteImage
{

protected:

	CImage m_ciSpriteImage;

	int m_nFrameXNum;
	int m_nFrameYNum;

	int m_nFrameWidthSize;
	int m_nFrameHeightSize;

	POINT m_ptCurrentAnimationState{ 0,0 };

	COLORREF m_colTransparent;

	bool m_Build{ false };
public:
	CSpriteImage(LPCTSTR path, int w, int h);
	virtual ~CSpriteImage();
	
	virtual void OnUpdate();

	virtual void Draw(HDC hDC, int x, int y);
	virtual void Draw(HDC hDC, int x, int y, int w, int h);
};


/*
	class CAnimationSprite
	- Ⱦ��ũ��(��, ��) ���� �ִϸ��̼� ��������Ʈ Ŭ����

	- ���¸� �����Ͽ� �̹����� ���¿� ���� ó���� �� �ְ� ����
	- �̹����� Ȧ�� ��° : ������ ���� / ¦�� ��° : ���� �������� ��ġ �ʿ�
	- ���� ���� ����, ���� ���� ����, ���� ���� ���¿� ���� �� ������ ����
	- �ܼ��� ���� - ������ �������� �ʾƵ� ��� ����
	
*/
class CAnimationSprite : public CSpriteImage
{
public:
	// Sprite State : ĳ������ ���� ����
	// �ʿ信 ���� ���� �ʿ�
	typedef enum {
		  sprite_state_idle = 0
		, sprite_state_move
		, sprite_state_jump
		, sprite_state_attack_0
		, sprite_state_attack_1
		, sprite_state_attack_2
		, sprite_state_attack_3
		, sprite_state_dash
		, sprite_state_jump_attack
		, sprite_state_guard
		, sprite_state_parrying
		, sprite_state_hit
		, sprite_state_shot
		, sprite_state_count
	}SpriteState;

	// ������ ����(����/����/����)
	// �������� ���ÿ�
	typedef enum {
		  state_state_excute = 0
		, state_state_action
		, state_state_exit
		
	}StateState;

protected:

	// ���¿� ���� ��ü �̹��� ��
	int m_iMaxState		[SpriteState::sprite_state_count];
	// ���¿� ���� �� �̹����� �ִϸ��̼� ������
	// ���� - ���� - ���� ������ ���
	// ����-���� ���°� ������ 0
	int m_iStateDelay	[SpriteState::sprite_state_count][3];

	// ���¿� ���� ���� ������ ���۰� �� �̹��� ��ȣ
	int m_iStateExcute	[SpriteState::sprite_state_count][2];
	// ���¿� ���� ���� ������ ���۰� �� �̹��� ��ȣ
	int m_iStateAction	[SpriteState::sprite_state_count][2];
	// ���¿� ���� ���� ������ ���۰� �� �̹��� ��ȣ
	int m_iStateExit	[SpriteState::sprite_state_count][2];

	// ���� ����
	SpriteState m_stCurrent = sprite_state_idle;
	// ���� ���� : ���� ���� ���� �� �����ߴٰ� ���� ���� ���� �� ���� ���·� ����
	SpriteState m_stNext = sprite_state_idle;

	// ������ ī����
	// m_iStateDelay�� ����� ����ŭ Update�� ����
	// Update�� ���� ���� �ִϸ��̼� ���� ���� 
	// = ���� �̹����� ���� �ε巯�� �ִϸ��̼� ȿ�� ���� ����
	int m_nCount = 0;

	// ���� ����
	bool m_bLeft = false;
public:

	CAnimationSprite(LPCTSTR path, int w, int h);
	virtual ~CAnimationSprite();

	// State �� ���� : ���� ������ �̹��� ��ȣ ����. ���� - ���� ���°� ���� �� ���
	void SetState(SpriteState s, int val);
	// State �� ���� : ��� ������ �̹��� ��ȣ ����. ���� ���´� ���� - ���� ������ ���� ���� ����
	void SetState(SpriteState s, int val, int excute_start, int excute_end, int exit_start, int exit_end);
	
	// Delay �� ���� : ���� - ���� - ���� ������ Delay �� ����
	void SetStateDelay(SpriteState s, int excute, int action, int exit)
	{ m_iStateDelay[s][0] = excute; m_iStateDelay[s][1] = action; m_iStateDelay[s][2] = exit; }
	// Delay �� ���� : ���� ������ Delay �� ����. ������ ���� Delay�� 0.
	void SetStateDelay(SpriteState s, int val)
	{ m_iStateDelay[s][0] = 0; m_iStateDelay[s][1] = val; m_iStateDelay[s][2] = 0; }
	// ���ڷ� �Ѱܹ��� ���·� ����
	void UpdateState(SpriteState s);
	
	// ���� ������ �˷��ִ� Getter �Լ�
	bool IsLeft() const { return m_bLeft; }
	// ������ �����ϴ� Setter �Լ�
	void SetDirection(bool bLeft);

	// ���°� ������ ���� - ���� - ���� �̹��� ���� ���� ��ȯ
	int GetMaxState(SpriteState s) const { return m_iMaxState[s]; }

	// ���� ���¸� ��ȯ
	SpriteState GetCurrentState() const { return m_stCurrent; }
	// ���� ���°� � ��������(���� - ���� - ����) ��ȯ
	StateState GetCurrentStateState() const;
	// ���� ������� �̹��� ��ȣ�� ��ȯ
	LONG GetCurrentAnimationCount() const { return m_ptCurrentAnimationState.x; }

	// ����
	virtual void OnUpdate();

	// �׸���
	virtual void Draw(HDC hDC, int x, int y);
};

class CEnemyAnimationSprite : public CSpriteImage
{
public:
	// Sprite State : ĳ������ ���� ����
	// �ʿ信 ���� ���� �ʿ�
	typedef enum {
		sprite_state_idle = 0
		, sprite_state_move
		, sprite_state_attack
		, sprite_state_guard
		, sprite_state_hit
		, sprite_state_pop
		, sprite_state_count
	}ESpriteState;

	// ������ ����(����/����/����)
	// �������� ���ÿ�
	typedef enum {
		state_state_excute = 0
		, state_state_action
		, state_state_exit

	}StateState;

protected:

	// ���¿� ���� ��ü �̹��� ��
	int m_iMaxState[ESpriteState::sprite_state_count];
	// ���¿� ���� �� �̹����� �ִϸ��̼� ������
	// ���� - ���� - ���� ������ ���
	// ����-���� ���°� ������ 0
	int m_iStateDelay[ESpriteState::sprite_state_count][3];

	// ���¿� ���� ���� ������ ���۰� �� �̹��� ��ȣ
	int m_iStateExcute[ESpriteState::sprite_state_count][2];
	// ���¿� ���� ���� ������ ���۰� �� �̹��� ��ȣ
	int m_iStateAction[ESpriteState::sprite_state_count][2];
	// ���¿� ���� ���� ������ ���۰� �� �̹��� ��ȣ
	int m_iStateExit[ESpriteState::sprite_state_count][2];

	// ���� ����
	ESpriteState m_stCurrent{ sprite_state_pop };
	// ���� ���� : ���� ���� ���� �� �����ߴٰ� ���� ���� ���� �� ���� ���·� ����
	ESpriteState m_stNext = sprite_state_idle;

	// ������ ī����
	// m_iStateDelay�� ����� ����ŭ Update�� ����
	// Update�� ���� ���� �ִϸ��̼� ���� ���� 
	// = ���� �̹����� ���� �ε巯�� �ִϸ��̼� ȿ�� ���� ����
	int m_nCount = 0;

	// ���� ����
	bool m_bLeft{ true };
public:

	CEnemyAnimationSprite(LPCTSTR path, int w, int h);
	virtual ~CEnemyAnimationSprite();

	// State �� ���� : ���� ������ �̹��� ��ȣ ����. ���� - ���� ���°� ���� �� ���
	void SetState(ESpriteState s, int val);
	// State �� ���� : ��� ������ �̹��� ��ȣ ����. ���� ���´� ���� - ���� ������ ���� ���� ����
	void SetState(ESpriteState s, int val, int excute_start, int excute_end, int exit_start, int exit_end);

	// Delay �� ���� : ���� - ���� - ���� ������ Delay �� ����
	void SetStateDelay(ESpriteState s, int excute, int action, int exit)
	{
		m_iStateDelay[s][0] = excute; m_iStateDelay[s][1] = action; m_iStateDelay[s][2] = exit;
	}
	// Delay �� ���� : ���� ������ Delay �� ����. ������ ���� Delay�� 0.
	void SetStateDelay(ESpriteState s, int val)
	{
		m_iStateDelay[s][0] = 0; m_iStateDelay[s][1] = val; m_iStateDelay[s][2] = 0;
	}
	// ���ڷ� �Ѱܹ��� ���·� ����
	void UpdateState(ESpriteState s);

	// ���� ������ �˷��ִ� Getter �Լ�
	bool IsLeft() const { return m_bLeft; }
	// ������ �����ϴ� Setter �Լ�
	void SetDirection(bool bLeft);

	// ���°� ������ ���� - ���� - ���� �̹��� ���� ���� ��ȯ
	int GetMaxState(ESpriteState s) const { return m_iMaxState[s]; }
	// ���� ���¸� ��ȯ
	ESpriteState GetCurrentState() const { return m_stCurrent; }
	// ���� ������� �̹��� ��ȣ�� ��ȯ
	LONG GetCurrentAnimationCount() const { return m_ptCurrentAnimationState.x; }
	// ���� ���°� � ��������(���� - ���� - ����) ��ȯ
	StateState GetCurrentStateState() const;

	// ����
	virtual void OnUpdate(bool reset = false);

	// �׸���
	virtual void Draw(HDC hDC, int x, int y);
};
class CEnemyArcher_AnimationSprite : public CSpriteImage
{
public:
	// Sprite State : ĳ������ ���� ����
	// �ʿ信 ���� ���� �ʿ�
	typedef enum {
		sprite_state_idle = 0
		, sprite_state_move
		, sprite_state_attack
		, sprite_state_shot
		, sprite_state_hit
		, sprite_state_pop
		, sprite_state_count
	}ESpriteState;

	// ������ ����(����/����/����)
	// �������� ���ÿ�
	typedef enum {
		state_state_excute = 0
		, state_state_action
		, state_state_exit

	}StateState;

protected:

	// ���¿� ���� ��ü �̹��� ��
	int m_iMaxState[ESpriteState::sprite_state_count];
	// ���¿� ���� �� �̹����� �ִϸ��̼� ������
	// ���� - ���� - ���� ������ ���
	// ����-���� ���°� ������ 0
	int m_iStateDelay[ESpriteState::sprite_state_count][3];

	// ���¿� ���� ���� ������ ���۰� �� �̹��� ��ȣ
	int m_iStateExcute[ESpriteState::sprite_state_count][2];
	// ���¿� ���� ���� ������ ���۰� �� �̹��� ��ȣ
	int m_iStateAction[ESpriteState::sprite_state_count][2];
	// ���¿� ���� ���� ������ ���۰� �� �̹��� ��ȣ
	int m_iStateExit[ESpriteState::sprite_state_count][2];

	// ���� ����
	ESpriteState m_stCurrent = sprite_state_pop;
	// ���� ���� : ���� ���� ���� �� �����ߴٰ� ���� ���� ���� �� ���� ���·� ����
	ESpriteState m_stNext = sprite_state_idle;

	// ������ ī����
	// m_iStateDelay�� ����� ����ŭ Update�� ����
	// Update�� ���� ���� �ִϸ��̼� ���� ���� 
	// = ���� �̹����� ���� �ε巯�� �ִϸ��̼� ȿ�� ���� ����
	int m_nCount = 0;

	// ���� ����
	bool m_bLeft = true;
public:

	CEnemyArcher_AnimationSprite(LPCTSTR path, int w, int h);
	virtual ~CEnemyArcher_AnimationSprite();

	// State �� ���� : ���� ������ �̹��� ��ȣ ����. ���� - ���� ���°� ���� �� ���
	void SetState(ESpriteState s, int val);
	// State �� ���� : ��� ������ �̹��� ��ȣ ����. ���� ���´� ���� - ���� ������ ���� ���� ����
	void SetState(ESpriteState s, int val, int excute_start, int excute_end, int exit_start, int exit_end);

	// Delay �� ���� : ���� - ���� - ���� ������ Delay �� ����
	void SetStateDelay(ESpriteState s, int excute, int action, int exit)
	{
		m_iStateDelay[s][0] = excute; m_iStateDelay[s][1] = action; m_iStateDelay[s][2] = exit;
	}
	// Delay �� ���� : ���� ������ Delay �� ����. ������ ���� Delay�� 0.
	void SetStateDelay(ESpriteState s, int val)
	{
		m_iStateDelay[s][0] = 0; m_iStateDelay[s][1] = val; m_iStateDelay[s][2] = 0;
	}
	// ���ڷ� �Ѱܹ��� ���·� ����
	void UpdateState(ESpriteState s);

	// ���� ������ �˷��ִ� Getter �Լ�
	bool IsLeft() const { return m_bLeft; }
	// ������ �����ϴ� Setter �Լ�
	void SetDirection(bool bLeft);

	// ���°� ������ ���� - ���� - ���� �̹��� ���� ���� ��ȯ
	int GetMaxState(ESpriteState s) const { return m_iMaxState[s]; }
	// ���� ���¸� ��ȯ
	ESpriteState GetCurrentState() const { return m_stCurrent; }
	// ���� ������� �̹��� ��ȣ�� ��ȯ
	LONG GetCurrentAnimationCount() const { return m_ptCurrentAnimationState.x; }
	// ���� ���°� � ��������(���� - ���� - ����) ��ȯ
	StateState GetCurrentStateState() const;

	// ����
	virtual void OnUpdate(bool reset = false);

	// �׸���
	virtual void Draw(HDC hDC, int x, int y);
};

class CBOSSAnimationSprite : public CSpriteImage
{
public:
	// Sprite State : ĳ������ ���� ����
	// �ʿ信 ���� ���� �ʿ�
	typedef enum {
		  sprite_state_phase1_idle = 0
		, sprite_state_phase1_hit
		, sprite_state_phase2_shift
		, sprite_state_phase2_idle
		, sprite_state_phase2_summon
		, sprite_state_phase2_attack
		, sprite_state_phase2_hit
		, sprite_state_phase3_shift
		, sprite_state_phase3_idle
		, sprite_state_phase3_dash_ready
		, sprite_state_phase3_dash
		, sprite_state_phase3_attack
		, sprite_state_phase3_die
		, sprite_state_count
	}SpriteState;

	// ������ ����(����/����/����)
	// �������� ���ÿ�
	typedef enum {
		state_state_excute = 0
		, state_state_action
		, state_state_exit

	}StateState;

protected:

	// ���¿� ���� ��ü �̹��� ��
	int m_iMaxState[SpriteState::sprite_state_count];
	// ���¿� ���� �� �̹����� �ִϸ��̼� ������
	// ���� - ���� - ���� ������ ���
	// ����-���� ���°� ������ 0
	int m_iStateDelay[SpriteState::sprite_state_count][3];

	// ���¿� ���� ���� ������ ���۰� �� �̹��� ��ȣ
	int m_iStateExcute[SpriteState::sprite_state_count][2];
	// ���¿� ���� ���� ������ ���۰� �� �̹��� ��ȣ
	int m_iStateAction[SpriteState::sprite_state_count][2];
	// ���¿� ���� ���� ������ ���۰� �� �̹��� ��ȣ
	int m_iStateExit[SpriteState::sprite_state_count][2];

	// ���� ����
	SpriteState m_stCurrent = sprite_state_phase1_idle;
	// ���� ���� : ���� ���� ���� �� �����ߴٰ� ���� ���� ���� �� ���� ���·� ����
	SpriteState m_stNext = sprite_state_phase1_idle;

	// ������ ī����
	// m_iStateDelay�� ����� ����ŭ Update�� ����
	// Update�� ���� ���� �ִϸ��̼� ���� ���� 
	// = ���� �̹����� ���� �ε巯�� �ִϸ��̼� ȿ�� ���� ����
	int m_nCount = 0;

	// ���� ����
	bool m_bLeft = false;
	int m_phase = 1;
public:

	CBOSSAnimationSprite(LPCTSTR path, int w, int h);
	virtual ~CBOSSAnimationSprite();

	// State �� ���� : ���� ������ �̹��� ��ȣ ����. ���� - ���� ���°� ���� �� ���
	void SetState(SpriteState s, int val);
	// State �� ���� : ��� ������ �̹��� ��ȣ ����. ���� ���´� ���� - ���� ������ ���� ���� ����
	void SetState(SpriteState s, int val, int excute_start, int excute_end, int exit_start, int exit_end);

	// Delay �� ���� : ���� - ���� - ���� ������ Delay �� ����
	void SetStateDelay(SpriteState s, int excute, int action, int exit)
	{
		m_iStateDelay[s][0] = excute; m_iStateDelay[s][1] = action; m_iStateDelay[s][2] = exit;
	}
	// Delay �� ���� : ���� ������ Delay �� ����. ������ ���� Delay�� 0.
	void SetStateDelay(SpriteState s, int val)
	{
		m_iStateDelay[s][0] = 0; m_iStateDelay[s][1] = val; m_iStateDelay[s][2] = 0;
	}
	// ���ڷ� �Ѱܹ��� ���·� ����
	void UpdateState(SpriteState s);

	void SetPhase(int phase) { m_phase = phase; }
	// ���� ������ �˷��ִ� Getter �Լ�
	bool IsLeft() const { return m_bLeft; }
	// ������ �����ϴ� Setter �Լ�
	void SetDirection(bool bLeft);

	// ���°� ������ ���� - ���� - ���� �̹��� ���� ���� ��ȯ
	int GetMaxState(SpriteState s) const { return m_iMaxState[s]; }
	// ���� ���¸� ��ȯ
	SpriteState GetCurrentState() const { return m_stCurrent; }
	// ���� ������� �̹��� ��ȣ�� ��ȯ
	LONG GetCurrentAnimationCount() const { return m_ptCurrentAnimationState.x; }
	// ���� ���°� � ��������(���� - ���� - ����) ��ȯ
	StateState GetCurrentStateState() const;

	// ����
	virtual void OnUpdate(bool reset = false);

	// �׸���
	virtual void Draw(HDC hDC, int x, int y);
};