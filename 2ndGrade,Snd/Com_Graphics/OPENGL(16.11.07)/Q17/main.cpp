#include<iostream>
#include<gl/glut.h>
#include<ctime>
#include"Vec3D.h"

using namespace std;

enum Type {
	Cube = 0, Sphere, Cone, Teapot
};

enum Handle {
	Middle,Hand,Finger
};

constexpr int Window_Width = 800;
constexpr int Window_Height = 800;

constexpr float axis_size = 50.0;
constexpr float floor_size = 120.0;
constexpr int Rotate_Speed = 2;
constexpr float PI = 3.141592;

class Crane {
private:
	Vec3f m_pt;

	Vec3f m_mid_angle{};
	Vec3f m_hand_angle{};
	Vec3f m_finger_angle{};

	int dir = 1;
	int speed = 1;
	int base_angle{};
	float m_size = 50;
public:
	void Rander() {

		glPushMatrix();
		glTranslatef(m_pt.x, m_pt.y, m_pt.z);
		glRotatef(base_angle, 0, 1, 0);
		glColor3f(1.0, 0, 0);
		DrawCube(m_size, 1, true); // base;


		glTranslatef(0, m_size / 2, 0);

		glRotatef(m_mid_angle.x, 1, 0, 0);
		glRotatef(m_mid_angle.y, 0, 1, 0);



		glColor3f(0.0, 1.0, 0);
		DrawCube(m_size / 2, 1, true); // arm

		glTranslatef(m_size / 2, 0, 0);

		glRotatef(m_hand_angle.x, 1, 0, 0);
		glRotatef(m_hand_angle.z, 0, 0, 1);

		glColor3f(0.0, 0.0, 1.0);
		DrawCube(m_size / 4, 6, false); // hand

		glTranslatef(m_size*1.5, 0, 0);

		glRotatef(m_finger_angle.x, 1, 0, 0);
		glRotatef(m_finger_angle.z, 0, 0, 1);

		glColor3f(0.0, 0.5, 1.0);
		DrawCube(m_size / 5, 4, false); // hand

		glPopMatrix();
	}

	void Update() {

		m_pt.x += dir*speed;

		if (m_pt.x < -floor_size)
		{
			dir *= -1;
			m_pt.x = -floor_size;
		}
		if (m_pt.x > floor_size)
		{
			dir *= -1;
			m_pt.x = floor_size;
		}

	}

	void DrawCube(float size, int length, bool isbase) {

		glPushMatrix();

		if (isbase)glTranslatef(-size / 2, 0, 0);
		//if(!isbase)glTranslatef(size/2, 0, 0);
		glutSolidCube(size);
		for (int i = 0; i < length; ++i)
		{
			glTranslatef(size, 0, 0);
			glutSolidCube(size);
		}
		glPopMatrix();

	}

	void RotateBase(int x) {
		base_angle += x;
	}

	void Handle(int dir, Vec3f axis, int handle) {

		switch (handle) {
		case Handle::Middle:
			m_mid_angle += axis*dir;
			break;
		case Handle::Hand:
			m_hand_angle += axis*dir;
			break;
		case Handle::Finger:
			m_finger_angle += axis*dir;
			break;
		}
	}

	void Init() {
		Vec3f m_mid_angle = {0,0,0};
		Vec3f m_hand_angle = { 0,0,0 };
	}

};



///////////////<전역>//////////////////////////

/////////////////////////////////////////////

//////////////<기본 함수>//////////////////////////
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void SpecialInput(int key, int x, int y);
void Mouse(int button, int state, int x, int y);
void TimerFunction(int value);
//////////////////////////////////////////////////
void InitObjects();

void DrawAxis();
void DrawFloor();

void DrawTriangle(Vec3f Position, Vec3f Size, int angle, Vec3f axis);
void DrawRactangle(Vec3f Position, Vec3f Size, int angle, Vec3f axis);
///////////////////////////////////////////
int x_angle = 0;
int y_angle = 0;
int z_angle = 0;
////////////////////////////////////////////
Crane crane;





void main(int argc, char *argv[])
{
	//초기화 함수들
	InitObjects();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(Window_Width, Window_Height); // 윈도우의 크기 지정
	glutCreateWindow("[2013182010김병진]Q17"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutKeyboardFunc(Keyboard); // 키보드 입력 콜백 함수
	glutTimerFunc(1, TimerFunction, 1);
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정
	glutMainLoop();


}
// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기
														// 색상 지정하고 사각형 그리기
	glEnable(GL_DEPTH_TEST);

	glColor4f(1.0, 1.0, 1.0, 1.0f);

	glPushMatrix();
	{
		

		glRotatef(x_angle, 1, 0, 0);
		glRotatef(y_angle, 0, 1, 0);
		glRotatef(z_angle, 0, 0, 1);
		//
		glTranslatef(0, -100, 0);
		DrawAxis();

		//////////////////<바닥>////////////////////
		DrawFloor();

		glColor4f(1.0, 1.0, 1.0, 1.0);
		glutWireCube(floor_size * 2);

		crane.Rander();

	}
	glPopMatrix();









	glutSwapBuffers(); // 화면에 출력하기 (glflush효과가 있다.)
}
GLvoid Reshape(int w, int h)
{

	//////<뷰포트 변환 설정>////////
	glViewport(0, 0, w, h);


	/////<투영 행렬스택 재설정>//////
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	///////////<원근투영>////////////////////////
	gluPerspective(60.0f, w / h, 1.0, 1000.0); // fovy :: 최대 180(넘어가면 거꾸로 보여), 작을수록 크게 보임
											   //glTranslatef(0.0, 0.0, -300.0);

											   //glOrtho(-400.0, 400, -400.0, 400, -400.0, 400.0); // x축 최소,최대, y축 최소,최대, z축 최소 최대 // 직각투영




	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	// 관측 변환: 카메라의 위치 설정 (필요한 경우, 다른 곳에 설정 가능)
	gluLookAt(0.0, 0.0, -300,		0.0, 0.0, -1.0, /* z값의 크기는 딱히 상관 X */		0.0, 1.0, 0.0);

}

