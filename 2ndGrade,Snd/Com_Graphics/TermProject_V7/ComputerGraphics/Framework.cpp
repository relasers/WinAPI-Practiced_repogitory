#include "stdafx.h"

#include "Framework.h"
#include "LogoScene.h"
#include "TitleScene.h"
#include "MainScene.h"
#include "GameOverScene.h"
#include "GameClearScene.h"

using namespace std;

template <typename T>
constexpr T GetUserDataPtr(HWND hWnd) noexcept
{
	return reinterpret_cast<T>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
}

void SetUserDataPtr(HWND hWnd, LPVOID ptr) 
{
	LONG_PTR result = ::SetWindowLongPtr(
		hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(ptr));
}

CFramework::CFramework()
{
}

CFramework::~CFramework()
{
	OnDestroy();
}

bool CFramework::OnCreate(HWND hWnd, const RECT & rc)
{
	// Set Console
	system("mode con:cols=50 lines=30");
	system("title Debug Console");

	srand((unsigned int)time(NULL));

	m_hWnd = hWnd;

	// 클라이언트 좌표 초기화
	m_rcClient.x1 = -rc.right / 2;
	m_rcClient.y1 = -rc.bottom / 2;
	m_rcClient.x2 = rc.right / 2;
	m_rcClient.y2 = rc.bottom / 2;

	// OpenGL 초기화
	if (!OpenGLInit())
	{
		MessageBox(NULL, L"Failed to Initialize OpenGL", L"Initialize Error", MB_OK);
		return false;
	}

	// 카메라 생성
	m_Camera = new CCamera_OpenGL(m_hWnd, CLIENT_WIDTH, CLIENT_HEIGHT);
	m_MiniMapCamera = new CCamera_OpenGL(m_hWnd, CLIENT_WIDTH, CLIENT_HEIGHT);
	m_MiniMapCamera->SetProjection(CCamera_OpenGL::ProjectionType::Ortho);
	
	// 조명 생성
	m_Light = new CLight();

	// 텍스처 생성
	m_TextureLib = new CTextureLibraray();
	TextureLoad();

	// 사운드 생성
	m_SoundManager = new CSoundManager();
	m_SoundManager->Initialize();

	// 백그라운드 색상 초기화
	ClearBackgroundColor();

	// 클래스와 윈도우 프로시저 연결
	::SetUserDataPtr(m_hWnd, this);

	// 현재 Scene은 없는걸로
	m_pCurrentScene = nullptr;
	// Scene 배열 초기화
	for (auto& p : m_arrScene)
		p = nullptr;

	// Scene 생성
	BuildScene();

	// 캡션 변경
	lstrcpy(m_CaptionTitle, TITLESTRING);

#if defined(SHOW_CAPTIONFPS)
	lstrcat(m_CaptionTitle, TEXT(" ("));
#endif
	m_TitleLength = lstrlen(m_CaptionTitle);
	SetWindowText(m_hWnd, m_CaptionTitle);
	
	// 타이머 초기화
	m_LastUpdate_time = chrono::system_clock::now();
	m_current_time = chrono::system_clock::now();
	m_fps = 0.0f;

	return (m_hWnd != NULL);
}

