/*
��� �־�� �ϴ°�
1. Framework
2. ������ �ڵ�
3. Tag
*/

#pragma once
#include <atlimage.h>

class CFrameWork;
typedef enum {
	Title=0,Lobby,Game, 
	Count // �迭�� ����� ���� �ִ� ��
}Scene_State;

class CScene
{
protected:
	CFrameWork* m_pframework;
	HWND m_hwnd;
	int m_tag;
public:

	CScene();
	virtual ~CScene();

	virtual void Update(float fTimeElapsed) = 0; // "=0" -> ���� �����Լ�
	virtual void Draw(HDC hdc) = 0;

	virtual bool InputMouse(UINT iMsg, WPARAM wParam, LPARAM lParam); //�޼���,w�Ķ�,l�Ķ�
	virtual bool InputKeyBoard(UINT iMsg, WPARAM wParam, LPARAM lParam);

	virtual void BuildObjects(CFrameWork* F,HWND hwnd,int tag) = 0;
	virtual void ReleaseObjects();

	bool IsMyTag(int tag) const { return tag == m_tag; }
	int GetMyTag() const { return m_tag; };
	CFrameWork* GetMyFramework() { return m_pframework; }
};

class CTitleScene:public CScene
{
protected:
	CImage img;
public:
	CTitleScene();
	~CTitleScene();

	virtual void Update(float fTimeElapsed); // "=0" -> ���� �����Լ�
	virtual void Draw(HDC hdc);

	virtual bool InputMouse(UINT iMsg, WPARAM wParam, LPARAM lParam); //�޼���,w�Ķ�,l�Ķ�
	virtual bool InputKeyBoard(UINT iMsg, WPARAM wParam, LPARAM lParam);

	virtual void BuildObjects(CFrameWork* F, HWND hwnd, int tag);
	virtual void ReleaseObjects();
};

class CLobbyScene :public CScene
{
protected:
	CImage img;
public:

	CLobbyScene();
	~CLobbyScene();

	virtual void Update(float fTimeElapsed); // "=0" -> ���� �����Լ�
	virtual void Draw(HDC hdc);

	virtual bool InputMouse(UINT iMsg, WPARAM wParam, LPARAM lParam); //�޼���,w�Ķ�,l�Ķ�
	virtual bool InputKeyBoard(UINT iMsg, WPARAM wParam, LPARAM lParam);

	virtual void BuildObjects(CFrameWork* F, HWND hwnd, int tag);
	virtual void ReleaseObjects();
};
