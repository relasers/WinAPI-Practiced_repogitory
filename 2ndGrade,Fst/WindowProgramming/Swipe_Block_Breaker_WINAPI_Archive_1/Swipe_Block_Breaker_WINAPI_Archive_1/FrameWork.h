#pragma once
class CFrameWork
{
private:

	typedef struct Object{
		RECT rect; // ������Ʈ ��ġ
		
		int hp; // ������Ʈ ü��

		bool exist; // ������Ʈ�� �����ϴ°�

		int item_id; // ������Ʈ ���̵� / ��,+������,������ȯ������,�����������
		Object* next;
	}Object;

	typedef struct Ball{
		double pos_x; // ���� x��ġ
		double pos_y; // ���� y��ġ

		double x_vec; // ���� �¿� �̵�����
		double y_vec; // ���� ���� �̵�����
		double distance; // �������Ӵ� ���� �̵� �Ÿ�
		double angle; // ���� ����
		bool shooted; // �����̰� �ִ���
		bool movtofirst; // ������������ ��
		Ball* next;
	}Ball;

	typedef struct Get_Ball {
		double pos_x; // ���� x��ġ
		double pos_y; // ���� y��ġ
		double distance; // �������Ӵ� ���� �̵� �Ÿ�
		bool shooted; // �����̰� �ִ���
		bool movtofirst; // ������������ ��
		Get_Ball* next;
	}Get_Ball; // ���� ��



	//////////////////////////<�׷��� ������>////////////////////
	PAINTSTRUCT ps;
	HDC hdc,MemDC; // �׻� ù��° ���ڴ� hDC ��! , �ι�°�� ��Ʈ�ʿ�
	
	
	HBRUSH brush_old;
	HPEN pen_old;
	HBITMAP bitmap_old;

	HPEN pen_int_bar; // ���ϴܸ���
	HPEN pen_sight; // ���ؼ�

	HBITMAP bitmap_subtitle; // ����
	HBITMAP bitmap_title; // Ÿ��Ʋ ȭ��
	HBITMAP bitmap_background; //���ȭ��
	HBITMAP bitmap_item_plus; // �÷��������� ��Ʈ��
	HBITMAP bitmap_item_change_dir; //������ȯ ������ ��Ʈ��
	HBITMAP bitmap_item_debuff; // ���ؿ� ���ڰ� ����� ������
	HBITMAP bitmap_ball; // �� ��Ʈ��
	HBITMAP bitmap_gball; // ������ ��Ʈ��
	wchar_t temp[50]; // ���ڿ� ��� �ӽ� �迭

	unsigned int mainframe; // ����������
	unsigned int title_frame; // Ÿ��Ʋȭ�� ������
	unsigned int item_frame; // ������ �ִϸ��̼ǿ�
	unsigned int ball_frame; // �� ������
	//////////////////////////////////////////////////


	///////////////////////////////////////////////////

	HWND m_hwnd; // ������ �ڵ�
	RECT m_rect; // rect ����ü
	HINSTANCE m_hinst;
	HBRUSH hbrBackground = NULL; // ���귯���ڵ�

	POINT ptmouse; // ���콺 ��ġ ��ǥ
	POINT ptstart; //���ؼ��� ��������

	double ptend_x; // ���ؼ� �� ����
	double ptend_y;


	RECT for_col_check; // �浹�˻�� 
	
//////<�������̽�>///////////////////////////
	RECT top_bar; // ��� ��
	RECT bottom_bar; // �ϴ� ��

	RECT start_button; // ���۹�ư
	RECT exit_button; // ������ ��ư
///////////////////////////////////////

	bool drag; // ���콺 ����Ű ������ �ִ���
	bool is_shooting; // ���� ��� �ִ� ������?
	bool is_collision; // ���� �浹 �߾�����?
	bool is_dir_changed; // �����۸Ծ ������ �ٲ������?
	bool win_or_lose; // �¸��� �й��?
	// 400���� ä��� �¸� , �ٴڿ� ���� �������� �й�
	bool is_brick_moving; // �� �����̴���?
	double mx_down_dist; //������Ʈ ������ �Ÿ� 
	double down_dist; // ������Ʈ�� ������ �Ÿ�

	bool is_ball_collecting; // ���� ȸ���Ϸ��ߴ���?
	bool is_first_drop; //ù��° ������ ������?

	int game_phase; // ���� ����
	bool isdebuffed_lowaim; // ������ ��鸮�� ������� �ɷȴ���
	int score;

	int coll_check; // �浹üũ��
							  //�����ڵ带 ����� ���� char ��� wchar_t �� ���� ���ڿ� �տ� L�� ���δ�
	int next_hp; // ���� ���� �� HP
	int next_num_brick;
	int next_num_plus_item;
	Object set_brick[BRICK_DEVIDE];

	int get_ball; // �̹��Ͽ� ���� ���� ��
	int num_ball; //���� ������ ��
	int shooted_ball; // ���ݱ��� � ������?

	double startX; // �߻�����X
	double startY; // �߻�����Y


	////////////////////////////<������>///////
	Ball* ballhead; // ���������� �Ӹ�
	Get_Ball* getballhead; // �������������� �Ӹ�
	Object* objecthead; //������Ʈ�������� �Ӹ�
	/////////////////////<���� ���� �ʱⰪ>/////////
	double x_vk; // ����
	double angle; // ����
	////////////////////////////////////////////
	
public:

	//////////////�浹����ϱ�/////////////////////////
	float LengthPts(double x1, double y1, double x2, double y2);
	// �� ���� ���� ���
	BOOL InCircle(double x, double y, double rad, double px, double py);
	// ���� �� ���
	int Collision_Rec_Ell(double c_x, double c_y, double c_rad, RECT rec_check);
	//���� �簢�� �浹��� (������ , ������ , �浹�� ������Ʈ ũ�� ���)
	int Collision_point_check(double c_x, double c_y, double b_x, double b_y);
	//�𼭸� �浹�� �浹��� (������, �浹 ������Ʈ ��)



	///////////////////////////////////////////////////
	bool Initial(HWND, RECT, HINSTANCE);
	void Destroy(); // posquit,destroywindow(hWnd)������ �ȵ�
	void OnCreate();
	void OnDraw(HDC);
	void OnTimer(UINT); // ������Ʈ
	void Resize();
	void InputMouse(UINT, WPARAM, LPARAM); //�޼���,w�Ķ�,l�Ķ�
	void InputKeyBoard(UINT, WPARAM, LPARAM); //�޼���,w�Ķ�,l�Ķ�
	/////////<���� �Լ�>//////////////////////
	void CreateObject(int); // ������Ʈ�� �����Ѵ� , ���ڴ� ������ġ
	void CreateGball(Object* );
	/////////<�׷��� �Լ�>/////////////////
	void CreateBkBrush(COLORREF);
	void ClearScreen(HDC);
	void DrawSight(HDC); // ���ؼ��� �׸���
	///////////////////////////////////
	LRESULT WindowMessage(HWND, UINT, WPARAM, LPARAM);//�޼���,w�Ķ�,l�Ķ�
	CFrameWork();
	~CFrameWork();
};