bool CFramework::OpenGLInit()
{
	// OpenGL
	PIXELFORMATDESCRIPTOR	pfd;
	int						pf;

	if ((m_hDC = GetDC(m_hWnd)) == NULL)	// get device context
	{
		MessageBox(NULL, L"Failed to Get the Window Device Context",
			L"Device Context Error", MB_OK);
		return false;
	}

	memset(&pfd, 0, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 0b00100000; //0x20

	if ((pf = ChoosePixelFormat(m_hDC, &pfd)) == NULL) {
		MessageBox(NULL, L"ChoosePixelFormat() failed:  "
			L"Cannot find a suitable pixel format.", L"Error", MB_OK);
		return false;
	}
	if (SetPixelFormat(m_hDC, pf, &pfd) == FALSE) {
		MessageBox(NULL, L"SetPixelFormat() failed:  "
			L"Cannot set format specified.", L"Error", MB_OK);
		return false;
	}
	if (DescribePixelFormat(m_hDC, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd) == FALSE) {
		MessageBox(NULL, L"DescribePixelFormat() failed:  "
			L"Cannot describe format specified.", L"Error", MB_OK);
		return false;
	}
	if ((m_hglRC = wglCreateContext(m_hDC)) == NULL)	// create the rendering context
	{
		MessageBox(NULL, L"Failed to Create the OpenGL Rendering Context",
			L"OpenGL Rendering Context Error", MB_OK);
		return false;
	}
	if ((wglMakeCurrent(m_hDC, m_hglRC)) == false)		// make hglrc current rc
	{
		MessageBox(NULL, L"Failed to make OpenGL Rendering Context current",
			L"OpenGL Rendering Context Error", MB_OK);
		return false;
	}
	return true;
}

void CFramework::TextureLoad()
{
	m_TextureLib->SetTexture(L"Texture/TILE_1.png");
	m_TextureLib->SetTexture(L"Texture/TILE_2.png");
	m_TextureLib->SetTexture(L"Texture/TILE_3.png");
	m_TextureLib->SetTexture(L"Texture/TILE_4.png");
	m_TextureLib->SetTexture(L"Texture/TILE_5.png");
	m_TextureLib->SetTexture(L"Texture/TILE_6.png");
	m_TextureLib->SetTexture(L"Texture/Bottom.jpg");
	m_TextureLib->SetTexture(L"Texture/Storm.jpg");
	m_TextureLib->SetTexture(L"Texture/Radar.png");
	m_TextureLib->SetTexture(L"Texture/Heroes.png");
	m_TextureLib->SetTexture(L"Texture/Gear.png");
	m_TextureLib->SetTexture(L"Texture/UI_Back.png");
	m_TextureLib->SetTexture(L"Texture/Logo.png");
	m_TextureLib->SetTexture(L"Texture/Title.png");
	m_TextureLib->SetTexture(L"Texture/GameOver.png");
	m_TextureLib->SetTexture(L"Texture/GameClear.png");
}

void CFramework::BuildScene()
{
	m_arrScene[GetSceneEnumInt(Logo)] = new CLogoScene();
	m_arrScene[GetSceneEnumInt(Logo)]->BuildObjects(this, m_hWnd, CScene::CurrentScene::Logo);

	m_arrScene[GetSceneEnumInt(Title)] = new CTitleScene();
	m_arrScene[GetSceneEnumInt(Title)]->BuildObjects(this, m_hWnd, CScene::CurrentScene::Title);
	
	m_arrScene[GetSceneEnumInt(Main)] = new CMainScene();
	m_arrScene[GetSceneEnumInt(Main)]->BuildObjects(this, m_hWnd, CScene::CurrentScene::Main);
	
	m_arrScene[GetSceneEnumInt(GameOver)] = new CGameOverScene();
	m_arrScene[GetSceneEnumInt(GameOver)]->BuildObjects(this, m_hWnd, CScene::CurrentScene::GameOver);
	
	m_arrScene[GetSceneEnumInt(GameClear)] = new CGameClearScene();
	m_arrScene[GetSceneEnumInt(GameClear)]->BuildObjects(this, m_hWnd, CScene::CurrentScene::GameClear);

	m_pCurrentScene = m_arrScene[GetSceneEnumInt(Logo)]; // 현재신은 타이틀로 초기화

}

bool CFramework::OnDestroy()
{
	wglMakeCurrent(m_hDC, NULL);

	if (m_hDC) ::DeleteDC(m_hDC);

	wglDeleteContext(m_hglRC);
	DestroyWindow(m_hWnd);
	return false;
}

bool CFramework::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	if (m_pCurrentScene->OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam)) return false;
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		return true;
	case WM_KEYUP:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		return true;
	}
	return false;
}

bool CFramework::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	if (m_pCurrentScene->OnProcessingMouseMessage(hWnd, nMessageID, wParam, lParam)) return false;
	switch (nMessageID)
	{
	case WM_LBUTTONUP:
		break;

	case WM_LBUTTONDOWN:
		break;

	case WM_MOUSEMOVE:
		break;
	}
	return false;
}

HRESULT CFramework::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	default:
		return ::DefWindowProc(hWnd, nMessageID, wParam, lParam);

	}
	return 0;
}

void CFramework::Update(float fTimeElapsed)
{
	m_pCurrentScene->Update(fTimeElapsed);
}

void CFramework::ClearBackgroundColor()
{
	glClearColor(m_clrBackBuffer.red, m_clrBackBuffer.green, m_clrBackBuffer.blue, m_clrBackBuffer.alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);

	m_Light->SettingLight();

	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
}

void CFramework::PreproccessingForRendering()
{
	ClearBackgroundColor();

	m_pCurrentScene->Rendering();


	m_pCurrentScene->RendMiniMap();
}

void CFramework::Rendering()
{
	//glFlush();
	SwapBuffers(m_hDC);
}

void CFramework::ReShape(int width, int height)
{
	glViewport(0, 0, width, height);
	m_Camera->LookAt();
}

