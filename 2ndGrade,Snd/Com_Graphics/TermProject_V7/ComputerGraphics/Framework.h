#pragma once

#include "Scene.h"

template<typename Enum>				// Enum class의 선언형을 알려주어 인자와 대응하는 값을 반환하는 함수입니다.
inline constexpr auto GetEnumValueByType(Enum enumerator) noexcept	// enum class E : int { a,b,c }; 일 때,
{																	// auto data = GetEnumValueByType(E::a);
	return static_cast<std::underlying_type_t<Enum>>(enumerator);	// data의 형식은 int 이고, 값은 0 입니다.
}

#define GetSceneEnumInt(Enum) GetEnumValueByType(CScene::CurrentScene::Enum)

class CFramework
{
private:
	HWND			m_hWnd{ NULL };
	HGLRC			m_hglRC{ NULL };
	RECTf			m_rcClient{ 0,0,0,0 };

	HDC				m_hDC = NULL;

	myCOLORREFf		m_clrBackBuffer{ 0.5f, 0.5f, 0.9f, 0.1f };

	CSoundManager	*m_SoundManager;

	CScene			*m_pCurrentScene;
	CScene			*m_arrScene[GetEnumValueByType(CScene::CurrentScene::count)];

	CCamera_OpenGL	*m_Camera;
	CCamera_OpenGL	*m_MiniMapCamera;
	CLight			*m_Light;
	CTextureLibraray*m_TextureLib;

	std::chrono::system_clock::time_point m_current_time;
	std::chrono::duration<double> m_timeElapsed; // 시간이 얼마나 지났나
	double m_fps;

	TCHAR m_CaptionTitle[TITLE_MX_LENGTH];
	int m_TitleLength;
	std::chrono::system_clock::time_point m_LastUpdate_time;
	std::chrono::duration<double> m_UpdateElapsed; // 시간이 얼마나 지났나

public:
	CFramework();
	~CFramework();

	bool OnCreate(HWND hWnd, const RECT& rc);
	bool OpenGLInit();
	void TextureLoad();
	void BuildScene();

	bool OnDestroy();
	
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	HRESULT OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	void Update(float fTimeElapsed);
	
	void ClearBackgroundColor();
	void PreproccessingForRendering();
	void Rendering();
	void ReShape(int width, int height);

	void ChangeScene(CScene::CurrentScene tag, bool bDestroy = false);

	CSoundManager*		GetSoundManager() { return m_SoundManager; }
	CCamera_OpenGL*		GetMiniMapCamera() { return m_MiniMapCamera; }
	CCamera_OpenGL*		GetCamera() { return m_Camera; }
	CLight*				GetLight() { return m_Light; }
	CTextureLibraray*	GetTextureLib() { return m_TextureLib; }

	void FrameAdvance();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

