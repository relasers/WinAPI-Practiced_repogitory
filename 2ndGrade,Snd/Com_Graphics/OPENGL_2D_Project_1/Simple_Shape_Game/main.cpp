#include"stdafx.h"

using namespace std;

//////////////<기본 함수>//////////////////////////
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void TimerFunction(int value);
//////////////////////////////////////////////////
void InitObjects();
///////////////<객체들>//////////////////////////

int tick = 0;
int notespeed = 1;
CLine line[Number_Line];
CScore score;
CShape mainshape;
list <CNote> note;

/////////////////////////////////////////////

void main(int argc, char *argv[])
{
	//초기화 함수들
	InitObjects();
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(Window_Width, Window_Height); // 윈도우의 크기 지정
	glutCreateWindow("[2013182010김병진]PROJECT_1"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutKeyboardFunc(Keyboard); // 키보드 입력 콜백 함수
	glutTimerFunc(10, TimerFunction, 1);
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정
	glutMainLoop();


}
// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기
								  // 색상 지정하고 사각형 그리기
	for (int i = 0; i < Number_Line; ++i) {
		line[i].draw();
	}
	

	for (auto &p : note)
	{
		p.Draw();
	}
	mainshape.Draw();
	score.Draw();




	glFlush(); // 화면에 출력하기
}
GLvoid Reshape(int w, int h)
{
	glutReshapeWindow(Window_Width, Window_Height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, Window_Width, 0.0, Window_Height, -1.0, 1.0);
	glViewport(0, 0, Window_Width, Window_Height);
}

void Keyboard(unsigned char key, int x, int y)
{
	/////////////////<반사>/////////////////////////
	if (key == 'q')
	{
		mainshape.Reflect(Direction::Left);
	}
	if (key == 'e')
	{
		mainshape.Reflect(Direction::Plus);
	}
	/////////////////<좌우이동>/////////////////////////
	if (key == 'a')
	{
		mainshape.InputKeyBoard(Direction::Left);
	}
	if (key == 'd')
	{
		mainshape.InputKeyBoard(Direction::Right);
	}
	/////////////////<확대 축소>/////////////////////////
	if (key == 'w')
	{
		mainshape.InputKeyBoard(Direction::Plus);
	}
	if (key == 's')
	{
		mainshape.InputKeyBoard(Direction::Minus);
	}
	////////////////////<메인도형 모양변경>//////////////////////////////////
	if (key == 'j')
	{
		mainshape.Reshape(3);
	}
	if (key == 'i')
	{
		mainshape.Reshape(4);
	}
	if (key == 'o')
	{
		mainshape.Reshape(5);
	}
	if (key == 'p')
	{
		mainshape.Reshape(6);
	}
	/////////////////<도형 생성>/////////////////////////////////////////////
	if (key == 'x')
	{
		int moveval = Window_Width / (Number_Line + 1);
		POINT temp = { (moveval / 2) + rand() % 5 * moveval,Window_Height };
		note.push_front(
			CNote(temp, 3 + rand() % 4,notespeed)
		);
	}
}

void Mouse(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		POINT temp{ x,Window_Height - y };


	}// 왼클릭 :: 사각형 생성

}

void TimerFunction(int value)
{
	(++tick)%= 10000;

	if (tick % 100 == 0) {
		int moveval = Window_Width / (Number_Line + 1);
		POINT temp = { (moveval / 2)+rand()%5*moveval,Window_Height };
		note.push_front(
			CNote(temp,3+rand()%4,notespeed)
			);
	}

	if (tick % 1000 == 0) {
		notespeed = 1+rand()%3;
		for (auto &p : note)
		{
			p.SpeedChange(notespeed);
		}
	}



	mainshape.Update();
	for (auto &p : note)
	{
		p.Update();
	}


	for (auto &p : note)
	{
		p.Update();
		if(p.Check(mainshape.GetPoint(),mainshape.GetSize(), mainshape.GetNVertex()))
			score.GainScore();
	}

	if (score.GetScore() > MaxScore) {
		InitObjects();
	}

	note.remove_if([](auto& data) -> bool {
		return (data.IsOut());
	});
	
	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(10, TimerFunction, 1); // 타이머함수 재 설정
}

void InitObjects()
{
	srand((unsigned)time(nullptr));
	glOrtho(0.0, Window_Width, 0.0, Window_Height, -1.0, 1.0);
	for (int i = 0; i < Number_Line; ++i) {
		line[i] = CLine(
			i,
			Number_Line,
			Window_Width, 
			Window_Height);
	}
	note.clear();
	score = CScore();
	POINT temp = { 50,50 };
	mainshape = CShape(temp,5);

}
