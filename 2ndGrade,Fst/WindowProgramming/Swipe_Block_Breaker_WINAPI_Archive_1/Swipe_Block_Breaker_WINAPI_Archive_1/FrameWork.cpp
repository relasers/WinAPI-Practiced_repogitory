#include "stdafx.h"
#include "FrameWork.h"

CFrameWork::CFrameWork()
{

}
CFrameWork::~CFrameWork()
{
	Destroy();
}
// 클래스 함수선언은 헤더에서 하는게 아니고 cpp 파일에 한다.
bool CFrameWork::Initial(HWND h, RECT r, HINSTANCE hInst) {
	// 변수명 앞에 자료형 쓰면 그건 지역변수가 되어버린다
	m_hwnd = h;
	m_rect = r;
	m_hinst = hInst;
	return m_hwnd != NULL; // 윈도우 생성 실패하면 윈도우 핸들이 NULL 값이 들어간다.
						   // 이값이 NULL값일 경우 윈도우가 제대로 만들어지지 않았다는것, 널값이면 윈도우를 죽여라!
}
void CFrameWork::Destroy() { // 반환값은 없어도 상관없다, 어쩌피 죽을테니까, 메모리 누수 방지
							 //소멸자로 소멸할때 Destroy 호출, 소멸자는 함수가 죽어야만 나온다 , 죽이고 다시 생성하고 싶을때 쓰자
							 // 대를 잇게 할때 -> 그떄를 위해 함수를 미리 빼 놓는다
	DeleteObject(bitmap_background);
	DeleteObject(bitmap_ball);
	DeleteObject(bitmap_gball);
	DeleteObject(bitmap_item_change_dir);
	DeleteObject(bitmap_item_debuff);
	DeleteObject(bitmap_item_plus);

	KillTimer(m_hwnd, TIMER_MENU::UPDATER); // 게임상태를 업데이트 한다
	KillTimer(m_hwnd, TIMER_MENU::MOV_BALL); // 공이 움직이는 타이머
	KillTimer(m_hwnd, TIMER_MENU::ANIMATION); // 애니메이션 타이머
	
	PostQuitMessage(0);
};