void CFramework::ChangeScene(CScene::CurrentScene Tag, bool bDestroy)
{
	const int tag = GetEnumValueByType(Tag);
	if (bDestroy)
	{
		int d_tag = GetEnumValueByType(m_pCurrentScene->GetMyTag());
		delete m_pCurrentScene;
		m_pCurrentScene = nullptr;
		m_arrScene[d_tag] = nullptr;
	}
	// 만약 nullptr가 아닐 경우
	if (m_arrScene[tag])
	{ 
		m_pCurrentScene = m_arrScene[tag];
	}
	else
	{
		switch (Tag) 
		{
		case CScene::CurrentScene::Logo:
			m_arrScene[GetSceneEnumInt(Logo)] = new CLogoScene();
			m_arrScene[GetSceneEnumInt(Logo)]->BuildObjects(this, m_hWnd, CScene::CurrentScene::Logo);
			break;
		case CScene::CurrentScene::Title:
			m_arrScene[GetSceneEnumInt(Title)] = new CTitleScene();
			m_arrScene[GetSceneEnumInt(Title)]->BuildObjects(this, m_hWnd, CScene::CurrentScene::Title);
			break;
		case CScene::CurrentScene::Main:
			m_arrScene[GetSceneEnumInt(Main)] = new CMainScene();
			m_arrScene[GetSceneEnumInt(Main)]->BuildObjects(this, m_hWnd, CScene::CurrentScene::Main);
			break;
		case CScene::CurrentScene::GameOver:
			m_arrScene[GetSceneEnumInt(GameOver)] = new CGameOverScene();
			m_arrScene[GetSceneEnumInt(GameOver)]->BuildObjects(this, m_hWnd, CScene::CurrentScene::GameOver);
			break;
		case CScene::CurrentScene::GameClear:
			m_arrScene[GetSceneEnumInt(GameClear)] = new CGameClearScene();
			m_arrScene[GetSceneEnumInt(GameClear)]->BuildObjects(this, m_hWnd, CScene::CurrentScene::GameClear);
			break;
		}

		m_pCurrentScene = m_arrScene[tag];

	}
}

void CFramework::FrameAdvance()
{
	// Get tick
	m_timeElapsed = chrono::system_clock::now() - m_current_time;
	if (m_timeElapsed.count() > MAX_FPS)
	{
		m_current_time = chrono::system_clock::now();
	
		if (m_timeElapsed.count() > 0.0f)
			m_fps = 1.0f / m_timeElapsed.count();
	}
	// 최대 FPS 미만의 시간이 경과하면 진행 생략
	else return;

	Update(m_timeElapsed.count());
	PreproccessingForRendering();

	RECT temp{ m_rcClient.x1, m_rcClient.y2, m_rcClient.x2, m_rcClient.y1 };
	InvalidateRect(m_hWnd, &temp, FALSE);

#if defined(SHOW_CAPTIONFPS)

	m_UpdateElapsed = chrono::system_clock::now() - m_LastUpdate_time;
	if (m_UpdateElapsed.count() > MAX_UPDATE_FPS)
		m_LastUpdate_time = chrono::system_clock::now();
	else return;

	_itow_s(m_fps + 0.1f, m_CaptionTitle + m_TitleLength, TITLE_MX_LENGTH - m_TitleLength, 10);
	wcscat_s(m_CaptionTitle + m_TitleLength, TITLE_MX_LENGTH - m_TitleLength, TEXT(" FPS)"));
	SetWindowText(m_hWnd, m_CaptionTitle);
#endif

}

LRESULT CFramework::WndProc(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	CFramework* self = ::GetUserDataPtr<CFramework*>(hWnd);
	if (!self)
		return ::DefWindowProc(hWnd, nMessageID, wParam, lParam);

	switch (nMessageID)
	{

	case WM_LBUTTONDOWN: case WM_LBUTTONUP:
	case WM_RBUTTONDOWN: case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
		self->OnProcessingMouseMessage(hWnd, nMessageID, wParam, lParam);
		break;

	case WM_KEYDOWN:
	case WM_KEYUP:
		self->OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam);
		break;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			self->Rendering();
			::BeginPaint(hWnd, &ps);
			::EndPaint(hWnd, &ps);
		}
		break;

	case WM_SIZE:
		
		self->ReShape(static_cast<int>(LOWORD(lParam)), static_cast<int>(HIWORD(lParam)));
		PostMessage(hWnd, WM_PAINT, 0, 0);
		break;

	case WM_DESTROY:
		::SetUserDataPtr(hWnd, NULL);
		::PostQuitMessage(0);
		break;

	default:
		return self->OnProcessingWindowMessage(hWnd, nMessageID, wParam, lParam);

	}
	return 0;
}
