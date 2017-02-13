/*
들고 있어야 하는거
1. Framework
2. 윈도우 핸들
3. Tag
*/

#pragma once
#include <atlimage.h>

class CFrameWork;
typedef enum {
	Title=0,Lobby,Game, 
	Count // 배열을 만들기 위해 넣는 값
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

	virtual void Update(float fTimeElapsed) = 0; // "=0" -> 순수 가상함수
	virtual void Draw(HDC hdc) = 0;

	virtual bool InputMouse(UINT iMsg, WPARAM wParam, LPARAM lParam); //메세지,w파람,l파람
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

	virtual void Update(float fTimeElapsed); // "=0" -> 순수 가상함수
	virtual void Draw(HDC hdc);

	virtual bool InputMouse(UINT iMsg, WPARAM wParam, LPARAM lParam); //메세지,w파람,l파람
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

	virtual void Update(float fTimeElapsed); // "=0" -> 순수 가상함수
	virtual void Draw(HDC hdc);

	virtual bool InputMouse(UINT iMsg, WPARAM wParam, LPARAM lParam); //메세지,w파람,l파람
	virtual bool InputKeyBoard(UINT iMsg, WPARAM wParam, LPARAM lParam);

	virtual void BuildObjects(CFrameWork* F, HWND hwnd, int tag);
	virtual void ReleaseObjects();
};
