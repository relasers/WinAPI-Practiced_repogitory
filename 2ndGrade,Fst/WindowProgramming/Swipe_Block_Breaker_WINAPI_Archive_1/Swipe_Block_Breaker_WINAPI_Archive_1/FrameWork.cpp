#include "stdafx.h"
#include "FrameWork.h"

CFrameWork::CFrameWork()
{

}
CFrameWork::~CFrameWork()
{
	Destroy();
}
// Ŭ���� �Լ������� ������� �ϴ°� �ƴϰ� cpp ���Ͽ� �Ѵ�.
bool CFrameWork::Initial(HWND h, RECT r, HINSTANCE hInst) {
	// ������ �տ� �ڷ��� ���� �װ� ���������� �Ǿ������
	m_hwnd = h;
	m_rect = r;
	m_hinst = hInst;
	return m_hwnd != NULL; // ������ ���� �����ϸ� ������ �ڵ��� NULL ���� ����.
						   // �̰��� NULL���� ��� �����찡 ����� ��������� �ʾҴٴ°�, �ΰ��̸� �����츦 �׿���!
}
void CFrameWork::Destroy() { // ��ȯ���� ��� �������, ��¼�� �����״ϱ�, �޸� ���� ����
							 //�Ҹ��ڷ� �Ҹ��Ҷ� Destroy ȣ��, �Ҹ��ڴ� �Լ��� �׾�߸� ���´� , ���̰� �ٽ� �����ϰ� ������ ����
							 // �븦 �հ� �Ҷ� -> �׋��� ���� �Լ��� �̸� �� ���´�
	DeleteObject(bitmap_background);
	DeleteObject(bitmap_ball);
	DeleteObject(bitmap_gball);
	DeleteObject(bitmap_item_change_dir);
	DeleteObject(bitmap_item_debuff);
	DeleteObject(bitmap_item_plus);

	KillTimer(m_hwnd, TIMER_MENU::UPDATER); // ���ӻ��¸� ������Ʈ �Ѵ�
	KillTimer(m_hwnd, TIMER_MENU::MOV_BALL); // ���� �����̴� Ÿ�̸�
	KillTimer(m_hwnd, TIMER_MENU::ANIMATION); // �ִϸ��̼� Ÿ�̸�
	
	PostQuitMessage(0);
};