void Keyboard(unsigned char key, int x, int y)
{
	{
		if (key == 'e') {
			crane.Handle(1, { 1,0,0 }, Handle::Finger);
		}
		if (key == 'E') {
			crane.Handle(-1, { 1,0,0 }, Handle::Finger);
		}
		if (key == 'r') {
			crane.Handle(1, { 0,0,1 }, Handle::Finger);
		}
		if (key == 'R') {
			crane.Handle(-1, { 0,0,1 }, Handle::Finger);
		}
		if (key == 'q') {
			crane.Handle(1, {1,0,0},Handle::Hand);
		}
		if (key == 'Q') {
			crane.Handle(-1, { 1,0,0 }, Handle::Hand);
		}
		if (key == 'w') {
			crane.Handle(1, { 0,0,1 }, Handle::Hand);
		}
		if (key == 'W') {
			crane.Handle(-1, { 0,0,1 }, Handle::Hand);
		}
		if (key == 'a') {
			crane.Handle(1, { 1,0,0 }, Handle::Middle);
		}
		if (key == 'A') {
			crane.Handle(-1, { 1,0,0 }, Handle::Middle);
		}
		if (key == 's') {
			crane.Handle(1, { 0,1,0 }, Handle::Middle);
		}
		if (key == 'S') {
			crane.Handle(-1, { 0,1,0 }, Handle::Middle);
		}
		if (key == 'z') {
			crane.RotateBase(-5);
		}
		if (key == 'Z') {
			crane.RotateBase(5);
		}
		if (key == 'i' || key == 'I') {
			crane.Init();
		}
	}



	if (key == 'p' || key == 'P') {
		exit(0);
	}	// 종료
}

void Mouse(int button, int state, int x, int y)
{

}

void TimerFunction(int value)
{
	crane.Update();
	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(1, TimerFunction, 1); // 타이머함수 재 설정
}

void InitObjects()
{
	srand((unsigned)time(nullptr));

	/*
	Vec3f pt = {-100.0f,(float)(-floor_size+shape_size),20.0f};

	Shape solid = Shape(pt,Type::Cube, shape_size, false);

	pt = { 100.0f,(float)(-floor_size + shape_size),20.0f };
	Shape wire = Shape(pt,Type::Cube, shape_size, true);
	*/


}

void DrawAxis()
{
	/////////////<좌표계 그림>//////////////////
	{
		glBegin(GL_LINES);

		/////////////////<x축>///////////////////
		glColor4f(1.0, 0.0, 0.0, 1.0);
		glVertex3f(-axis_size, 0.0, 0.0);
		glVertex3f(axis_size, 0.0, 0.0);
		/////////////////<x축>///////////////////
		glColor4f(0.0, 1.0, 0.0, 1.0);
		glVertex3f(0.0, -axis_size, 0.0);
		glVertex3f(0.0, axis_size, 0.0);
		/////////////////<x축>///////////////////
		glColor4f(0.0, 0.0, 1.0, 1.0);
		glVertex3f(0.0, 0.0, axis_size);
		glVertex3f(0.0, 0.0, -axis_size);


		glEnd();
	}
}

void DrawFloor()
{
	{
		glColor4f(0.2, 0.5, 0.2, 0.7f);
		glBegin(GL_POLYGON);

		glVertex3f(floor_size, -1, -floor_size);
		glVertex3f(-floor_size,-1, -floor_size);
		glVertex3f(-floor_size,-1, floor_size);
		glVertex3f(floor_size, -1, floor_size);

		glVertex3f(floor_size, - 2, -floor_size);
		glVertex3f(-floor_size, - 2, -floor_size);
		glVertex3f(-floor_size, - 2, floor_size);
		glVertex3f(floor_size, - 2, floor_size);

		glEnd();
	}
}

void DrawTriangle(Vec3f Position, Vec3f Size, int angle, Vec3f axis)
{
	glPushMatrix();

	glTranslatef(Position.x, Position.y, Position.z);
	glRotatef(angle, axis.x, axis.y, axis.z);

	glBegin(GL_LINE_LOOP);
	glVertex3f((Size.x) / 2, -Size.y / 2, Size.z);
	glVertex3f(-Size.x / 2, -Size.y / 2, Size.z);
	glVertex3f(0.0, Size.y / 2, Size.z);
	glEnd();


	glPopMatrix();

}

void DrawRactangle(Vec3f Position, Vec3f Size, int angle, Vec3f axis)
{
	glPushMatrix();

	glTranslatef(Position.x, Position.y, Position.z);
	glRotatef(angle, axis.x, axis.y, axis.z);

	glBegin(GL_LINE_LOOP);
	glVertex3f((Size.x) / 2, Size.y / 2, Size.z);
	glVertex3f(-Size.x / 2, Size.y / 2, Size.z);
	glVertex3f(-Size.x / 2, -Size.y / 2, Size.z);
	glVertex3f((Size.x) / 2, -Size.y / 2, Size.z);
	glEnd();


	glPopMatrix();

}
