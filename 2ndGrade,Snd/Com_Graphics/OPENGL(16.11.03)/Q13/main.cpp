#include<iostream>
#include<gl/glut.h>
#include<deque>
#include<Windows.h>
#include<chrono>
#include<cmath>
#include"Vec3D.h"
using namespace std;

constexpr int Window_Width = 800;
constexpr int Window_Height = 800;
constexpr int Base_Size = 400;
constexpr int Small_Size = 100;
constexpr int Speed = 1;
constexpr float PI = 3.141592;

///////////////<전역>//////////////////////////
bool isspin = false;
bool isaround = false;


bool issize = true;
int t_angle = 0;
int alphaSize = 0;
/////////////////////////////////////////////

class Points {
public:
	Vec3f m_pt;
	int index;
};

class Triangle {
private:
	deque<Vec3f>BigTriangle;
	Vec3f m_small_triangle_pt;
	int m_index = 0;
	int m_speed = 0;
	int m_Big_Size{};
	int m_Small_Size{};
public:
	Triangle() {}

	Triangle(int Big_Size, int Small_Size, int speed) {

		m_Big_Size = Big_Size;
		m_Small_Size = Small_Size;
		m_speed = speed;

		BigTriangle.push_front({0,m_Big_Size /2,0});
		BigTriangle.push_front({ m_Big_Size /2,-m_Big_Size / 2,0 });
		BigTriangle.push_front({ -m_Big_Size / 2,-m_Big_Size / 2,0 });

		m_small_triangle_pt = BigTriangle.at(0);

	}

	GLvoid Rander(int angle, Vec3f axis) {
		

		glPushMatrix();
		{
			glRotatef(angle, axis.x, axis.y, axis.z);

			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_LINE_LOOP);

			for (auto p : BigTriangle) {
				glVertex3f(p.x, p.y, p.z);
			}

			glEnd();
			glPushMatrix();
			{
				glTranslatef(m_small_triangle_pt.x, m_small_triangle_pt.y, m_small_triangle_pt.z);
				glColor3f(1.0, 0, 0);
				glBegin(GL_LINE_LOOP);

				glVertex3f(0, m_Small_Size / 2, 0);
				glVertex3f(m_Small_Size / 2, -m_Small_Size / 2, 0);
				glVertex3f(-m_Small_Size / 2, -m_Small_Size / 2, 0);

				glEnd();
			}
			glPopMatrix();
		}
		glPopMatrix();
	
	}

	GLvoid update() {
		
		Size_Spring();

		if(isaround)
		{
			Vec3f target;

			if (m_index != 2) {
				target = BigTriangle.at(m_index + 1);
			}
			else {
				target = BigTriangle.at(0);
			}

			Vec3f force{ target.x - m_small_triangle_pt.x, target.y - m_small_triangle_pt.y,  target.z - m_small_triangle_pt.z };
			force.Normalize();

			for (int i = 0; i < 32; ++i) {
				Vec3f temp;
				temp = force*m_speed;
				temp.Divide(16.0f);
				m_small_triangle_pt += temp;

				if (m_small_triangle_pt == target) {
					(++m_index) %= 3;
					m_small_triangle_pt = target;
					break;
				}
			}
		}
		


	}

	GLvoid Size_Spring() {
	
		if (issize) {
			m_Small_Size = Small_Size + sin(alphaSize*3.141592 / 180) * (Small_Size/2);
		}
	
	}


};




//////////////<기본 함수>//////////////////////////
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void SpecialInput(int key, int x, int y);
void Mouse(int button, int state, int x, int y);
void TimerFunction(int value);
//////////////////////////////////////////////////
void InitObjects();
GLvoid DrawShape();
void DrawTriangle(Vec3f Position, Vec3f Size, int angle, Vec3f axis);
void DrawRactangle(Vec3f Position, Vec3f Size, int angle, Vec3f axis);
///////////////////////////////////////////
Triangle x = Triangle(Base_Size, Small_Size,Speed);
Triangle y = Triangle(Base_Size, Small_Size, Speed*2);
////////////////////////////////////////////






void main(int argc, char *argv[])
{
	//초기화 함수들
	InitObjects();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(Window_Width, Window_Height); // 윈도우의 크기 지정
	glutCreateWindow("[2013182010김병진]Q12"); // 윈도우 생성 (윈도우 이름)
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
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기
								  // 색상 지정하고 사각형 그리기

	glColor4f(1.0, 1.0, 1.0, 1.0f);

	/////////////<좌표계 그림>//////////////////
	glBegin(GL_LINES);
	glVertex2f(-400.0, 0.0);
	glVertex2f(400.0, 0.0);
	glVertex2f(0.0, -400.0);
	glVertex2f(0.0, 400.0);
	glEnd();
	//////////////////////////////////////////
	glLoadIdentity();

	Vec3f Axis{ 0,1,0 };
	x.Rander(t_angle,Axis);
	y.Rander(t_angle+90, Axis);

	glutSwapBuffers(); // 화면에 출력하기 (glflush효과가 있다.)
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-400.0, 400, -400.0, 400, -400.0, 400.0); // x축 최소,최대, y축 최소,최대, z축 최소 최대
	glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'z' || key == 'Z') {
		issize = 1 - issize;
	}	// 신축
	if (key == 'x' || key == 'X') {
		isaround = 1 - isaround;
	}	// 어라운드
	if (key == 'c' || key == 'C') {
		isspin = 1 - isspin;
	}	// 회전
	if (key == 'q' || key == 'Q') {
		exit(0);
	}	// 종료
}

void Mouse(int button, int state, int x, int y)
{

}

void TimerFunction(int value)
{
	
	if(isspin)
	(++t_angle) %= 360;
	
	
	if(issize)
	(++alphaSize) %= 360;

	x.update();
	y.update();

	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(1, TimerFunction, 1); // 타이머함수 재 설정
}

void InitObjects()
{
	srand((unsigned)time(nullptr));

	
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
