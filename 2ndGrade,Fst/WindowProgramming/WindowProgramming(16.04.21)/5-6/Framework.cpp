#include "stdafx.h"
#include "FrameWork.h"
#include "Puzzle.h"

CFrameWork::CFrameWork()
{

}

CFrameWork::~CFrameWork()
{
	Destroy();
}
// 클래스 함수선언은 헤더에서 하는게 아니고 cpp 파일에 한다.
bool CFrameWork::Initial(HWND h, RECT r, HINSTANCE inst) {
	// 변수명 앞에 자료형 쓰면 그건 지역변수가 되어버린다
	m_hwnd = h;
	m_rect = r;
	m_hinstance = inst;
	return m_hwnd != NULL; // 윈도우 생성 실패하면 윈도우 핸들이 NULL 값이 들어간다.
						   // 이값이 NULL값일 경우 윈도우가 제대로 만들어지지 않았다는것, 널값이면 윈도우를 죽여라!
}
void CFrameWork::Destroy() { // 반환값은 없어도 상관없다, 어쩌피 죽을테니까, 메모리 누수 방지
							 //소멸자로 소멸할때 Destroy 호출, 소멸자는 함수가 죽어야만 나온다 , 죽이고 다시 생성하고 싶을때 쓰자
							 // 대를 잇게 할때 -> 그떄를 위해 함수를 미리 빼 놓는다

};

LRESULT CFrameWork::WindowMessage(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
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
		PostQuitMessage(0);
		return 0;
	} //처리할 메시지만 case문에 나열
	return(DefWindowProc(hwnd, iMessage, wParam, lParam));// CASE에서 정의되지 않은 메시지는 커널이 처리하도록 메시지 전달 
}