LRESULT CFrameWork::WindowMessage(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {

	PAINTSTRUCT ps;
	HDC hdc; // 항상 첫번째 인자는 hDC 다! 

	switch (iMessage) {// 메시지 번호// case: 메시지에 따라 처리
	case WM_TIMER:
		OnTimer(wParam);
		break;
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_MOUSEMOVE:
		InputMouse(iMessage, wParam, lParam);
		break;
		/////////////////////////////////////////
	case WM_CHAR:
	case WM_KEYDOWN:
	case WM_KEYUP:
		InputKeyBoard(iMessage, wParam, lParam);
		break;
		///////////////////////////////////////////
	case WM_PAINT: //윈도우 다시 그려줘야 할 때
		hdc = BeginPaint(hwnd, &ps); // WM_PAINT 메세지에서 사용 , 이 외에서 쓸떄는 GetDC(),ReleaseDC() 를 쓴다(잠시 출력할때)

		OnDraw(hdc); // hdc 를 OnDraw 로 넘긴다.

		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		Destroy();
		return 0;
	} //처리할 메시지만 case문에 나열
	return(DefWindowProc(hwnd, iMessage, wParam, lParam));// CASE에서 정의되지 않은 메시지는 커널이 처리하도록 메시지 전달 
}
void CFrameWork::OnCreate() { // 나중에 3-1학기떄 BuildObject 로 쓴다 , 동적메모리 릴리즈 용
	GetClientRect(m_hwnd, &m_rect);
	CreateBkBrush(RGB(255, 255, 255));
	PlaySound(L"BackGroundSound.wav",NULL,SND_ASYNC|SND_LOOP); // 배경음악을 재생한다, ASYNC -> 비동기화, 루프를 돌린다
	srand((unsigned)time(NULL)); // 랜덤ㄴ 시드생성
	/////////////////////////<그래픽 도구들>///////////////////////////////
	pen_sight = (HPEN)CreatePen(PS_DASH,3,RGB(0,150,255));
	bitmap_background = (HBITMAP)LoadBitmap(m_hinst, // m_hinstance 인수는 맨위에 선언한 m_hinstANCE 값으로..
	MAKEINTRESOURCE(IDB_BACKGROUND)); // 배경화면을 불러온다
	bitmap_item_plus = (HBITMAP)LoadBitmap(m_hinst, // 공 추가 아이템 스프라이트를 불러온다
		MAKEINTRESOURCE(IDB_ITEM_PLUS));
	bitmap_item_change_dir = (HBITMAP)LoadBitmap(m_hinst, // 공 방향전환 아이템 스프라이트를 불러온다
		MAKEINTRESOURCE(IDB_ITEM_CHANGE_DIR));
	bitmap_item_debuff = (HBITMAP)LoadBitmap(m_hinst, // 공 발사 디버프 아이템 스프라이트를 불러온다
		MAKEINTRESOURCE(IDB_ITEM_DEBUFF));
	bitmap_ball = (HBITMAP)LoadBitmap(m_hinst, //공 스프라이트를 불러온다
		MAKEINTRESOURCE(IDB_BALL));
	bitmap_gball = (HBITMAP)LoadBitmap(m_hinst, // 녹색공 스프라이트를 불러온다
		MAKEINTRESOURCE(IDB_G_BALL));
	bitmap_title = (HBITMAP)LoadBitmap(m_hinst, // 타이틀 화면 스프라이트를 불러온다
		MAKEINTRESOURCE(IDB_TITLEBG));
	bitmap_subtitle = (HBITMAP)LoadBitmap(m_hinst, // 제목 스프라이트를 불러온다
		MAKEINTRESOURCE(IDB_SUBTITLE));


	mainframe = 0;
	ball_frame = 0;
	item_frame = 0;
	title_frame = 0;
	/////////<게임 상태 변수들>//////////////////////////////////
	game_phase = Phase::GAME_MENU;

	is_collision = false; // 공이 블럭과 충돌한적 있는가?
	is_first_drop = true; // 공이 처음 떨어졌나?
	is_shooting = false; // 공 쏘고 있는가?
	is_dir_changed = false; // 공이 방향전환 아이템과 충돌한 적 있는가?
	is_ball_collecting = false; // 공이 회수되고 있는가?
	is_brick_moving = false; // 블럭이 움직이는중인가?

	isdebuffed_lowaim = false; //디버프가 걸렸는가?
	drag = false;
	coll_check = 0; // 충돌체크용

	next_hp = 1; // 다음 단의 블럭 HP
	next_num_brick = 4; //다음 단 블럭 수 최소 4개는 만들어야지
	next_num_plus_item = 1; // 공 추가하는 아이템 갯수는 언제나 1개씩 만들자
	score = 0; // 점수

	startX = CLIENT_WIDTH / 2; // 초기 공 위치
	startY = bottom_bar.top - BALL_SIZE; // 초기 공 위치

	mx_down_dist = m_rect.bottom / GAME_BOARD_DEVIDE; //오브젝트 내려오는 거리 
	down_dist = 0; // 오브젝트가 내려올 거리

	get_ball = 0; // 획득한 공의 수
	shooted_ball = 0; // 발사한 공의 수
	num_ball = 100; // 처음 공의 수

	x_vk = 1; // 초기 방향 값
	angle = 1; // 초기 각도 값

	///////////<게임 인터페이스>/////////////////////////////////////////
	top_bar = {-3,-3,m_rect.right + 3, m_rect.bottom/GAME_BOARD_DEVIDE}; // 상단 바
	bottom_bar = {-3,m_rect.bottom - 2*m_rect.bottom/GAME_BOARD_DEVIDE-12, 
	m_rect.right + 3,m_rect.bottom + 3}; // 하단 바

	start_button = { 300,350,500,400 }; // 시작버튼
	exit_button = { 300,450,500,500 }; // 나가는 버튼, 후에 타이틀 화면으로 돌아가는 버튼도 병행


	///////////////////////////////////////////////공 포인터 생성
	ballhead = (Ball*)malloc(sizeof(Ball));
	Ball* p = ballhead; // 공의 헤드포인터를 생성해보자
	for (int i = 0; i < num_ball; ++i) {
		Ball* ball = (Ball*)malloc(sizeof(Ball));
		ball->pos_x = CLIENT_WIDTH / 2; // 초기위치는 클라의 중앙
		ball->pos_y = bottom_bar.top - BALL_SIZE; // 하단 바의 상단에 위치하도록한다
		ball->x_vec = 1; // 1, -1, 로 방향조절한다
		ball->y_vec = 1; // 위와 동일
		ball->distance = BALL_SPEED; // 속도는 디폴트값으로 두자
		ball->angle = 45*3.14/180; // 각도는 45도 , 어쩌피 마우스로 각도설정 다시한다.
		ball->shooted = false; // 쐇는가?
		ball->movtofirst = false; // 공이 회수당하고 있는가?
		ball->next = NULL; 
		p->next = ball;
		p = p->next;
	} // 공을 num_ball 값만큼 생성한다.

	//////////////////<먹은공 포인터 생성>/////////////////////
	getballhead = (Get_Ball*)malloc(sizeof(Get_Ball));
	getballhead->next = NULL; // 먹은공의 헤드포인터를 만들어보자, 아이템 먹었을떄 나오는 초록색 공이다
	///////////////////////<블럭 생성>///////////////////////////////////
	objecthead = (Object*)malloc(sizeof(Object));
	objecthead->next = NULL; // 오브젝트의 헤드포인터를 만들어보자

	CreateObject(2); // 블럭을 만들어보자, 인자는 생성위치,, 처음이니까 두번째
	///////////////////////////////////////////////////////////////////// 

	SetTimer(m_hwnd, TIMER_MENU::UPDATER, 10, NULL); // 게임상태를 업데이트 한다
	SetTimer(m_hwnd, TIMER_MENU::MOV_BALL, 10, NULL); // 공이 움직이는 타이머
	SetTimer(m_hwnd, TIMER_MENU::ANIMATION, 60, NULL); //애니메이션  타이머
}
////////////////<그리는 곳>/////////////////////////////////////////////
void CFrameWork::OnDraw(HDC hdc) {
	
	HDC LayDC;
	LayDC = CreateCompatibleDC(hdc); // hdc와 호환시킨다.
	HBITMAP Lay; // 레이어 생성
	HBRUSH block_brush; // 블럭의 색깔 브러쉬를 만든다
	int block_color; // 블럭 색깔 바꾸기용 변수
	Lay = CreateCompatibleBitmap(hdc, m_rect.right, m_rect.bottom); // 다블 버퍼링 ,hdc와 호환시키자.
	SelectObject(LayDC, Lay);
	{
////////////////////////////////////////////////////////////////////////////
		SetBkMode(LayDC, TRANSPARENT);
		ClearScreen(LayDC); // 화면 클리어
		MemDC = CreateCompatibleDC(LayDC); // 이건 비트맵 뿌리기용
		
		switch (game_phase) {
		case Phase::GAME_MENU: // 게임메뉴
			bitmap_old = (HBITMAP)SelectObject(MemDC, bitmap_title);
			BitBlt(LayDC, 0, 0, 600, 660, MemDC, title_frame*600, 0, SRCCOPY); // 타이틀화면을 그린다
			SelectObject(MemDC, bitmap_old);

			bitmap_old = (HBITMAP)SelectObject(MemDC, bitmap_subtitle);
			TransparentBlt(LayDC, 50, 50 + title_frame,
				300, 200,
				MemDC, 0, 0, 300, 200,
				RGB(255, 255, 255)); // 타이틀 제목을 그린다
			// 흰색을 투명하게 설정핚다.
			SelectObject(MemDC, bitmap_old);

			block_brush = (HBRUSH)CreateSolidBrush(RGB(230,150,150)); // 버튼 브러쉬
			brush_old = (HBRUSH)SelectObject(LayDC,block_brush);
			Rectangle(LayDC, start_button.left, start_button.top
				, start_button.right, start_button.bottom); // 시작버튼
			Rectangle(LayDC, exit_button.left, exit_button.top
				, exit_button.right, exit_button.bottom); // 종료버튼
			wsprintf(temp, TEXT("START"));
			DrawText(LayDC, temp, -1, &start_button,
				DT_SINGLELINE | DT_NOCLIP | DT_CENTER | DT_VCENTER); // 시작문자열
			wsprintf(temp, TEXT("EXIT"));
			DrawText(LayDC, temp, -1, &exit_button,
				DT_SINGLELINE | DT_NOCLIP | DT_CENTER | DT_VCENTER); // 종료문자열
			SelectObject(LayDC, brush_old);
			break;
		case Phase::Aiming_Phase:
		case Phase::Shoot_Phase:
		case Phase::Calculating_Phase:
		case Phase::Create_Brick_Phase:
		case Phase::GAME_END:
			Ball* ball = ballhead->next;
			Get_Ball* gball = getballhead->next;
			bitmap_old = (HBITMAP)SelectObject(MemDC, bitmap_background);
			BitBlt(LayDC, 0, 0, 600, 660, MemDC, 0, 0, SRCCOPY); // 배경화면을 그린다
			// SRCCOPY : 바탕색을 무시하고 그려라
			SelectObject(MemDC, bitmap_old);

			while (ball != NULL) {
				bitmap_old = (HBITMAP)SelectObject(MemDC, bitmap_ball);
				TransparentBlt(LayDC, ball->pos_x, ball->pos_y,
					BALL_SIZE, BALL_SIZE,
					MemDC, ball_frame*BALL_SIZE, 0, BALL_SIZE, BALL_SIZE,
					RGB(255, 255, 255)); // 전체 공을 그린다
				// 흰색을 투명하게 설정핚다.
				SelectObject(MemDC, bitmap_old);
				ball = ball->next;
			}

			while (gball != NULL) {
				bitmap_old = (HBITMAP)SelectObject(MemDC, bitmap_gball);
				TransparentBlt(LayDC, gball->pos_x, gball->pos_y,
					BALL_SIZE, BALL_SIZE,
					MemDC, ball_frame*BALL_SIZE, 0, BALL_SIZE, BALL_SIZE,
					RGB(255, 255, 255)); // 전체 초록공을 그린다
				// 흰색을 투명하게 설정핚다.
				SelectObject(MemDC, bitmap_old);
				gball = gball->next;
			}

			Object* object = objecthead->next;
			while (object != NULL) { // 오브젝트들을 모조리 그리자
				switch (object->item_id) {
				case ITEM_NOTHING: // 블럭일때

					block_color = 255 - object->hp * 10; // 체력에 따라 블럭 색깔이 바뀐다
					if (block_color < 0) {
						block_color = 0; // 칼라값이 0보다 작아지면 0으로 고정
					}
					block_brush = (HBRUSH)CreateSolidBrush(RGB(255, block_color, block_color));
					brush_old = (HBRUSH)SelectObject(LayDC, block_brush);
					Rectangle(LayDC, object->rect.left, object->rect.top,
						object->rect.right, object->rect.bottom);
					if (object->item_id == ITEM_NOTHING) {
						wsprintf(temp, TEXT("%d"), object->hp);
						SetTextColor(LayDC, RGB(0, 255 - block_color, 255 - block_color));
						DrawText(LayDC, temp, -1, &object->rect,
							DT_SINGLELINE | DT_NOCLIP | DT_CENTER | DT_VCENTER); //체력을 블럭안에 표기
					}
					SelectObject(LayDC, brush_old);
					DeleteObject(block_brush);
					break;
				case ITEM_PLUS_BALL: // 공 추가 아이템일시
					bitmap_old = (HBITMAP)SelectObject(MemDC, bitmap_item_plus);
					TransparentBlt(LayDC, object->rect.left, object->rect.top,
						ITEM_SIZE, ITEM_SIZE,
						MemDC, item_frame*ITEM_SIZE, 0, ITEM_SIZE, ITEM_SIZE,
						RGB(255, 255, 255)); // 아이템 스프라이트를 뿌리자
					// 흰색을 투명하게 설정핚다.
					SelectObject(MemDC, bitmap_old);

					break;
				case ITEM_CHANGE_BALL_DIR:
					bitmap_old = (HBITMAP)SelectObject(MemDC, bitmap_item_change_dir);
					TransparentBlt(LayDC, object->rect.left, object->rect.top,
						ITEM_SIZE, ITEM_SIZE,
						MemDC, item_frame*ITEM_SIZE, 0, ITEM_SIZE, ITEM_SIZE,
						RGB(255, 255, 255)); // 아이템 스프라이트를 뿌리자
					// 흰색을 투명하게 설정핚다.
					SelectObject(MemDC, bitmap_old);

					break;
				case ITEM_DEBUFF:
					bitmap_old = (HBITMAP)SelectObject(MemDC, bitmap_item_debuff);
					TransparentBlt(LayDC, object->rect.left, object->rect.top,
						ITEM_SIZE, ITEM_SIZE,
						MemDC, item_frame*ITEM_SIZE, 0, ITEM_SIZE, ITEM_SIZE,
						RGB(255, 255, 255)); // 디벞아이템 스프라이트를 뿌리자
					// 흰색을 투명하게 설정핚다.
					SelectObject(MemDC, bitmap_old);

					break;
				}
				object = object->next;
			}

			DrawSight(LayDC); // 조준선을 그린다

			pen_old = (HPEN)SelectObject(LayDC, pen_int_bar);
			Rectangle(LayDC, top_bar.left, top_bar.top, top_bar.right, top_bar.bottom); // 상단바 그린다
			Rectangle(LayDC, bottom_bar.left, bottom_bar.top, bottom_bar.right, bottom_bar.bottom); // 하단바 그린자
			SelectObject(LayDC, pen_int_bar);

			wsprintf(temp, TEXT("STAGE : %d / SCORE : %d / %d개만 더 부수면 된다!"), next_hp,score,CLEAR_GAME-score);
			SetTextColor(LayDC, RGB(255, 0, 0));
			DrawText(LayDC, temp, -1, &top_bar,
				DT_SINGLELINE | DT_NOCLIP | DT_CENTER | DT_VCENTER); // 희망을 주는 메세지

			if (num_ball != shooted_ball) {
				wsprintf(temp,TEXT("X%d"),num_ball-shooted_ball);
				TextOut(LayDC,startX,bottom_bar.top+30,temp,wcslen(temp));
			} // 공이 몇개인지 표기한다

			if (game_phase == Phase::GAME_END) {
			
				if (win_or_lose == true) {
					wsprintf(temp, TEXT("이겼다! 보상은 게임을 클리어 했다는 성취감입니다. Score : %d"), score);
					DrawText(LayDC, temp, -1, &m_rect,
						DT_SINGLELINE | DT_NOCLIP | DT_CENTER | DT_VCENTER);//성취감 ^^
				}
				if (win_or_lose == false) {
					wsprintf(temp, TEXT("졌습니다. Score : %d"), score);
					DrawText(LayDC, temp, -1, &m_rect,
						DT_SINGLELINE | DT_NOCLIP | DT_CENTER | DT_VCENTER);// 졌을때 메세지
				}
				
				Rectangle(LayDC, exit_button.left, exit_button.top
					, exit_button.right, exit_button.bottom);
				wsprintf(temp, TEXT("Back To Title"));
				DrawText(LayDC, temp, -1, &exit_button,
					DT_SINGLELINE | DT_NOCLIP | DT_CENTER | DT_VCENTER); // 나가는 버튼을 그린다
			}

			break;

		}
		BitBlt(hdc, 0, 0, m_rect.right, m_rect.bottom, LayDC, 0, 0, SRCCOPY);
		////////////////////////////////////////////////////////////////////////////
	}
	DeleteObject(Lay);
	DeleteObject(hdc);
	DeleteDC(LayDC);
	DeleteDC(MemDC);
	DeleteDC(hdc);
}
///////////////////////////////////////////////////////////////////////////////
void CFrameWork::OnTimer(UINT id) {
	Ball* ball;
	Object* object;
	Get_Ball* gball;
	bool movingcheck; // 움직이고 있는가?
	bool isdelete; // 사이클중 삭제한적있나
	bool iscollisioned; //충돌했었늕지?
	bool damage_one_time; // 한번에 한번만 데미지를 준다
	int dice; // 확률계산 주사위
	switch (id) {
////////<실시간 업데이트>//////////////////////
	case TIMER_MENU::UPDATER:
		switch (game_phase) { // 게임 페이즈에 따라 업데이터에서 하는 연산이 다르다.
		/////////////<블럭생성 페이즈>/////////////////
		case Phase::Create_Brick_Phase:
			is_collision = false;
			is_dir_changed = false;
			is_first_drop = true;
			is_shooting = false;
			isdebuffed_lowaim = false;
			shooted_ball = 0;
			/////<공 추가>//////////
			num_ball += get_ball;

			ball = ballhead;
			while (ball->next != NULL) ball = ball->next;

			for (int i = 0; i < get_ball; ++i) {
				Ball* new_ball = (Ball*)malloc(sizeof(Ball));
				new_ball->pos_x = startX;
				new_ball->pos_y = startY;
				new_ball->x_vec = 1;
				new_ball->y_vec = 1;
				new_ball->distance = BALL_SPEED;
				new_ball->angle = 45;
				new_ball->shooted = false;
				new_ball->movtofirst = false;
				new_ball->next = NULL;
				ball->next = new_ball;
				ball = ball->next;
			} // 먹은 공의 갯수만큼 공 노드를 추가생성후 뒤에 연결한다
			get_ball = 0;

			////<블럭생성>///////
			next_num_brick = 4 + rand() % (BRICK_DEVIDE - 4);
			next_hp++;
			down_dist = 0;
			// 우선 플래그를 초기화하자

			CreateObject(1); // 블럭을 만드는 함수를 호출한다

			game_phase = Phase::Calculating_Phase;
			break;
		/////////////////////////////////////////
		////////////////<연산하는 페이즈>////////////////////
		case Phase::Calculating_Phase:
			is_ball_collecting = false;
			is_brick_moving = false;
			//////////////<오브젝트 내린다>////////////////////////////////////
			if (down_dist != mx_down_dist) { // 이러면 내려가야하는 거리만큼만 내려간다
				down_dist++;
				is_brick_moving = true;
				object = objecthead->next;
				while (object != NULL) {
					object->rect.top++;
					object->rect.bottom++;
					object = object->next;
				}
			} // 블럭을 한 단 내린다.
			isdelete = true;
			while (isdelete) { // 삭제 된적있다면 한번 더 돌리자
				isdelete = false;
				object = objecthead;
				while (object->next != NULL) {
					if (object->next->item_id == ITEM_NOTHING && object->next->rect.bottom >= bottom_bar.top) {
						win_or_lose = false; // 만약 블럭이 바닥에 닿았다면 이 변수를 false로 만들고 게임엔드 페이즈로
						game_phase = Phase::GAME_END;
						break;
					}
					if (object->next->item_id == ITEM_PLUS_BALL && object->next->rect.bottom >= bottom_bar.top-m_rect.right/GAME_BOARD_DEVIDE) {
					Object* temp = (Object*)malloc(sizeof(Object));
						get_ball++; // 공 추가 아이템이 밑바닥에 왔다면 자동으로 공을 먹는다

						if (object->next->item_id == ITEM_PLUS_BALL) {
							CreateGball(object);
						}
						//플러스아이템이라면 플러스 공을 하나 생성한다
						temp = object->next;
						object->next = temp->next;
						free(temp);
						isdelete = true;
						break;
					}
					object = object->next;
				}
			}
			num_ball += get_ball;
			ball = ballhead;
			while (ball->next != NULL) ball = ball->next;
			for (int i = 0; i < get_ball; ++i) {
				Ball* new_ball = (Ball*)malloc(sizeof(Ball));
				new_ball->pos_x = startX;
				new_ball->pos_y = startY;
				new_ball->x_vec = 1;
				new_ball->y_vec = 1;
				new_ball->distance = 3.0;
				new_ball->angle = 45;
				new_ball->shooted = false;
				new_ball->movtofirst = false;
				new_ball->next = NULL;
				ball->next = new_ball;
				ball = ball->next;
			} // 공 추가!
			get_ball = 0;
			/////////////////////////////////////////////////////
			//////<공을 모은다>/////////////////////
			gball = getballhead->next;
			while (gball != NULL) {
				if (gball->shooted == true) {
					if (gball->pos_y < bottom_bar.top - BALL_SIZE) {
						for (int i = 0; i < 16; ++i) {
							gball->pos_y += 18.0 / 16.0;
							if (gball->pos_y > bottom_bar.top) {
								gball->shooted = false;
								gball->pos_y = bottom_bar.top - BALL_SIZE;
							}
						}
					}
				}
				if (gball->movtofirst == true) {
					for (int i = 0; i < 16; ++i) {
						if (gball->pos_x < startX) {
							gball->pos_x += 18.0 / 16.0;
							is_ball_collecting = true;
						}
						else if (gball->pos_x > startX) {
							gball->pos_x -= 18.0 / 16.0;
							is_ball_collecting = true;
						}
						double x1 = max(gball->pos_x, startX);
						double x2 = min(gball->pos_x, startX); // 최대최소값 추출
						if (x1 - x2 < 1) {
							gball->pos_x = startX;
							gball->pos_y = startY;
							gball->movtofirst = false;
						}
					}
				
				
				
				}
				gball = gball->next;
			}
			ball = ballhead->next;
			while (ball!=NULL) {
				if (ball->shooted == true) {
					ball->pos_x = startX;
					ball->pos_y = startY;
					ball->shooted = false;
					ball->movtofirst = false;
				}
				double dist16 = ball->distance*3 / 16;
				for (int i=0; i < 16; ++i) {
					if (ball->pos_x < startX) {
						ball->pos_x+=dist16;
						is_ball_collecting = true;
					}
					else if (ball->pos_x > startX) {
						ball->pos_x-=dist16;
						is_ball_collecting = true;
					}
					double x1 = max(ball->pos_x, startX);
					double x2 = min(ball->pos_x, startX); // 최대최소값 추출
					if (x1 - x2 < 1) {
						ball->pos_x = startX;
						ball->pos_y = startY;
						ball->movtofirst = false;
					}
				}
				
				ball = ball->next;
			}

			if (is_ball_collecting == false && is_brick_moving == false) {
				getballhead->next = NULL; // 아이템 공 싹다 날려버려
				game_phase = Phase::Aiming_Phase;
			}
			break;
		//////////////////////////////////////////



		}
		
		break;
////////////////////////////////////////////////
	case TIMER_MENU::SHOOTING: // 공을 발사한다

		if (shooted_ball == num_ball) {
			KillTimer(m_hwnd,TIMER_MENU::SHOOTING);
		}
		ball = ballhead->next;

		for (int i = 0; i < shooted_ball; ++i) {
			ball = ball->next;
		}
		if (ball != NULL) {
			is_shooting = true; // 슈팅플래그를 켠다
			ball->x_vec = x_vk; // 방향은 조준하면서 정한걸로
			ball->y_vec = -1; // 방향은 위로
			ball->angle = angle;
			if (isdebuffed_lowaim == true) {
				ball->angle = angle - 5 * 3.14 / 180 + rand() % 10 * 3.14 / 180;
			} // 디버프가 걸린상태라면 술취한거마냥 공이 흩뿌려진단
			ball->distance = 5.0; // 기본속도는 5
			ball->shooted = true;
			shooted_ball++;
		}
		
		break;

	case TIMER_MENU::MOV_BALL:
		movingcheck = false; // 이게 movephase에서 false로 유지되면 createphase로 넘어간다
		double dist16; // 정밀한 충돌 확인을 위해 이동거리를 16등분한다
		ball = ballhead->next;
		while (ball != NULL) {
			dist16 = ball->distance / 16;
			damage_one_time = true;
			for (int i = 0; i < 16; ++i) {
				if (ball->shooted == true) {
					movingcheck = true;
					///////////<충돌전 좌표를 갱신한다>////////////
					double mx = cos(ball->angle)*dist16*ball->x_vec;
					double my = sin(ball->angle)*dist16*ball->y_vec;
					ball->pos_x += mx;
					ball->pos_y += my;


					////////////충돌 쳌 ///////////////////////////////////////////////////
					RECT collball = { ball->pos_x, ball->pos_y, // 충돌 체크 용
						ball->pos_x + BALL_SIZE , ball->pos_y + BALL_SIZE };
					 /////////////////////////////////////////////////////////
					int p_c_check; // 모서리에 부딫혔을때 충돌체크용 변수
					Object* obj = objecthead->next; // 오브젝트와 충돌 확인
					while (obj != NULL) {
						switch (obj->item_id) {
					///////////////////<블럭과의 충돌체크>////////////////////////////////
						case ITEM_NOTHING:
							if (IntersectRect(&for_col_check, &obj->rect, &collball) == true) {
								is_collision = true; // 충돌스위치를 온 한다
								iscollisioned = false; //충돌했었늕지?
								int coll_check = Collision_Rec_Ell(ball->pos_x + BALL_SIZE / 2
									, ball->pos_y + BALL_SIZE / 2, BALL_SIZE / 2, obj->rect);

								switch (coll_check) {
								case Collision_Check::Side:
									ball->x_vec *= -1;
									ball->pos_x += cos(ball->angle)*ball->x_vec *ball->distance;
									iscollisioned = true;
									break;
								case Collision_Check::Updown:
									ball->y_vec *= -1;
									ball->pos_y += sin(ball->angle)*ball->y_vec *ball->distance;
									iscollisioned = true;
									break;
								case Collision_Check::Point_LT:
									p_c_check = Collision_point_check(ball->pos_x + BALL_SIZE / 2, ball->pos_y + BALL_SIZE / 2, obj->rect.left, obj->rect.top);
									iscollisioned = true;
									switch (p_c_check) {
									case Point_Check::More_X:
										ball->x_vec *= -1;
										ball->pos_x += cos(ball->angle)*ball->distance*ball->x_vec;
										break;
									case Point_Check::More_Y:
										ball->y_vec *= -1;
										ball->pos_y += sin(ball->angle)*ball->distance*ball->y_vec;
										break;
									case Point_Check::Same:
										if (ball->x_vec == -1 && ball->y_vec == -1) {
											ball->x_vec *= -1;
											ball->y_vec *= -1;
											ball->pos_x += cos(ball->angle)*ball->distance*ball->x_vec;
											ball->pos_y += sin(ball->angle)*ball->distance*ball->y_vec;
										} // ↘
										else if (ball->x_vec == 1 && ball->y_vec == -1) {
											ball->y_vec *= -1;
											ball->pos_y += sin(ball->angle)*ball->distance*ball->y_vec;
										} // ↙
										else if (ball->x_vec == 1 && ball->y_vec == 1) {
											ball->x_vec *= -1;
											ball->pos_x += cos(ball->angle)*ball->distance*ball->x_vec;
										} // ↗
										break;
									}


									break;
								case Collision_Check::Point_LB:
									p_c_check = Collision_point_check(ball->pos_x + BALL_SIZE / 2, ball->pos_y + BALL_SIZE / 2, obj->rect.left, obj->rect.bottom);
									iscollisioned = true;
									switch (p_c_check) {
									case Point_Check::More_X:
										ball->x_vec *= -1;
										ball->pos_x += cos(ball->angle)*ball->distance*ball->x_vec;
										break;
									case Point_Check::More_Y:
										ball->y_vec *= -1;
										ball->pos_y += sin(ball->angle)*ball->distance*ball->y_vec;
										break;
									case Point_Check::Same:
										if (ball->x_vec == -1 && ball->y_vec == 1) {
											ball->x_vec *= -1;
											ball->pos_x += cos(ball->angle)*ball->distance*ball->x_vec;
										} // ↘
										else if (ball->x_vec == 1 && ball->y_vec == -1) {
											ball->x_vec *= -1;
											ball->y_vec *= -1;
											ball->pos_x += cos(ball->angle)*ball->distance*ball->x_vec;
											ball->pos_y += sin(ball->angle)*ball->distance*ball->y_vec;
										} // ↗
										else if (ball->x_vec == -1 && ball->y_vec == -1) {
											ball->y_vec *= -1;
											ball->pos_y += sin(ball->angle)*ball->distance*ball->y_vec;
										} // ↖
										break;
									}

									break;
								case Collision_Check::Point_RT:
									p_c_check = Collision_point_check(ball->pos_x + BALL_SIZE / 2, ball->pos_y + BALL_SIZE / 2, obj->rect.right, obj->rect.top);
									iscollisioned = true;
									switch (p_c_check) {
									case Point_Check::More_X:
										ball->x_vec *= -1;
										ball->pos_x += cos(ball->angle)*ball->distance*ball->x_vec;
										break;
									case Point_Check::More_Y:
										ball->y_vec *= -1;
										ball->pos_y += sin(ball->angle)*ball->distance*ball->y_vec;
										break;
									case Point_Check::Same:
										if (ball->x_vec == 1 && ball->y_vec == 1) {
											ball->y_vec *= -1;
											ball->pos_y += sin(ball->angle)*ball->distance*ball->y_vec;
										} // ↘
										else if (ball->x_vec == -1 && ball->y_vec == 1) {
											ball->x_vec *= -1;
											ball->y_vec *= -1;
											ball->pos_x += cos(ball->angle)*ball->distance*ball->x_vec;
											ball->pos_y += sin(ball->angle)*ball->distance*ball->y_vec;
										} // ↙
										else if (ball->x_vec == -1 && ball->y_vec == -1) {
											ball->x_vec *= -1;
											ball->pos_x += cos(ball->angle)*ball->distance*ball->x_vec;
										} // ↖
										break;
									}

									break;
								case Collision_Check::Point_RB:
									p_c_check = Collision_point_check(ball->pos_x + BALL_SIZE / 2, ball->pos_y + BALL_SIZE / 2, obj->rect.right, obj->rect.bottom);
									iscollisioned = true;
									switch (p_c_check) {
									case Point_Check::More_X:
										ball->x_vec *= -1;
										ball->pos_x += cos(ball->angle)*ball->distance*ball->x_vec;
										break;
									case Point_Check::More_Y:
										ball->y_vec *= -1;
										ball->pos_y += sin(ball->angle)*ball->distance*ball->y_vec;
										break;
									case Point_Check::Same:
										if (ball->x_vec == 1 && ball->y_vec == -1) {
											ball->y_vec *= -1;
											ball->pos_y += sin(ball->angle)*dist16*ball->y_vec;
										} // ↗
										else if (ball->x_vec == -1 && ball->y_vec == -1) {
											ball->x_vec *= -1;
											ball->y_vec *= -1;
											ball->pos_x += cos(ball->angle)*ball->distance*ball->x_vec;
											ball->pos_y += sin(ball->angle)*ball->distance*ball->y_vec;
										} // ↖
										else if (ball->x_vec == -1 && ball->y_vec == 1) {
											ball->x_vec *= -1;
											ball->pos_x += cos(ball->angle)*ball->distance*ball->x_vec;
										} // ↙
										break;
									}
									break;
								}
								if (iscollisioned == true) {
									if (damage_one_time == true) {
										damage_one_time = false;
										obj->hp--; // 블럭의 HP를 1 줄인다.
									}
								}
								

							}
						
							break;
					///////////////<아이템 충돌 체크>/////////////////////////////
							case ITEM_PLUS_BALL:
								if (IntersectRect(&for_col_check, &obj->rect, &collball) == true) {
									if (0 < obj->hp) {
										obj->hp--;
										get_ball++;
									}
								}
								break;
							case ITEM_CHANGE_BALL_DIR:
								if (IntersectRect(&for_col_check, &obj->rect, &collball) == true) {
									int dice = rand() % 2;
									is_dir_changed = true;
									if (dice == 0) {
										ball->x_vec *= -1;
										obj->hp--;
									}
									else {
										ball->y_vec *= -1;
										obj->hp--;
									}

								}
								break;
							case ITEM_DEBUFF:
								if (IntersectRect(&for_col_check, &obj->rect, &collball) == true) {
									obj->hp--;
									isdebuffed_lowaim = true;
								}
								break;
					///////////////////////////////////////////////////
						}
						obj = obj->next;
					}

					/////////////벽과의 충돌////////////////////////////////
					if (IntersectRect(&for_col_check, &top_bar, &collball) == true) {
						ball->y_vec *= -1;
						ball->pos_y = top_bar.bottom;
					}// 위쪽에 부딛혔다
					 ////////////////////////////////////////
					if (IntersectRect(&for_col_check, &bottom_bar, &collball) == true) {
						ball->y_vec *= -1;
						ball->pos_y = bottom_bar.top - BALL_SIZE;
						if (is_first_drop) { // 처음 떨궈진 공이라먄
							startX = ball->pos_x;
							startY = ball->pos_y; // 이공을 다음 시작점으로 만든다
							is_first_drop = false;
						}
						ball->movtofirst = true;
						ball->shooted = false; // 작동을 중지시킨다
						if (is_collision == false && isdebuffed_lowaim == false && is_dir_changed == false) { // 만약 한번도 충돌한적 없다면?, 디버프도 안받았다면
							KillTimer(m_hwnd, TIMER_MENU::SHOOTING); 
							game_phase = Phase::Create_Brick_Phase; // 블럭생성 페이즈로 넘긴다
							break;
						}
					}// 아래쪽에 부딛혔다
					if (ball->pos_x < 0) {
						ball->x_vec *= -1;
						ball->pos_x = 0;
					} // 왼쪽에 부딫혔다
					if (m_rect.right < ball->pos_x + BALL_SIZE) {
						ball->x_vec *= -1;
						ball->pos_x = m_rect.right - BALL_SIZE;
					} //오른쪽에 부딛혔다
////////////////////////////////////충돌 계산//////////////////////////////////////////////
				}
			} // 16등분하여 정밀하게 측정
			ball = ball->next;
		}

		gball = getballhead->next; // 먹은 공을 하단으로 내린다
		while (gball != NULL) {
			dist16 = gball->distance / 16.0;
			if (gball->shooted == true) {
				if (gball->pos_y < bottom_bar.top - BALL_SIZE) {
					for (int i = 0; i < 16; ++i) {
						gball->pos_y+= dist16;
						if (gball->pos_y > bottom_bar.top) {
							gball->shooted = false;
							gball->pos_y = bottom_bar.top - BALL_SIZE;
						}
					}
				}
			}
			gball = gball->next;
		}



		////////////hp가 0이 된 블럭들을 파.괘.한.다 /////////////////
		isdelete = true;
		while (isdelete) {
			isdelete = false;
			object = objecthead;
			while (object->next != NULL) {
				if (object->next->hp <= 0) {
					Object* temp = (Object*)malloc(sizeof(Object));

					
					if (object->next->item_id == ITEM_PLUS_BALL) {
						CreateGball(object); // 초록공 생성함수
					}
					//만약 없어지는 오브젝트가 플러스아이템이라면 플러스 공을 하나 생성한다
					if (object->next->item_id == ITEM_NOTHING) {
						score++;
					} // 블럭이라면 점수 ++

					temp = object->next;
					object->next = temp->next;
					free(temp);
					isdelete = true;
					break;
				}
				object = object->next;
			}
		}
		
		if (score == CLEAR_GAME) { // 클리어 조건을 만족했다면
			win_or_lose = true; // 이겼다로 반환
			game_phase = Phase::GAME_END; // 게임엔드 페이즈로 넘어간다
		}

		/////////<발사되고 있는 공 있는지 확인>/////////////////////////////////////////////
		if (game_phase == Phase::Shoot_Phase && is_shooting == true) {
			if (movingcheck == false) {
				ball = ballhead->next;
				while (ball != NULL) {
					ball->movtofirst = true; // 모든 공을 공 회수 상태로 넘긴다
					ball = ball->next;
				}
				is_shooting = false; // 공 쏘고있는지 여부를 false로 만든다
				game_phase = Phase::Create_Brick_Phase; // 블럭 생성 페이즈로 넘어간다
			}
		}
		break;

/////////////<애니메이션>////////////////////////////////
		case TIMER_MENU::ANIMATION:
			mainframe++; // 메인 프레임을 계속 ++
			item_frame = mainframe % 6; // 아이템 프레임
			ball_frame = mainframe % 11; // 공 프레임
			title_frame = mainframe % 7; // 타이틀메뉴 프레임
			start_button = { 250,350 + (LONG)title_frame,500,400 + (LONG)title_frame }; // 시작버튼
			exit_button = { 250,450 + (LONG)title_frame,500,500 + (LONG)title_frame }; // 나가는 버튼
			break;
/////////////////////////////////////////
	}

	InvalidateRect(m_hwnd, &m_rect, FALSE);
}
void CFrameWork::Resize() {
	GetClientRect(m_hwnd, &m_rect);
	InvalidateRect(m_hwnd, &m_rect, FALSE);
} // 혹시 몰라서



void CFrameWork::InputMouse(UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_LBUTTONDOWN:
		POINT mouse; // 마우스포인트
		ptmouse.x = LOWORD(lParam);
		ptmouse.y = HIWORD(lParam);
		switch (game_phase) {
		case Phase::Aiming_Phase:
			drag = true;
			ptstart.x = ballhead->pos_x;
			ptstart.y = ballhead->pos_y;
			break;
		case Phase::GAME_MENU:
			mouse = { ptmouse.x,ptmouse.y };
			if (PtInRect(&start_button, mouse)) {
				game_phase = Phase::Aiming_Phase;
			}
			else if (PtInRect(&exit_button, mouse)) {
				Destroy();
			}
			break;
		case Phase::GAME_END:
			mouse = { ptmouse.x,ptmouse.y };
			if (PtInRect(&exit_button, mouse)) {
				OnCreate();
			}
			break;
		}
		break;
	case WM_MOUSEMOVE:
		if (drag == true) {
			bool issightend = false; // 조준선이 끝에 닿았나?
			ptmouse.x = LOWORD(lParam);
			ptmouse.y = HIWORD(lParam);
			// 이 점과 공의 중점을 이어 조준선을 구현해보자
			Ball* ball = ballhead->next;

			double x1 = max(ptmouse.x, ball->pos_x + BALL_SIZE/2);
			double y1 = max(ptmouse.y, ball->pos_y + BALL_SIZE / 2);
			double x2 = min(ptmouse.x, ball->pos_x + BALL_SIZE / 2);
			double y2 = min(ptmouse.y, ball->pos_y + BALL_SIZE / 2);

			double height = y1-y2;
			double width = x1-x2;
			if (ball->pos_y < ptmouse.y) {
				ptmouse.y = ball->pos_y + BALL_SIZE / 2 - 60 ;
			}
			if (atan2(height, width) < 15.0*3.14/180) { // 15도보다 낮다면
				ptmouse.y = ball->pos_y + BALL_SIZE / 2 - 60;
			}
					
				y1 = max(ptmouse.y, ball->pos_y + BALL_SIZE / 2);
				y2 = min(ptmouse.y, ball->pos_y + BALL_SIZE / 2);

				ptend_x = ball->pos_x + BALL_SIZE / 2;
				ptend_y = ball->pos_y + BALL_SIZE / 2;

				height = y1 - y2;

				double temp_angle = atan2(height, width); // 앜탄젠트를 이용 각도를 구한다

				int temp_vec = 1;
				if (ptmouse.x < ball->pos_x + BALL_SIZE / 2)
					temp_vec = -1;

				while (0 < ptend_x && ptend_x < m_rect.right
					&& 0 < ptend_y && ptend_y < m_rect.bottom) {
					ptend_x += cos(temp_angle) * 1.0 * temp_vec;
					ptend_y -= sin(temp_angle) * 1.0; // 레이저 경로를 따라 이동시키자

					POINT pt = { ptend_x,ptend_y };

					Object* object = objecthead->next;
					while (object != NULL) {
						if (PtInRect(&object->rect, pt)) {
							if (object->exist == true && object->item_id == ITEM_NOTHING) {
								issightend = true; // 레이저포인터가 끝에 다다랐다
							}
						}
						object = object->next;
					}
					if (issightend == true) // 끝에 다다랐으니 정지
						break;
				}
		}
		break;
	case WM_LBUTTONUP:
		
		if (game_phase == Phase::Aiming_Phase && drag == true) { //지금 조준페이즈에 드래그가 되있따면
			drag = false; // 드래그를 없애고
			Ball* ball = ballhead->next;
			double x1 = max(ptmouse.x, ball->pos_x + BALL_SIZE / 2);
			double y1 = max(ptmouse.y, ball->pos_y + BALL_SIZE / 2);
			double x2 = min(ptmouse.x, ball->pos_x + BALL_SIZE / 2);
			double y2 = min(ptmouse.y, ball->pos_y + BALL_SIZE / 2);
			double height = y1 - y2; //마우스와 공 사이의 높이와
			double width = x1 - x2;// 너비를 구한다

			if (ball->pos_x + BALL_SIZE / 2 < ptmouse.x)
				x_vk = 1; // 마우스보다 공이 왼쪽에 있을때
			else
				x_vk = -1; // 마우스보다 공이 오른쪽에 있을때

				angle = atan2(height, width); //앜탄젠트로 각도반영한다

			shooted_ball = 0;

			SetTimer(m_hwnd,TIMER_MENU::SHOOTING,80,NULL);
			game_phase = Phase::Shoot_Phase; // 슈팅페이즈로 넘어간다
		}

	}
	InvalidateRect(m_hwnd, &m_rect, FALSE);
}
void CFrameWork::InputKeyBoard(UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_KEYDOWN:
		break;
	}
	InvalidateRect(m_hwnd, &m_rect, FALSE); // 키 입력은 없는데 혹시 모르니 넣어보았다
}
void CFrameWork::CreateBkBrush(COLORREF color) {
	if (hbrBackground) DeleteObject(hbrBackground);
	hbrBackground = (HBRUSH)CreateSolidBrush(color);
}
void CFrameWork::ClearScreen(HDC hdc) {
	FillRect(hdc, &m_rect, hbrBackground);
}
void CFrameWork::DrawSight(HDC hdc) {
	///////////<조준선 그리기>////////////////////////////////////////
	if (drag == true) {
		pen_old = (HPEN)SelectObject(hdc, pen_sight);

		Ball* ball = ballhead->next;
		MoveToEx(hdc, ball->pos_x + BALL_SIZE / 2
			, ball->pos_y + BALL_SIZE / 2, NULL);
		LineTo(hdc, ptend_x, ptend_y); // 끝없는 선을 긋는다

		SelectObject(hdc, pen_old);
	}
	///////////////////////////////////////////////////////////////

}
float CFrameWork::LengthPts(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)));
}

