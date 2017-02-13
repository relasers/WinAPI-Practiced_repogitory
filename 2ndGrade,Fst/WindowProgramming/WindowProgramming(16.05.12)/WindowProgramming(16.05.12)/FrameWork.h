#pragma once
class CFrameWork
{
private:

	HWND m_hwnd; // ������ �ڵ�
	RECT m_rect; // rect ����ü
	HINSTANCE m_hInst;
	////////////////////////////////////////////////////////
	PAINTSTRUCT ps;
	HDC hdc, MemDC; // �׻� ù��° ���ڴ� hDC ��! , �ι�°�� ��Ʈ�ʿ�

	HBRUSH hbrBackground = NULL; // ���귯���ڵ�
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
	wchar_t temp[40]; // �޼��� ��¿�
	RECT rect_temp = { 0,0,70,50 };
	RECT for_col_check; // �浹�˻�� 

	Brick brick[N_BRICK_Y][N_BRICK_X]; // ����
	RECT bar; // �����
	Ball ball; // ��

	int x, mx; // ���� x ��ǥ�� ���콺 x �Bǥ ����
	
	bool game_end = false; // ������ ����Ǵ���
	bool game_moving = true;
	bool drag; // ���콺 ����Ű ������ �ִ���
	bool grid = false;

	int coll_check = 0; // �浹üũ��
	int damaged = 0; // ���� �ջ� �� ����
	int destroyed = 0; // ���� �ı� �� ����
	int colortype = Color::red;




public:
	bool Initial(HWND, RECT,HINSTANCE);
	void Destroy(); // posquit,destroywindow(hWnd)������ �ȵ�
	void OnCreate();
	void OnDraw(HDC);
	void OnTimer(UINT); // ������Ʈ
	void InputMouse(UINT, WPARAM, LPARAM); //�޼���,w�Ķ�,l�Ķ�
	void InputKeyBoard(UINT, WPARAM, LPARAM); //�޼���,w�Ķ�,l�Ķ�

	void CreateBkBrush(COLORREF);
	void ClearScreen(HDC);

	float LengthPts(int x1, int y1, int x2, int y2);
	BOOL InCircle(int x, int y, int rad, int px, int py);
	int Collision_Rec_Ell(int, int, int, RECT);

	LRESULT WindowMessage(HWND, UINT, WPARAM, LPARAM );//�޼���,w�Ķ�,l�Ķ�
	INT_PTR WindowMenu(HWND, UINT, WPARAM, LPARAM);
	CFrameWork();
	~CFrameWork();
};