void CFrameWork::OnCreate() { // 나중에 3-1학기떄 BuildObject 로 쓴다 , 동적메모리 릴리즈 용
	GetClientRect(m_hwnd, &m_rect);
	CreateBkBrush(RGB(255, 255, 255));

	srand((unsigned)time(NULL));
	backimage = (HBITMAP)LoadBitmap(m_hinstance, // hinstance 인수는 맨위에 선언한 HINSTANCE 값으로..
		MAKEINTRESOURCE(IDB_BITMAP1));

	moved_rect = {0,0,0,0};
	SetTimer(m_hwnd, 1, 1, NULL);
}
void CFrameWork::OnDraw(HDC hdc) { //여기다 드로우를 처리한다
	HDC LayDC;
	LayDC = CreateCompatibleDC(hdc); // hdc와 호환시킨다.
	HBITMAP Lay; // 레이어 생성
	Lay = CreateCompatibleBitmap(hdc, m_rect.right, m_rect.bottom); // 다블 버퍼링 ,hdc와 호환시키자.
	SelectObject(LayDC, Lay);
	{
		ClearScreen(LayDC); // 화면 클리어
		MemDC = CreateCompatibleDC(LayDC); // 이건 비트맵 뿌리기용

		SetBkMode(LayDC, TRANSPARENT);
		//////<여기다 그린다>//////////////////////////////////////////////////////////////////
		SelectObject(MemDC, backimage);
		
		switch (screenmode) {
		case 0:
			BitBlt(LayDC, 0, 0, m_rect.right, m_rect.bottom, MemDC, 0, 0, SRCCOPY);
			break;
		case 3:
			Draw_image(screenmode, LayDC, MemDC);
			break;
		case 4:
			Draw_image(screenmode, LayDC, MemDC);
			break;
		case 5:
			Draw_image(screenmode, LayDC, MemDC);
			break;
		}
		//////////////////////////////////////////////////////////////////////
		BitBlt(hdc, 0, 0, m_rect.right, m_rect.bottom, LayDC, 0, 0, SRCCOPY);
	}
	DeleteObject(Lay);
	DeleteObject(hdc);

	DeleteDC(LayDC);
	DeleteDC(MemDC);
	DeleteDC(hdc);
}
void CFrameWork::OnTimer(UINT id) {
	bool ismoved = false;
	bool isstoped = false;
	switch (id) {
	case WT_MOVINGPIECE:
		for (int i=0; i < screenmode; ++i) {
			for (int j=0; j < screenmode; ++j) {
				if (!(i == blanked_pos.y && j == blanked_pos.x)) {
				
					if (puzzle[i][j].getMoving() == true) {
						if (puzzle[blanked_pos.y][blanked_pos.x].getPos().left <
							puzzle[i][j].getPos().left &&
							puzzle[blanked_pos.y][blanked_pos.x].getPos().left !=
							puzzle[i][j].getPos().left
							) {
							puzzle[i][j].moverect(left);
							ismoved = true;
							if (puzzle[blanked_pos.y][blanked_pos.x].getPos().left ==
								puzzle[i][j].getPos().left) {
								gamestate = Game_Stat::gameon;
								if (ismoved && !isstoped)
									puzzle[blanked_pos.y][blanked_pos.x].CopyPos(moved_rect);
								puzzle[i][j].setmoving(false);
								KillTimer(m_hwnd, WT_MOVINGPIECE);
								isstoped = true;
								break;
							}
							break;
						}
						if (puzzle[blanked_pos.y][blanked_pos.x].getPos().left >
							puzzle[i][j].getPos().left &&
							puzzle[blanked_pos.y][blanked_pos.x].getPos().left !=
							puzzle[i][j].getPos().left
							) {
							puzzle[i][j].moverect(right);
							ismoved = true;
							if (puzzle[blanked_pos.y][blanked_pos.x].getPos().left ==
								puzzle[i][j].getPos().left) {
								gamestate = Game_Stat::gameon;
								if (ismoved && !isstoped)
									puzzle[blanked_pos.y][blanked_pos.x].CopyPos(moved_rect);
								puzzle[i][j].setmoving(false);
								KillTimer(m_hwnd, WT_MOVINGPIECE);
								isstoped = true;
								break;
							}
							break;
						}
						if (puzzle[blanked_pos.y][blanked_pos.x].getPos().top <
							puzzle[i][j].getPos().top
							&& puzzle[blanked_pos.y][blanked_pos.x].getPos().top !=
							puzzle[i][j].getPos().top
							) {
							puzzle[i][j].moverect(up);
							ismoved = true;
							if (puzzle[blanked_pos.y][blanked_pos.x].getPos().top ==
								puzzle[i][j].getPos().top) {
								gamestate = Game_Stat::gameon;
								if (ismoved && !isstoped)
									puzzle[blanked_pos.y][blanked_pos.x].CopyPos(moved_rect);
								puzzle[i][j].setmoving(false);
								KillTimer(m_hwnd, WT_MOVINGPIECE);
								isstoped = true;
								break;
							}
							break;
						}
						if (puzzle[blanked_pos.y][blanked_pos.x].getPos().top >
							puzzle[i][j].getPos().top &&
							puzzle[blanked_pos.y][blanked_pos.x].getPos().top !=
							puzzle[i][j].getPos().top
							) {
							puzzle[i][j].moverect(down);
							ismoved = true;
							if (puzzle[blanked_pos.y][blanked_pos.x].getPos().top ==
								puzzle[i][j].getPos().top) {
								gamestate = Game_Stat::gameon;
								if (ismoved && !isstoped)
									puzzle[blanked_pos.y][blanked_pos.x].CopyPos(moved_rect);
								puzzle[i][j].setmoving(false);
								KillTimer(m_hwnd, WT_MOVINGPIECE);
								isstoped = true;
								break;
							}
							break;
						}

					}
				
				}
				
			}

			if (ismoved == true || isstoped == true)
				break;
		}
		break;
	}
	InvalidateRect(m_hwnd, &m_rect, FALSE);
}
void CFrameWork::InputMouse(UINT iMessage, WPARAM wParam, LPARAM lParam) {
	bool isselected = false;
	switch (iMessage) {
	case WM_LBUTTONDOWN:
		if (gamestate == Game_Stat::gameon) {
			ptmouse.x = LOWORD(lParam);
			ptmouse.y = HIWORD(lParam);
			pt_left = { ptmouse.x - m_rect.right/screenmode + 1 ,ptmouse.y };
			pt_right = { ptmouse.x + m_rect.right / screenmode - 1 ,ptmouse.y };
			pt_up = { ptmouse.x ,ptmouse.y - m_rect.bottom / screenmode + 1 };
			pt_down = { ptmouse.x ,ptmouse.y + m_rect.bottom / screenmode -1 };
			for (int i = 0; i < screenmode; ++i) {
				for (int j = 0; j < screenmode; ++j) {
				
					if (PtInRect(&puzzle[i][j].getPos(), ptmouse)
						&& puzzle[i][j].getViewed() == true
						&& !(PtInRect(&puzzle[blanked_pos.y][blanked_pos.x].getPos(),
							ptmouse))
						) {
						if (
							PtInRect(&puzzle[blanked_pos.y][blanked_pos.x].getPos(),
								pt_left) ||
							PtInRect(&puzzle[blanked_pos.y][blanked_pos.x].getPos(),
								pt_right) ||
							PtInRect(&puzzle[blanked_pos.y][blanked_pos.x].getPos(),
								pt_up) ||
							PtInRect(&puzzle[blanked_pos.y][blanked_pos.x].getPos(),
								pt_down)
							) {
							puzzle[i][j].setmoving(true);
							moved_rect = puzzle[i][j].getPos();
							SetTimer(m_hwnd, WT_MOVINGPIECE, 1, NULL);
							gamestate = Game_Stat::moving;
							isselected = true;
							break;
						}
					}
				}
				if (isselected == true) {break;}
			}
		}
		
		break;
	}
	InvalidateRect(m_hwnd, &m_rect, FALSE);
}
void CFrameWork::InputKeyBoard(UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_KEYDOWN:
			switch(wParam){
			case '3':
				if (gamestate == gameset) {
					screenmode = 3;
					createPuzzle();
					Shuffle_image();
				}
				break;
			case '4':
				if (gamestate == gameset) {
					screenmode = 4;
					createPuzzle();
					Shuffle_image();
				}
				break;
			case '5':
				if (gamestate == gameset) {
					screenmode = 5;
					createPuzzle();
					Shuffle_image();
				}
				break;
			case 'F':
			case 'f':
				if (gamestate != Game_Stat::moving) {
					gamestate = Game_Stat::gameset;
					KillTimer(m_hwnd, WT_MOVINGPIECE);
					screenmode = 0;
				}
				
				break;
			case 'S':
			case 's':
				if (gamestate == Game_Stat::gameset && screenmode!=0) {
					gamestate = Game_Stat::gameon;
					temp_pos.x = rand() % screenmode;
					temp_pos.y = rand() % screenmode;
					puzzle[temp_pos.y][temp_pos.x].setviewed(false);
					blanked_pos = {temp_pos.x,temp_pos.y};
				}
				break;
			}
		break;
	}
	InvalidateRect(m_hwnd, &m_rect, FALSE);
}
void CFrameWork::CreateBkBrush(COLORREF color) {
	if (hbrBackground) DeleteObject(hbrBackground);
	hbrBackground = (HBRUSH)CreateSolidBrush(color);
}
void CFrameWork::ClearScreen(HDC hdc) {
	FillRect(hdc, &m_rect, hbrBackground);
}
void CFrameWork::Draw_image(int screenmode,HDC LayDC,HDC MemDC){

	for (int i = 0; i < screenmode; ++i) {
		for (int j = 0; j < screenmode; ++j) {
			if (puzzle[i][j].getViewed()) {
				StretchBlt(LayDC,
					puzzle[i][j].getPos().left,
					puzzle[i][j].getPos().top,
					m_rect.right / screenmode,
					m_rect.bottom / screenmode,
					MemDC,
					puzzle[i][j].getImagepos().x*m_rect.right / screenmode,
					puzzle[i][j].getImagepos().y*m_rect.bottom / screenmode,
					m_rect.right / screenmode,
					m_rect.bottom / screenmode,
					SRCCOPY);
			}
			
		}
	}
}

void CFrameWork::Shuffle_image() {

	for (int i = 0; i < SHUFFLE_TIME; ++i) {
		POINT temp;
		POINT rand_po_1 = { rand() % screenmode,rand() % screenmode };
		POINT rand_po_2 = { rand() % screenmode,rand() % screenmode };
		temp = puzzle[rand_po_1.y][rand_po_1.x].getImagepos();
		puzzle[rand_po_1.y][rand_po_1.x]
			.setimagepos(
				puzzle[rand_po_2.y][rand_po_2.x].getImagepos().y,
				puzzle[rand_po_2.y][rand_po_2.x].getImagepos().x);
		puzzle[rand_po_2.y][rand_po_2.x].setimagepos(temp.y, temp.x);
	}

}

void CFrameWork::createPuzzle() {
	for (int i = 0; i < screenmode; ++i) {
		for (int j = 0; j < screenmode; ++j) {
			puzzle[i][j].setimagepos(i, j);
			puzzle[i][j].SetPos(i, j, screenmode, m_rect);
			puzzle[i][j].setviewed(true);
		}
	}//초기화
}