BOOL CFrameWork::InCircle(double x, double y, double rad, double px, double py)
{
	if (LengthPts(x, y, px, py) < rad)
		return TRUE;
	else
		return FALSE;
}
//////////////////////////////////////////////////////////////////////
int CFrameWork::Collision_Rec_Ell(double c_x, double c_y, double c_rad, RECT rec_check) {
	if ((rec_check.left <= c_x && c_x <= rec_check.right) ||
		(rec_check.top <= c_y && c_y <= rec_check.bottom)) {
		RECT rec_ud_chk = {
			rec_check.left,
			rec_check.top - c_rad,
			rec_check.right,
			rec_check.bottom + c_rad,
		};
		RECT rec_sd_chk = {
			rec_check.left - c_rad,
			rec_check.top,
			rec_check.right + c_rad,
			rec_check.bottom,
		};
		if ((rec_ud_chk.left < c_x && c_x < rec_ud_chk.right) && (rec_ud_chk.top < c_y && c_y < rec_ud_chk.bottom)) {
			return Collision_Check::Updown;
		}
		if ((rec_sd_chk.left < c_x && c_x < rec_sd_chk.right) && (rec_sd_chk.top < c_y && c_y < rec_sd_chk.bottom)) {
			return Collision_Check::Side;
		}
	}

	else {
		if (InCircle(c_x, c_y, c_rad, rec_check.left, rec_check.top))return Collision_Check::Point_LT;
		if (InCircle(c_x, c_y, c_rad, rec_check.left, rec_check.bottom))return Collision_Check::Point_LB;
		if (InCircle(c_x, c_y, c_rad, rec_check.right, rec_check.top))return Collision_Check::Point_RT;
		if (InCircle(c_x, c_y, c_rad, rec_check.right, rec_check.bottom))return Collision_Check::Point_RB;
	}
	return Collision_Check::No;
}
/////////////////////////////////////////////////////////////////////////
int CFrameWork::Collision_point_check(double c_x, double c_y, double b_x, double b_y) {
	double x1 = min(c_x, b_x);
	double y1 = min(c_y, b_y);
	double x2 = max(c_x, b_x);
	double y2 = max(c_y, b_y);
	double width = x2 - x1;
	double height = y2 - y1;

	if (width < height) {
		return Point_Check::More_Y;
	}
	else if (width == height) {
		return Point_Check::Same;
	}
	else if (width > height) {
		return Point_Check::More_X;
	}
}
///////<블럭을 만든다>
void CFrameWork::CreateObject(int pos) {

	Object* object;
	int created_brick;
	int created_plusitem;
	int dice; // 주사위

	for (int i = 0; i < BRICK_DEVIDE; ++i) {
		set_brick[i] = { { 0,0,0,0 },0,false,ITEM_NOTHING, NULL }; // 초기화한다
	}
	created_brick = 0;
	while (created_brick != next_num_brick) {
		int i = rand() % BRICK_DEVIDE; // 위치를 랜덤 지정하자
		if (set_brick[i].exist == false) {
			set_brick[i].rect.left = i*m_rect.right / BRICK_DEVIDE;
			set_brick[i].rect.top = pos * m_rect.bottom / (GAME_BOARD_DEVIDE);
			set_brick[i].rect.right = (i + 1)*m_rect.right / BRICK_DEVIDE;
			set_brick[i].rect.bottom = (pos + 1) * m_rect.bottom / (GAME_BOARD_DEVIDE);
			set_brick[i].hp = next_hp;
			set_brick[i].exist = true;
			set_brick[i].item_id = ITEM_NOTHING;
			set_brick[i].next = NULL;
			created_brick++;
		}
	};
	created_plusitem = 0;
	while (created_plusitem != 1) {
		int i = rand() % BRICK_DEVIDE; // 위치를 랜덤 지정하자
		if (set_brick[i].exist == true && set_brick[i].item_id == ITEM_NOTHING) {
			double setpositem_x =
				set_brick[i].rect.left + (set_brick[i].rect.right - set_brick[i].rect.left) / 2 - ITEM_SIZE / 2;
			double setpositem_y =
				set_brick[i].rect.top + (set_brick[i].rect.bottom - set_brick[i].rect.top) / 2 - ITEM_SIZE / 2;;
			set_brick[i].rect.left = setpositem_x;
			set_brick[i].rect.top = setpositem_y;
			set_brick[i].rect.right = setpositem_x + ITEM_SIZE;
			set_brick[i].rect.bottom = setpositem_y + ITEM_SIZE;
			set_brick[i].hp = 1;
			set_brick[i].exist = true;
			set_brick[i].item_id = ITEM_PLUS_BALL;
			set_brick[i].next = NULL;
			created_plusitem++;
		}
	};

	created_plusitem = 0;
	while (created_plusitem != 1) {
		int i = rand() % BRICK_DEVIDE; // 위치를 랜덤 지정하자
		if (set_brick[i].exist == true && set_brick[i].item_id == ITEM_NOTHING) {
			double setpositem_x =
				set_brick[i].rect.left + (set_brick[i].rect.right - set_brick[i].rect.left) / 2 - ITEM_SIZE / 2;
			double setpositem_y =
				set_brick[i].rect.top + (set_brick[i].rect.bottom - set_brick[i].rect.top) / 2 - ITEM_SIZE / 2;;
			set_brick[i].rect.left = setpositem_x;
			set_brick[i].rect.top = setpositem_y;
			set_brick[i].rect.right = setpositem_x + ITEM_SIZE;
			set_brick[i].rect.bottom = setpositem_y + ITEM_SIZE;
			set_brick[i].hp = 1;
			set_brick[i].exist = true;
			set_brick[i].item_id = ITEM_CHANGE_BALL_DIR;
			set_brick[i].next = NULL;
			created_plusitem++;
		}
	};

	dice = rand() % 4;
	if (dice == 0) {
		created_plusitem = 0;
		while (created_plusitem != 1) {
			int i = rand() % BRICK_DEVIDE; // 위치를 랜덤 지정하자
			if (set_brick[i].exist == true && set_brick[i].item_id == ITEM_NOTHING) {
				double setpositem_x =
					set_brick[i].rect.left + (set_brick[i].rect.right - set_brick[i].rect.left) / 2 - ITEM_SIZE / 2;
				double setpositem_y =
					set_brick[i].rect.top + (set_brick[i].rect.bottom - set_brick[i].rect.top) / 2 - ITEM_SIZE / 2;;
				set_brick[i].rect.left = setpositem_x;
				set_brick[i].rect.top = setpositem_y;
				set_brick[i].rect.right = setpositem_x + ITEM_SIZE;
				set_brick[i].rect.bottom = setpositem_y + ITEM_SIZE;
				set_brick[i].hp = 1;
				set_brick[i].exist = true;
				set_brick[i].item_id = ITEM_DEBUFF;
				set_brick[i].next = NULL;
				created_plusitem++;
			}
		};
	}

	object = objecthead;

	while (object->next != NULL) object = object->next;
	for (int i = 0; i < BRICK_DEVIDE; ++i) {
		if (set_brick[i].exist == true) { // 만약 오브젝트가 생성되었다면?
			Object* new_object = (Object*)malloc(sizeof(Object));

			new_object->rect.left = set_brick[i].rect.left;
			new_object->rect.top = set_brick[i].rect.top;
			new_object->rect.right = set_brick[i].rect.right;
			new_object->rect.bottom = set_brick[i].rect.bottom;
			new_object->exist = set_brick[i].exist;
			new_object->hp = set_brick[i].hp;
			new_object->item_id = set_brick[i].item_id;
			new_object->next = NULL;

			if (objecthead->next == NULL) {
				objecthead->next = new_object;
			}
			object->next = new_object;
			object = object->next;
		}
	}
}
void CFrameWork::CreateGball(Object* object) { // 초록색 공을 생성한다
	Get_Ball * gball = getballhead;
	while (gball->next != NULL) gball = gball->next;
	Get_Ball* new_gball = (Get_Ball*)malloc(sizeof(Get_Ball));
	new_gball->pos_x = object->next->rect.left + ITEM_SIZE / 2;
	new_gball->pos_y = object->next->rect.top + ITEM_SIZE / 2;
	new_gball->distance = 6.0;
	new_gball->movtofirst = true;
	new_gball->shooted = true;
	new_gball->next = NULL;
	gball->next = new_gball;
}