LRESULT CFrameWork::WindowMessage(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {

	PAINTSTRUCT ps;
	HDC hdc; // �׻� ù��° ���ڴ� hDC ��! 

	switch (iMessage) {// �޽��� ��ȣ// case: �޽����� ���� ó��
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
	case WM_PAINT: //������ �ٽ� �׷���� �� ��
		hdc = BeginPaint(hwnd, &ps); // WM_PAINT �޼������� ��� , �� �ܿ��� ������ GetDC(),ReleaseDC() �� ����(��� ����Ҷ�)

		OnDraw(hdc); // hdc �� OnDraw �� �ѱ��.

		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		Destroy();
		return 0;
	} //ó���� �޽����� case���� ����
	return(DefWindowProc(hwnd, iMessage, wParam, lParam));// CASE���� ���ǵ��� ���� �޽����� Ŀ���� ó���ϵ��� �޽��� ���� 
}
void CFrameWork::OnCreate() { // ���߿� 3-1�б⋚ BuildObject �� ���� , �����޸� ������ ��
	GetClientRect(m_hwnd, &m_rect);
	CreateBkBrush(RGB(255, 255, 255));
	PlaySound(L"BackGroundSound.wav",NULL,SND_ASYNC|SND_LOOP); // ��������� ����Ѵ�, ASYNC -> �񵿱�ȭ, ������ ������
	srand((unsigned)time(NULL)); // ������ �õ����
	/////////////////////////<�׷��� ������>///////////////////////////////
	pen_sight = (HPEN)CreatePen(PS_DASH,3,RGB(0,150,255));
	bitmap_background = (HBITMAP)LoadBitmap(m_hinst, // m_hinstance �μ��� ������ ������ m_hinstANCE ������..
	MAKEINTRESOURCE(IDB_BACKGROUND)); // ���ȭ���� �ҷ��´�
	bitmap_item_plus = (HBITMAP)LoadBitmap(m_hinst, // �� �߰� ������ ��������Ʈ�� �ҷ��´�
		MAKEINTRESOURCE(IDB_ITEM_PLUS));
	bitmap_item_change_dir = (HBITMAP)LoadBitmap(m_hinst, // �� ������ȯ ������ ��������Ʈ�� �ҷ��´�
		MAKEINTRESOURCE(IDB_ITEM_CHANGE_DIR));
	bitmap_item_debuff = (HBITMAP)LoadBitmap(m_hinst, // �� �߻� ����� ������ ��������Ʈ�� �ҷ��´�
		MAKEINTRESOURCE(IDB_ITEM_DEBUFF));
	bitmap_ball = (HBITMAP)LoadBitmap(m_hinst, //�� ��������Ʈ�� �ҷ��´�
		MAKEINTRESOURCE(IDB_BALL));
	bitmap_gball = (HBITMAP)LoadBitmap(m_hinst, // ����� ��������Ʈ�� �ҷ��´�
		MAKEINTRESOURCE(IDB_G_BALL));
	bitmap_title = (HBITMAP)LoadBitmap(m_hinst, // Ÿ��Ʋ ȭ�� ��������Ʈ�� �ҷ��´�
		MAKEINTRESOURCE(IDB_TITLEBG));
	bitmap_subtitle = (HBITMAP)LoadBitmap(m_hinst, // ���� ��������Ʈ�� �ҷ��´�
		MAKEINTRESOURCE(IDB_SUBTITLE));


	mainframe = 0;
	ball_frame = 0;
	item_frame = 0;
	title_frame = 0;
	/////////<���� ���� ������>//////////////////////////////////
	game_phase = Phase::GAME_MENU;

	is_collision = false; // ���� ���� �浹���� �ִ°�?
	is_first_drop = true; // ���� ó�� ��������?
	is_shooting = false; // �� ��� �ִ°�?
	is_dir_changed = false; // ���� ������ȯ �����۰� �浹�� �� �ִ°�?
	is_ball_collecting = false; // ���� ȸ���ǰ� �ִ°�?
	is_brick_moving = false; // ���� �����̴����ΰ�?

	isdebuffed_lowaim = false; //������� �ɷȴ°�?
	drag = false;
	coll_check = 0; // �浹üũ��

	next_hp = 1; // ���� ���� �� HP
	next_num_brick = 4; //���� �� �� �� �ּ� 4���� ��������
	next_num_plus_item = 1; // �� �߰��ϴ� ������ ������ ������ 1���� ������
	score = 0; // ����

	startX = CLIENT_WIDTH / 2; // �ʱ� �� ��ġ
	startY = bottom_bar.top - BALL_SIZE; // �ʱ� �� ��ġ

	mx_down_dist = m_rect.bottom / GAME_BOARD_DEVIDE; //������Ʈ �������� �Ÿ� 
	down_dist = 0; // ������Ʈ�� ������ �Ÿ�

	get_ball = 0; // ȹ���� ���� ��
	shooted_ball = 0; // �߻��� ���� ��
	num_ball = 100; // ó�� ���� ��

	x_vk = 1; // �ʱ� ���� ��
	angle = 1; // �ʱ� ���� ��

	///////////<���� �������̽�>/////////////////////////////////////////
	top_bar = {-3,-3,m_rect.right + 3, m_rect.bottom/GAME_BOARD_DEVIDE}; // ��� ��
	bottom_bar = {-3,m_rect.bottom - 2*m_rect.bottom/GAME_BOARD_DEVIDE-12, 
	m_rect.right + 3,m_rect.bottom + 3}; // �ϴ� ��

	start_button = { 300,350,500,400 }; // ���۹�ư
	exit_button = { 300,450,500,500 }; // ������ ��ư, �Ŀ� Ÿ��Ʋ ȭ������ ���ư��� ��ư�� ����


	///////////////////////////////////////////////�� ������ ����
	ballhead = (Ball*)malloc(sizeof(Ball));
	Ball* p = ballhead; // ���� ��������͸� �����غ���
	for (int i = 0; i < num_ball; ++i) {
		Ball* ball = (Ball*)malloc(sizeof(Ball));
		ball->pos_x = CLIENT_WIDTH / 2; // �ʱ���ġ�� Ŭ���� �߾�
		ball->pos_y = bottom_bar.top - BALL_SIZE; // �ϴ� ���� ��ܿ� ��ġ�ϵ����Ѵ�
		ball->x_vec = 1; // 1, -1, �� ���������Ѵ�
		ball->y_vec = 1; // ���� ����
		ball->distance = BALL_SPEED; // �ӵ��� ����Ʈ������ ����
		ball->angle = 45*3.14/180; // ������ 45�� , ��¼�� ���콺�� �������� �ٽ��Ѵ�.
		ball->shooted = false; // �i�°�?
		ball->movtofirst = false; // ���� ȸ�����ϰ� �ִ°�?
		ball->next = NULL; 
		p->next = ball;
		p = p->next;
	} // ���� num_ball ����ŭ �����Ѵ�.

	//////////////////<������ ������ ����>/////////////////////
	getballhead = (Get_Ball*)malloc(sizeof(Get_Ball));
	getballhead->next = NULL; // �������� ��������͸� ������, ������ �Ծ����� ������ �ʷϻ� ���̴�
	///////////////////////<�� ����>///////////////////////////////////
	objecthead = (Object*)malloc(sizeof(Object));
	objecthead->next = NULL; // ������Ʈ�� ��������͸� ������

	CreateObject(2); // ���� ������, ���ڴ� ������ġ,, ó���̴ϱ� �ι�°
	///////////////////////////////////////////////////////////////////// 

	SetTimer(m_hwnd, TIMER_MENU::UPDATER, 10, NULL); // ���ӻ��¸� ������Ʈ �Ѵ�
	SetTimer(m_hwnd, TIMER_MENU::MOV_BALL, 10, NULL); // ���� �����̴� Ÿ�̸�
	SetTimer(m_hwnd, TIMER_MENU::ANIMATION, 60, NULL); //�ִϸ��̼�  Ÿ�̸�
}
////////////////<�׸��� ��>/////////////////////////////////////////////
void CFrameWork::OnDraw(HDC hdc) {
	
	HDC LayDC;
	LayDC = CreateCompatibleDC(hdc); // hdc�� ȣȯ��Ų��.
	HBITMAP Lay; // ���̾� ����
	HBRUSH block_brush; // ���� ���� �귯���� �����
	int block_color; // �� ���� �ٲٱ�� ����
	Lay = CreateCompatibleBitmap(hdc, m_rect.right, m_rect.bottom); // �ٺ� ���۸� ,hdc�� ȣȯ��Ű��.
	SelectObject(LayDC, Lay);
	{
////////////////////////////////////////////////////////////////////////////
		SetBkMode(LayDC, TRANSPARENT);
		ClearScreen(LayDC); // ȭ�� Ŭ����
		MemDC = CreateCompatibleDC(LayDC); // �̰� ��Ʈ�� �Ѹ����
		
		switch (game_phase) {
		case Phase::GAME_MENU: // ���Ӹ޴�
			bitmap_old = (HBITMAP)SelectObject(MemDC, bitmap_title);
			BitBlt(LayDC, 0, 0, 600, 660, MemDC, title_frame*600, 0, SRCCOPY); // Ÿ��Ʋȭ���� �׸���
			SelectObject(MemDC, bitmap_old);

			bitmap_old = (HBITMAP)SelectObject(MemDC, bitmap_subtitle);
			TransparentBlt(LayDC, 50, 50 + title_frame,
				300, 200,
				MemDC, 0, 0, 300, 200,
				RGB(255, 255, 255)); // Ÿ��Ʋ ������ �׸���
			// ����� �����ϰ� ��������.
			SelectObject(MemDC, bitmap_old);

			block_brush = (HBRUSH)CreateSolidBrush(RGB(230,150,150)); // ��ư �귯��
			brush_old = (HBRUSH)SelectObject(LayDC,block_brush);
			Rectangle(LayDC, start_button.left, start_button.top
				, start_button.right, start_button.bottom); // ���۹�ư
			Rectangle(LayDC, exit_button.left, exit_button.top
				, exit_button.right, exit_button.bottom); // �����ư
			wsprintf(temp, TEXT("START"));
			DrawText(LayDC, temp, -1, &start_button,
				DT_SINGLELINE | DT_NOCLIP | DT_CENTER | DT_VCENTER); // ���۹��ڿ�
			wsprintf(temp, TEXT("EXIT"));
			DrawText(LayDC, temp, -1, &exit_button,
				DT_SINGLELINE | DT_NOCLIP | DT_CENTER | DT_VCENTER); // ���Ṯ�ڿ�
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
			BitBlt(LayDC, 0, 0, 600, 660, MemDC, 0, 0, SRCCOPY); // ���ȭ���� �׸���
			// SRCCOPY : �������� �����ϰ� �׷���
			SelectObject(MemDC, bitmap_old);

			while (ball != NULL) {
				bitmap_old = (HBITMAP)SelectObject(MemDC, bitmap_ball);
				TransparentBlt(LayDC, ball->pos_x, ball->pos_y,
					BALL_SIZE, BALL_SIZE,
					MemDC, ball_frame*BALL_SIZE, 0, BALL_SIZE, BALL_SIZE,
					RGB(255, 255, 255)); // ��ü ���� �׸���
				// ����� �����ϰ� ��������.
				SelectObject(MemDC, bitmap_old);
				ball = ball->next;
			}

			while (gball != NULL) {
				bitmap_old = (HBITMAP)SelectObject(MemDC, bitmap_gball);
				TransparentBlt(LayDC, gball->pos_x, gball->pos_y,
					BALL_SIZE, BALL_SIZE,
					MemDC, ball_frame*BALL_SIZE, 0, BALL_SIZE, BALL_SIZE,
					RGB(255, 255, 255)); // ��ü �ʷϰ��� �׸���
				// ����� �����ϰ� ��������.
				SelectObject(MemDC, bitmap_old);
				gball = gball->next;
			}

			Object* object = objecthead->next;
			while (object != NULL) { // ������Ʈ���� ������ �׸���
				switch (object->item_id) {
				case ITEM_NOTHING: // ���϶�

					block_color = 255 - object->hp * 10; // ü�¿� ���� �� ������ �ٲ��
					if (block_color < 0) {
						block_color = 0; // Į���� 0���� �۾����� 0���� ����
					}
					block_brush = (HBRUSH)CreateSolidBrush(RGB(255, block_color, block_color));
					brush_old = (HBRUSH)SelectObject(LayDC, block_brush);
					Rectangle(LayDC, object->rect.left, object->rect.top,
						object->rect.right, object->rect.bottom);
					if (object->item_id == ITEM_NOTHING) {
						wsprintf(temp, TEXT("%d"), object->hp);
						SetTextColor(LayDC, RGB(0, 255 - block_color, 255 - block_color));
						DrawText(LayDC, temp, -1, &object->rect,
							DT_SINGLELINE | DT_NOCLIP | DT_CENTER | DT_VCENTER); //ü���� ���ȿ� ǥ��
					}
					SelectObject(LayDC, brush_old);
					DeleteObject(block_brush);
					break;
				case ITEM_PLUS_BALL: // �� �߰� �������Ͻ�
					bitmap_old = (HBITMAP)SelectObject(MemDC, bitmap_item_plus);
					TransparentBlt(LayDC, object->rect.left, object->rect.top,
						ITEM_SIZE, ITEM_SIZE,
						MemDC, item_frame*ITEM_SIZE, 0, ITEM_SIZE, ITEM_SIZE,
						RGB(255, 255, 255)); // ������ ��������Ʈ�� �Ѹ���
					// ����� �����ϰ� ��������.
					SelectObject(MemDC, bitmap_old);

					break;
				case ITEM_CHANGE_BALL_DIR:
					bitmap_old = (HBITMAP)SelectObject(MemDC, bitmap_item_change_dir);
					TransparentBlt(LayDC, object->rect.left, object->rect.top,
						ITEM_SIZE, ITEM_SIZE,
						MemDC, item_frame*ITEM_SIZE, 0, ITEM_SIZE, ITEM_SIZE,
						RGB(255, 255, 255)); // ������ ��������Ʈ�� �Ѹ���
					// ����� �����ϰ� ��������.
					SelectObject(MemDC, bitmap_old);

					break;
				case ITEM_DEBUFF:
					bitmap_old = (HBITMAP)SelectObject(MemDC, bitmap_item_debuff);
					TransparentBlt(LayDC, object->rect.left, object->rect.top,
						ITEM_SIZE, ITEM_SIZE,
						MemDC, item_frame*ITEM_SIZE, 0, ITEM_SIZE, ITEM_SIZE,
						RGB(255, 255, 255)); // �𓹾����� ��������Ʈ�� �Ѹ���
					// ����� �����ϰ� ��������.
					SelectObject(MemDC, bitmap_old);

					break;
				}
				object = object->next;
			}

			DrawSight(LayDC); // ���ؼ��� �׸���

			pen_old = (HPEN)SelectObject(LayDC, pen_int_bar);
			Rectangle(LayDC, top_bar.left, top_bar.top, top_bar.right, top_bar.bottom); // ��ܹ� �׸���
			Rectangle(LayDC, bottom_bar.left, bottom_bar.top, bottom_bar.right, bottom_bar.bottom); // �ϴܹ� �׸���
			SelectObject(LayDC, pen_int_bar);

			wsprintf(temp, TEXT("STAGE : %d / SCORE : %d / %d���� �� �μ��� �ȴ�!"), next_hp,score,CLEAR_GAME-score);
			SetTextColor(LayDC, RGB(255, 0, 0));
			DrawText(LayDC, temp, -1, &top_bar,
				DT_SINGLELINE | DT_NOCLIP | DT_CENTER | DT_VCENTER); // ����� �ִ� �޼���

			if (num_ball != shooted_ball) {
				wsprintf(temp,TEXT("X%d"),num_ball-shooted_ball);
				TextOut(LayDC,startX,bottom_bar.top+30,temp,wcslen(temp));
			} // ���� ����� ǥ���Ѵ�

			if (game_phase == Phase::GAME_END) {
			
				if (win_or_lose == true) {
					wsprintf(temp, TEXT("�̰��! ������ ������ Ŭ���� �ߴٴ� ���밨�Դϴ�. Score : %d"), score);
					DrawText(LayDC, temp, -1, &m_rect,
						DT_SINGLELINE | DT_NOCLIP | DT_CENTER | DT_VCENTER);//���밨 ^^
				}
				if (win_or_lose == false) {
					wsprintf(temp, TEXT("�����ϴ�. Score : %d"), score);
					DrawText(LayDC, temp, -1, &m_rect,
						DT_SINGLELINE | DT_NOCLIP | DT_CENTER | DT_VCENTER);// ������ �޼���
				}
				
				Rectangle(LayDC, exit_button.left, exit_button.top
					, exit_button.right, exit_button.bottom);
				wsprintf(temp, TEXT("Back To Title"));
				DrawText(LayDC, temp, -1, &exit_button,
					DT_SINGLELINE | DT_NOCLIP | DT_CENTER | DT_VCENTER); // ������ ��ư�� �׸���
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
	bool movingcheck; // �����̰� �ִ°�?
	bool isdelete; // ����Ŭ�� ���������ֳ�
	bool iscollisioned; //�浹�߾��d��?
	bool damage_one_time; // �ѹ��� �ѹ��� �������� �ش�
	int dice; // Ȯ����� �ֻ���
	switch (id) {
////////<�ǽð� ������Ʈ>//////////////////////
	case TIMER_MENU::UPDATER:
		switch (game_phase) { // ���� ����� ���� �������Ϳ��� �ϴ� ������ �ٸ���.
		/////////////<������ ������>/////////////////
		case Phase::Create_Brick_Phase:
			is_collision = false;
			is_dir_changed = false;
			is_first_drop = true;
			is_shooting = false;
			isdebuffed_lowaim = false;
			shooted_ball = 0;
			/////<�� �߰�>//////////
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
			} // ���� ���� ������ŭ �� ��带 �߰������� �ڿ� �����Ѵ�
			get_ball = 0;

			////<������>///////
			next_num_brick = 4 + rand() % (BRICK_DEVIDE - 4);
			next_hp++;
			down_dist = 0;
			// �켱 �÷��׸� �ʱ�ȭ����

			CreateObject(1); // ���� ����� �Լ��� ȣ���Ѵ�

			game_phase = Phase::Calculating_Phase;
			break;
		/////////////////////////////////////////
		////////////////<�����ϴ� ������>////////////////////
		case Phase::Calculating_Phase:
			is_ball_collecting = false;
			is_brick_moving = false;
			//////////////<������Ʈ ������>////////////////////////////////////
			if (down_dist != mx_down_dist) { // �̷��� ���������ϴ� �Ÿ���ŭ�� ��������
				down_dist++;
				is_brick_moving = true;
				object = objecthead->next;
				while (object != NULL) {
					object->rect.top++;
					object->rect.bottom++;
					object = object->next;
				}
			} // ���� �� �� ������.
			isdelete = true;
			while (isdelete) { // ���� �����ִٸ� �ѹ� �� ������
				isdelete = false;
				object = objecthead;
				while (object->next != NULL) {
					if (object->next->item_id == ITEM_NOTHING && object->next->rect.bottom >= bottom_bar.top) {
						win_or_lose = false; // ���� ���� �ٴڿ� ��Ҵٸ� �� ������ false�� ����� ���ӿ��� �������
						game_phase = Phase::GAME_END;
						break;
					}
					if (object->next->item_id == ITEM_PLUS_BALL && object->next->rect.bottom >= bottom_bar.top-m_rect.right/GAME_BOARD_DEVIDE) {
					Object* temp = (Object*)malloc(sizeof(Object));
						get_ball++; // �� �߰� �������� �عٴڿ� �Դٸ� �ڵ����� ���� �Դ´�

						if (object->next->item_id == ITEM_PLUS_BALL) {
							CreateGball(object);
						}
						//�÷����������̶�� �÷��� ���� �ϳ� �����Ѵ�
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
			} // �� �߰�!
			get_ball = 0;
			/////////////////////////////////////////////////////
			//////<���� ������>/////////////////////
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
						double x2 = min(gball->pos_x, startX); // �ִ��ּҰ� ����
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
					double x2 = min(ball->pos_x, startX); // �ִ��ּҰ� ����
					if (x1 - x2 < 1) {
						ball->pos_x = startX;
						ball->pos_y = startY;
						ball->movtofirst = false;
					}
				}
				
				ball = ball->next;
			}

			if (is_ball_collecting == false && is_brick_moving == false) {
				getballhead->next = NULL; // ������ �� �ϴ� ��������
				game_phase = Phase::Aiming_Phase;
			}
			break;
		//////////////////////////////////////////



		}
		
		break;
////////////////////////////////////////////////
	case TIMER_MENU::SHOOTING: // ���� �߻��Ѵ�

		if (shooted_ball == num_ball) {
			KillTimer(m_hwnd,TIMER_MENU::SHOOTING);
		}
		ball = ballhead->next;

		for (int i = 0; i < shooted_ball; ++i) {
			ball = ball->next;
		}
		if (ball != NULL) {
			is_shooting = true; // �����÷��׸� �Ҵ�
			ball->x_vec = x_vk; // ������ �����ϸ鼭 ���Ѱɷ�
			ball->y_vec = -1; // ������ ����
			ball->angle = angle;
			if (isdebuffed_lowaim == true) {
				ball->angle = angle - 5 * 3.14 / 180 + rand() % 10 * 3.14 / 180;
			} // ������� �ɸ����¶�� �����ѰŸ��� ���� ��ѷ�����
			ball->distance = 5.0; // �⺻�ӵ��� 5
			ball->shooted = true;
			shooted_ball++;
		}
		
		break;

	case TIMER_MENU::MOV_BALL:
		movingcheck = false; // �̰� movephase���� false�� �����Ǹ� createphase�� �Ѿ��
		double dist16; // ������ �浹 Ȯ���� ���� �̵��Ÿ��� 16����Ѵ�
		ball = ballhead->next;
		while (ball != NULL) {
			dist16 = ball->distance / 16;
			damage_one_time = true;
			for (int i = 0; i < 16; ++i) {
				if (ball->shooted == true) {
					movingcheck = true;
					///////////<�浹�� ��ǥ�� �����Ѵ�>////////////
					double mx = cos(ball->angle)*dist16*ball->x_vec;
					double my = sin(ball->angle)*dist16*ball->y_vec;
					ball->pos_x += mx;
					ball->pos_y += my;


					////////////�浹 �n ///////////////////////////////////////////////////
					RECT collball = { ball->pos_x, ball->pos_y, // �浹 üũ ��
						ball->pos_x + BALL_SIZE , ball->pos_y + BALL_SIZE };
					 /////////////////////////////////////////////////////////
					int p_c_check; // �𼭸��� �΋H������ �浹üũ�� ����
					Object* obj = objecthead->next; // ������Ʈ�� �浹 Ȯ��
					while (obj != NULL) {
						switch (obj->item_id) {
					///////////////////<������ �浹üũ>////////////////////////////////
						case ITEM_NOTHING:
							if (IntersectRect(&for_col_check, &obj->rect, &collball) == true) {
								is_collision = true; // �浹����ġ�� �� �Ѵ�
								iscollisioned = false; //�浹�߾��d��?
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
										} // ��
										else if (ball->x_vec == 1 && ball->y_vec == -1) {
											ball->y_vec *= -1;
											ball->pos_y += sin(ball->angle)*ball->distance*ball->y_vec;
										} // ��
										else if (ball->x_vec == 1 && ball->y_vec == 1) {
											ball->x_vec *= -1;
											ball->pos_x += cos(ball->angle)*ball->distance*ball->x_vec;
										} // ��
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
										} // ��
										else if (ball->x_vec == 1 && ball->y_vec == -1) {
											ball->x_vec *= -1;
											ball->y_vec *= -1;
											ball->pos_x += cos(ball->angle)*ball->distance*ball->x_vec;
											ball->pos_y += sin(ball->angle)*ball->distance*ball->y_vec;
										} // ��
										else if (ball->x_vec == -1 && ball->y_vec == -1) {
											ball->y_vec *= -1;
											ball->pos_y += sin(ball->angle)*ball->distance*ball->y_vec;
										} // ��
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
										} // ��
										else if (ball->x_vec == -1 && ball->y_vec == 1) {
											ball->x_vec *= -1;
											ball->y_vec *= -1;
											ball->pos_x += cos(ball->angle)*ball->distance*ball->x_vec;
											ball->pos_y += sin(ball->angle)*ball->distance*ball->y_vec;
										} // ��
										else if (ball->x_vec == -1 && ball->y_vec == -1) {
											ball->x_vec *= -1;
											ball->pos_x += cos(ball->angle)*ball->distance*ball->x_vec;
										} // ��
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
										} // ��
										else if (ball->x_vec == -1 && ball->y_vec == -1) {
											ball->x_vec *= -1;
											ball->y_vec *= -1;
											ball->pos_x += cos(ball->angle)*ball->distance*ball->x_vec;
											ball->pos_y += sin(ball->angle)*ball->distance*ball->y_vec;
										} // ��
										else if (ball->x_vec == -1 && ball->y_vec == 1) {
											ball->x_vec *= -1;
											ball->pos_x += cos(ball->angle)*ball->distance*ball->x_vec;
										} // ��
										break;
									}
									break;
								}
								if (iscollisioned == true) {
									if (damage_one_time == true) {
										damage_one_time = false;
										obj->hp--; // ���� HP�� 1 ���δ�.
									}
								}
								

							}
						
							break;
					///////////////<������ �浹 üũ>/////////////////////////////
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

					/////////////������ �浹////////////////////////////////
					if (IntersectRect(&for_col_check, &top_bar, &collball) == true) {
						ball->y_vec *= -1;
						ball->pos_y = top_bar.bottom;
					}// ���ʿ� �ε�����
					 ////////////////////////////////////////
					if (IntersectRect(&for_col_check, &bottom_bar, &collball) == true) {
						ball->y_vec *= -1;
						ball->pos_y = bottom_bar.top - BALL_SIZE;
						if (is_first_drop) { // ó�� ������ ���̶��
							startX = ball->pos_x;
							startY = ball->pos_y; // �̰��� ���� ���������� �����
							is_first_drop = false;
						}
						ball->movtofirst = true;
						ball->shooted = false; // �۵��� ������Ų��
						if (is_collision == false && isdebuffed_lowaim == false && is_dir_changed == false) { // ���� �ѹ��� �浹���� ���ٸ�?, ������� �ȹ޾Ҵٸ�
							KillTimer(m_hwnd, TIMER_MENU::SHOOTING); 
							game_phase = Phase::Create_Brick_Phase; // ������ ������� �ѱ��
							break;
						}
					}// �Ʒ��ʿ� �ε�����
					if (ball->pos_x < 0) {
						ball->x_vec *= -1;
						ball->pos_x = 0;
					} // ���ʿ� �΋H����
					if (m_rect.right < ball->pos_x + BALL_SIZE) {
						ball->x_vec *= -1;
						ball->pos_x = m_rect.right - BALL_SIZE;
					} //�����ʿ� �ε�����
////////////////////////////////////�浹 ���//////////////////////////////////////////////
				}
			} // 16����Ͽ� �����ϰ� ����
			ball = ball->next;
		}

		gball = getballhead->next; // ���� ���� �ϴ����� ������
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



		////////////hp�� 0�� �� ������ ��.��.��.�� /////////////////
		isdelete = true;
		while (isdelete) {
			isdelete = false;
			object = objecthead;
			while (object->next != NULL) {
				if (object->next->hp <= 0) {
					Object* temp = (Object*)malloc(sizeof(Object));

					
					if (object->next->item_id == ITEM_PLUS_BALL) {
						CreateGball(object); // �ʷϰ� �����Լ�
					}
					//���� �������� ������Ʈ�� �÷����������̶�� �÷��� ���� �ϳ� �����Ѵ�
					if (object->next->item_id == ITEM_NOTHING) {
						score++;
					} // ���̶�� ���� ++

					temp = object->next;
					object->next = temp->next;
					free(temp);
					isdelete = true;
					break;
				}
				object = object->next;
			}
		}
		
		if (score == CLEAR_GAME) { // Ŭ���� ������ �����ߴٸ�
			win_or_lose = true; // �̰�ٷ� ��ȯ
			game_phase = Phase::GAME_END; // ���ӿ��� ������� �Ѿ��
		}

		/////////<�߻�ǰ� �ִ� �� �ִ��� Ȯ��>/////////////////////////////////////////////
		if (game_phase == Phase::Shoot_Phase && is_shooting == true) {
			if (movingcheck == false) {
				ball = ballhead->next;
				while (ball != NULL) {
					ball->movtofirst = true; // ��� ���� �� ȸ�� ���·� �ѱ��
					ball = ball->next;
				}
				is_shooting = false; // �� ����ִ��� ���θ� false�� �����
				game_phase = Phase::Create_Brick_Phase; // �� ���� ������� �Ѿ��
			}
		}
		break;

/////////////<�ִϸ��̼�>////////////////////////////////
		case TIMER_MENU::ANIMATION:
			mainframe++; // ���� �������� ��� ++
			item_frame = mainframe % 6; // ������ ������
			ball_frame = mainframe % 11; // �� ������
			title_frame = mainframe % 7; // Ÿ��Ʋ�޴� ������
			start_button = { 250,350 + (LONG)title_frame,500,400 + (LONG)title_frame }; // ���۹�ư
			exit_button = { 250,450 + (LONG)title_frame,500,500 + (LONG)title_frame }; // ������ ��ư
			break;
/////////////////////////////////////////
	}

	InvalidateRect(m_hwnd, &m_rect, FALSE);
}
void CFrameWork::Resize() {
	GetClientRect(m_hwnd, &m_rect);
	InvalidateRect(m_hwnd, &m_rect, FALSE);
} // Ȥ�� ����



