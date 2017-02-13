#pragma once

#include <Windows.h>
#include <iostream>

#include "Player.h"
#include "Scene.h"
#include "SoundManager.h"

class CPlayer;

template<typename Enum>				// Enum class�� �������� �˷��־� ���ڿ� �����ϴ� ���� ��ȯ�ϴ� �Լ��Դϴ�.
inline constexpr auto GetEnumValueByType(Enum enumerator) noexcept	// enum class E : int { a,b,c }; �� ��,
{																	// auto data = GetEnumValueByType(E::a);
	return static_cast<std::underlying_type_t<Enum>>(enumerator);	// data�� ������ int �̰�, ���� 0 �Դϴ�.
}

#define GetSceneEnumInt(Enum) GetEnumValueByType(CScene::CurrentScene::Enum)

class CFramework
{
private:
	HWND			m_hWnd{ NULL };
	RECT			m_rcClient{ 0,0,0,0 };

	HBITMAP			m_hBitmapBackBuffer = NULL;
	HDC				m_hDC = NULL;

	COLORREF		m_clrBackBuffer = 0x000000;
	HBRUSH			m_hbrBackground = NULL;

	CScene			*m_pCurrentScene;
	CScene			*m_arrScene[GetEnumValueByType(CScene::CurrentScene::Count)];

	CSoundManager	m_Sound;

	CPlayer			*m_Player;

	std::chrono::system_clock::time_point m_current_time;
	std::chrono::duration<double> m_timeElapsed; // �ð��� �󸶳� ������
	double m_fps;

	TCHAR m_CaptionTitle[TITLE_MX_LENGTH];
	int m_TitleLength;
	std::chrono::system_clock::time_point m_LastUpdate_time;
	std::chrono::duration<double> m_UpdateElapsed; // �ð��� �󸶳� ������

public:
	CFramework();
	~CFramework();

	bool OnCreate(HWND hWnd, const RECT& rc);
	void CreatebackBuffer();
	void BuildScene();
	void BuildPlayer();
	void ReleaseScene();

	bool OnDestroy();
	
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	HRESULT OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	void Update(float fTimeElapsed);
	
	void SetBKColor(COLORREF color);
	void ClearBackgroundColor();
	void PreproccessingForDraw();
	void OnDraw(HDC hDC);

	void ChangeScene(CScene::CurrentScene tag, bool bDestroy = false);

	void FrameAdvance();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

