#pragma once
class CFrameWork
{
private:

	HWND m_hwnd; // 윈도우 핸들
	RECT m_rect; // rect 구조체
	HINSTANCE m_hInst;
	////////////////////////////////////////////////////////
	PAINTSTRUCT ps;
	HDC hdc, MemDC; // 항상 첫번째 인자는 hDC 다! , 두번째껀 비트맵용

	HBRUSH hbrBackground = NULL; // 배경브러쉬핸들
	/////////////////////////////////////////////////////////////////////
	typedef struct {
		RECT brick;
		bool exist;
		int hp;
	}Brick;

	typedef struct {
		RECT circle;
		bool exist;
		int x_vec;
		int y_vec;
		int speed;
	}Ball;


	HBRUSH hBar_Brush, hBall_Brush, hBrick_damaged_Brush, hBrick_normal_Brush, oldBrush;
	wchar_t temp[40]; // 메세지 출력용
	RECT rect_temp = { 0,0,70,50 };
	RECT for_col_check; // 충돌검사용 

	Brick brick[N_BRICK_Y][N_BRICK_X]; // 벽돌
	RECT bar; // 막대기
	Ball ball; // 공

	int x, mx; // 막대 x 좌표와 마우스 x 좦표 저장
	
	bool game_end = false; // 게임이 진행되는지
	bool game_moving = true;
	bool drag; // 마우스 왼쪽키 누르고 있는지
	bool grid = false;

	int coll_check = 0; // 충돌체크용
	int damaged = 0; // 벽돌 손상 수 저장
	int destroyed = 0; // 벽돌 파괴 수 저장
	int colortype = Color::red;




public:
	bool Initial(HWND, RECT,HINSTANCE);
	void Destroy(); // posquit,destroywindow(hWnd)넣으면 안돼
	void OnCreate();
	void OnDraw(HDC);
	void OnTimer(UINT); // 업데이트
	void InputMouse(UINT, WPARAM, LPARAM); //메세지,w파람,l파람
	void InputKeyBoard(UINT, WPARAM, LPARAM); //메세지,w파람,l파람

	void CreateBkBrush(COLORREF);
	void ClearScreen(HDC);

	float LengthPts(int x1, int y1, int x2, int y2);
	BOOL InCircle(int x, int y, int rad, int px, int py);
	int Collision_Rec_Ell(int, int, int, RECT);

	LRESULT WindowMessage(HWND, UINT, WPARAM, LPARAM );//메세지,w파람,l파람
	INT_PTR WindowMenu(HWND, UINT, WPARAM, LPARAM);
	CFrameWork();
	~CFrameWork();
};