void CFrameWork::InputMouse(UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_LBUTTONDOWN:
		POINT mouse; // ���콺����Ʈ
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
			bool issightend = false; // ���ؼ��� ���� ��ҳ�?
			ptmouse.x = LOWORD(lParam);
			ptmouse.y = HIWORD(lParam);
			// �� ���� ���� ������ �̾� ���ؼ��� �����غ���
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
			if (atan2(height, width) < 15.0*3.14/180) { // 15������ ���ٸ�
				ptmouse.y = ball->pos_y + BALL_SIZE / 2 - 60;
			}
					
				y1 = max(ptmouse.y, ball->pos_y + BALL_SIZE / 2);
				y2 = min(ptmouse.y, ball->pos_y + BALL_SIZE / 2);

				ptend_x = ball->pos_x + BALL_SIZE / 2;
				ptend_y = ball->pos_y + BALL_SIZE / 2;

				height = y1 - y2;

				double temp_angle = atan2(height, width); // ��ź��Ʈ�� �̿� ������ ���Ѵ�

				int temp_vec = 1;
				if (ptmouse.x < ball->pos_x + BALL_SIZE / 2)
					temp_vec = -1;

				while (0 < ptend_x && ptend_x < m_rect.right
					&& 0 < ptend_y && ptend_y < m_rect.bottom) {
					ptend_x += cos(temp_angle) * 1.0 * temp_vec;
					ptend_y -= sin(temp_angle) * 1.0; // ������ ��θ� ���� �̵���Ű��

					POINT pt = { ptend_x,ptend_y };

					Object* object = objecthead->next;
					while (object != NULL) {
						if (PtInRect(&object->rect, pt)) {
							if (object->exist == true && object->item_id == ITEM_NOTHING) {
								issightend = true; // �����������Ͱ� ���� �ٴٶ���
							}
						}
						object = object->next;
					}
					if (issightend == true) // ���� �ٴٶ����� ����
						break;
				}
		}
		break;
	case WM_LBUTTONUP:
		
		if (game_phase == Phase::Aiming_Phase && drag == true) { //���� ��������� �巡�װ� ���ֵ���
			drag = false; // �巡�׸� ���ְ�
			Ball* ball = ballhead->next;
			double x1 = max(ptmouse.x, ball->pos_x + BALL_SIZE / 2);
			double y1 = max(ptmouse.y, ball->pos_y + BALL_SIZE / 2);
			double x2 = min(ptmouse.x, ball->pos_x + BALL_SIZE / 2);
			double y2 = min(ptmouse.y, ball->pos_y + BALL_SIZE / 2);
			double height = y1 - y2; //���콺�� �� ������ ���̿�
			double width = x1 - x2;// �ʺ� ���Ѵ�

			if (ball->pos_x + BALL_SIZE / 2 < ptmouse.x)
				x_vk = 1; // ���콺���� ���� ���ʿ� ������
			else
				x_vk = -1; // ���콺���� ���� �����ʿ� ������

				angle = atan2(height, width); //��ź��Ʈ�� �����ݿ��Ѵ�

			shooted_ball = 0;

			SetTimer(m_hwnd,TIMER_MENU::SHOOTING,80,NULL);
			game_phase = Phase::Shoot_Phase; // ����������� �Ѿ��
		}

	}
	InvalidateRect(m_hwnd, &m_rect, FALSE);
}
void CFrameWork::InputKeyBoard(UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_KEYDOWN:
		break;
	}
	InvalidateRect(m_hwnd, &m_rect, FALSE); // Ű �Է��� ���µ� Ȥ�� �𸣴� �־�Ҵ�
}
void CFrameWork::CreateBkBrush(COLORREF color) {
	if (hbrBackground) DeleteObject(hbrBackground);
	hbrBackground = (HBRUSH)CreateSolidBrush(color);
}
void CFrameWork::ClearScreen(HDC hdc) {
	FillRect(hdc, &m_rect, hbrBackground);
}
void CFrameWork::DrawSight(HDC hdc) {
	///////////<���ؼ� �׸���>////////////////////////////////////////
	if (drag == true) {
		pen_old = (HPEN)SelectObject(hdc, pen_sight);

		Ball* ball = ballhead->next;
		MoveToEx(hdc, ball->pos_x + BALL_SIZE / 2
			, ball->pos_y + BALL_SIZE / 2, NULL);
		LineTo(hdc, ptend_x, ptend_y); // ������ ���� �ߴ´�

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
///////<���� �����>
void CFrameWork::CreateObject(int pos) {

	Object* object;
	int created_brick;
	int created_plusitem;
	int dice; // �ֻ���

	for (int i = 0; i < BRICK_DEVIDE; ++i) {
		set_brick[i] = { { 0,0,0,0 },0,false,ITEM_NOTHING, NULL }; // �ʱ�ȭ�Ѵ�
	}
	created_brick = 0;
	while (created_brick != next_num_brick) {
		int i = rand() % BRICK_DEVIDE; // ��ġ�� ���� ��������
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
		int i = rand() % BRICK_DEVIDE; // ��ġ�� ���� ��������
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
		int i = rand() % BRICK_DEVIDE; // ��ġ�� ���� ��������
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
			int i = rand() % BRICK_DEVIDE; // ��ġ�� ���� ��������
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
		if (set_brick[i].exist == true) { // ���� ������Ʈ�� �����Ǿ��ٸ�?
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
void CFrameWork::CreateGball(Object* object) { // �ʷϻ� ���� �����Ѵ�
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
