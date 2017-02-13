#pragma once
class CFrameWork
{
private:

	typedef struct Object{
		RECT rect; // 오브젝트 위치
		
		int hp; // 오브젝트 체력

		bool exist; // 오브젝트는 존재하는가

		int item_id; // 오브젝트 아이디 / 블럭,+아이템,방향전환아이템,디버프아이템
		Object* next;
	}Object;

	typedef struct Ball{
		double pos_x; // 공의 x위치
		double pos_y; // 공의 y위치

		double x_vec; // 공의 좌우 이동방향
		double y_vec; // 공의 상하 이동방향
		double distance; // 한프레임당 공의 이동 거리
		double angle; // 공의 각도
		bool shooted; // 움직이고 있는지
		bool movtofirst; // 시작지점으로 모여
		Ball* next;
	}Ball;

	typedef struct Get_Ball {
		double pos_x; // 공의 x위치
		double pos_y; // 공의 y위치
		double distance; // 한프레임당 공의 이동 거리
		bool shooted; // 움직이고 있는지
		bool movtofirst; // 시작지점으로 모여
		Get_Ball* next;
	}Get_Ball; // 먹은 공



	//////////////////////////<그래픽 도구들>////////////////////
	PAINTSTRUCT ps;
	HDC hdc,MemDC; // 항상 첫번째 인자는 hDC 다! , 두번째껀 비트맵용
	
	
	HBRUSH brush_old;
	HPEN pen_old;
	HBITMAP bitmap_old;

	HPEN pen_int_bar; // 상하단막대
	HPEN pen_sight; // 조준선

	HBITMAP bitmap_subtitle; // 제목
	HBITMAP bitmap_title; // 타이틀 화면
	HBITMAP bitmap_background; //배경화면
	HBITMAP bitmap_item_plus; // 플러스아이템 비트맵
	HBITMAP bitmap_item_change_dir; //방향전환 아이템 비트맵
	HBITMAP bitmap_item_debuff; // 조준에 하자가 생기는 아이템
	HBITMAP bitmap_ball; // 공 비트맵
	HBITMAP bitmap_gball; // 얻은공 비트맵
	wchar_t temp[50]; // 문자열 출력 임시 배열

	unsigned int mainframe; // 메인프레임
	unsigned int title_frame; // 타이틀화면 프레임
	unsigned int item_frame; // 아이템 애니메이션용
	unsigned int ball_frame; // 공 프레임
	//////////////////////////////////////////////////


	///////////////////////////////////////////////////

	HWND m_hwnd; // 윈도우 핸들
	RECT m_rect; // rect 구조체
	HINSTANCE m_hinst;
	HBRUSH hbrBackground = NULL; // 배경브러쉬핸들

	POINT ptmouse; // 마우스 위치 좌표
	POINT ptstart; //조준선의 시작지점

	double ptend_x; // 조준선 끝 지점
	double ptend_y;


	RECT for_col_check; // 충돌검사용 
	
//////<인터페이스>///////////////////////////
	RECT top_bar; // 상단 바
	RECT bottom_bar; // 하단 바

	RECT start_button; // 시작버튼
	RECT exit_button; // 나가는 버튼
///////////////////////////////////////

	bool drag; // 마우스 왼쪽키 누르고 있는지
	bool is_shooting; // 공을 쏘고 있는 중인지?
	bool is_collision; // 공이 충돌 했었는지?
	bool is_dir_changed; // 아이템먹어서 방향이 바뀌었는지?
	bool win_or_lose; // 승리냐 패배냐?
	// 400점을 채우면 승리 , 바닥에 블럭이 내려오면 패배
	bool is_brick_moving; // 블럭 움직이는지?
	double mx_down_dist; //오브젝트 내려올 거리 
	double down_dist; // 오브젝트가 내려온 거리

	bool is_ball_collecting; // 공을 회수완료했는지?
	bool is_first_drop; //첫번째 떨어진 공인지?

	int game_phase; // 게임 상태
	bool isdebuffed_lowaim; // 조준점 흔들리는 디버프에 걸렸는지
	int score;

	int coll_check; // 충돌체크용
							  //유니코드를 사용할 떄는 char 대신 wchar_t 를 쓰고 문자열 앞에 L를 붙인다
	int next_hp; // 다음 단의 블럭 HP
	int next_num_brick;
	int next_num_plus_item;
	Object set_brick[BRICK_DEVIDE];

	int get_ball; // 이번턴에 먹은 공의 수
	int num_ball; //현재 보유한 공
	int shooted_ball; // 지금까지 몇개 쐈는지?

	double startX; // 발사지점X
	double startY; // 발사지점Y


	////////////////////////////<포인터>///////
	Ball* ballhead; // 공포인터의 머리
	Get_Ball* getballhead; // 먹은공포인터의 머리
	Object* objecthead; //오브젝트포인터의 머리
	/////////////////////<공의 최종 초기값>/////////
	double x_vk; // 방향
	double angle; // 각도
	////////////////////////////////////////////
	
public:

	//////////////충돌계산하기/////////////////////////
	float LengthPts(double x1, double y1, double x2, double y2);
	// 두 점간 길이 계산
	BOOL InCircle(double x, double y, double rad, double px, double py);
	// 원과 원 계산
	int Collision_Rec_Ell(double c_x, double c_y, double c_rad, RECT rec_check);
	//원과 사각형 충돌계산 (원중점 , 반지름 , 충돌할 오브젝트 크기 계산)
	int Collision_point_check(double c_x, double c_y, double b_x, double b_y);
	//모서리 충돌시 충돌계산 (원중점, 충돌 오브젝트 점)



	///////////////////////////////////////////////////
	bool Initial(HWND, RECT, HINSTANCE);
	void Destroy(); // posquit,destroywindow(hWnd)넣으면 안돼
	void OnCreate();
	void OnDraw(HDC);
	void OnTimer(UINT); // 업데이트
	void Resize();
	void InputMouse(UINT, WPARAM, LPARAM); //메세지,w파람,l파람
	void InputKeyBoard(UINT, WPARAM, LPARAM); //메세지,w파람,l파람
	/////////<연산 함수>//////////////////////
	void CreateObject(int); // 오브젝트를 생성한다 , 인자는 생성위치
	void CreateGball(Object* );
	/////////<그래픽 함수>/////////////////
	void CreateBkBrush(COLORREF);
	void ClearScreen(HDC);
	void DrawSight(HDC); // 조준선을 그린다
	///////////////////////////////////
	LRESULT WindowMessage(HWND, UINT, WPARAM, LPARAM);//메세지,w파람,l파람
	CFrameWork();
	~CFrameWork();
};
