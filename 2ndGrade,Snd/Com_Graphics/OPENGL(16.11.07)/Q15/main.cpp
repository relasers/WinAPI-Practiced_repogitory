#include<iostream>
#include<gl/glut.h>
#include<ctime>
#include"Vec3D.h"

using namespace std;

enum Type {
	Cube = 0, Sphere, Cone, Teapot
};

constexpr int Window_Width = 800;
constexpr int Window_Height = 800;

constexpr float axis_size = 50.0;
constexpr float floor_size = 120.0;
constexpr int shape_size = (int)floor_size / 2;
constexpr int Rotate_Speed = 2;
constexpr float PI = 3.141592;

constexpr float Planet_Size = 25;
constexpr float Orbit_Size = 150;

class Mini_Orbit {
private:
	Vec3f m_pt{};
	Vec3f m_min_pt{};
	int m_angle = rand()%360;
	bool m_iswire;
public:

	void Rander(int angle, Vec3f axis) {

		glPushMatrix();
		{
			glRotatef(angle, axis.x, axis.y, axis.z);
			glTranslatef(m_pt.x, m_pt.y, m_pt.z);

			glColor3f(0.0,1.0,0.0);
			if(m_iswire)glutWireSphere(Planet_Size / 2, 25, 25);
			if(!m_iswire)glutSolidSphere(Planet_Size / 2, 25, 25);
			glRotatef(-angle, axis.x, axis.y, axis.z);

			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < 360; ++i) {
				glColor3f(0.0, 0.5, 0.3);
				glVertex3f(cos(i*PI / 180.0)*Orbit_Size/2, 0, sin(i*PI / 180.0) * Orbit_Size/2);
			}
			glEnd();

			glTranslatef(m_min_pt.x, m_min_pt.y, m_min_pt.z);
			glColor3f(0.7, 1.0, 0.0);
			if (m_iswire)glutWireSphere(Planet_Size / 3, 25, 25);
			if (!m_iswire)glutSolidSphere(Planet_Size / 3, 25, 25);


		}
		glPopMatrix();

	}

	void Update(int speed) {

		for (int i = 0; i < speed; ++i )(++m_angle) %= 360;

		m_pt.x = cos(m_angle*PI / 180.0)*Orbit_Size;
		m_pt.z = sin(m_angle*PI / 180.0)*Orbit_Size;

		m_min_pt.x = cos(m_angle*PI / 180.0)*Orbit_Size/2;
		m_min_pt.z = sin(m_angle*PI / 180.0)*Orbit_Size/2;

	}
	void switchtype(bool iswire) {
		m_iswire = iswire;
	
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
void MenuFunc(int button);
//////////////////////////////////////////////////
void InitObjects();

void DrawAxis();
void DrawFloor();

void DrawTriangle(Vec3f Position, Vec3f Size, int angle, Vec3f axis);
void DrawRactangle(Vec3f Position, Vec3f Size, int angle, Vec3f axis);
void DrawOrbitLine(int angle, Vec3f axis);
///////////////////////////////////////////
int x_angle = 0;
int y_angle = 0;
int z_angle = 0;

int x_pos = 0;
int y_pos = 0;
int z_pos = 0;
bool iswire = false;
Mini_Orbit orbit[3];
////////////////////////////////////////////





void main(int argc, char *argv[])
{
	//초기화 함수들
	InitObjects();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(Window_Width, Window_Height); // 윈도우의 크기 지정
	glutCreateWindow("[2013182010김병진]Q15"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutKeyboardFunc(Keyboard); // 키보드 입력 콜백 함수
	glutTimerFunc(1, TimerFunction, 1);
	glutMouseFunc(Mouse);
	

	GLint SubMenu;
	GLint MainMenu;
	SubMenu = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("Wire", 1);
	glutAddMenuEntry("Solid", 2);
	MainMenu = glutCreateMenu(MenuFunc);
	glutAddSubMenu("Shape", SubMenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


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
		//glRotatef(x_angle, 1, 0, 0);
		//glRotatef(y_angle, 0, 1, 0);
		glRotatef(z_angle, 0, 0, 1);
		//

		glTranslated(x_pos,y_pos,z_pos);


		DrawAxis();

		//////////////////<바닥>////////////////////
		//DrawFloor();

		glColor4f(1.0, 1.0, 1.0, 1.0);
		glutWireCube(floor_size * 2);
		
		glColor4f(1.0, 1.0, 0.0, 1.0);
		
		if (iswire)glutWireSphere(Planet_Size, 25, 25);
		if(!iswire)glutSolidSphere(Planet_Size,25,25);

		glColor4f(0.0, 1.0, 1.0, 1.0);
		DrawOrbitLine(0, {0,0,0});
		DrawOrbitLine(45, { 0,0,1 });
		DrawOrbitLine(-45, { 0,0,1 });

		orbit[0].Rander(0, { 0,0,0 });
		orbit[1].Rander(45, { 0,0,1 });
		orbit[2].Rander(-45, { 0,0,1 });


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
		if (key == 'x') {
			x_pos--;
		}
		if (key == 'X') {
			x_pos++;
		}
		if (key == 'y') {
			y_pos--;
		}
		if (key == 'Y') {
			y_pos++;
		}
		if (key == 'z') {
			z_angle--;
		}
		if (key == 'Z') {
			z_angle++;
		}
		if (key == '+') {
			z_pos--;
		}
		if (key == '-') {
			z_pos++;
		}
		if (key == 'i' || key == 'I') {
			x_pos = 0;
			y_pos = 0;
			z_pos = 0;
			x_angle = 0;
			y_angle = 0;
			z_angle = 0;
		}
	}
	


	if (key == 'q' || key == 'Q') {
		exit(0);
	}	// 종료
}

void Mouse(int button, int state, int x, int y)
{

}

void TimerFunction(int value)
{
	orbit[0].Update(1);
	orbit[1].Update(2);
	orbit[2].Update(3);

	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(1, TimerFunction, 1); // 타이머함수 재 설정
}

void MenuFunc(int button)
{

	switch (button) {
	case 1:
		for (int i = 0; i < 3; ++i) orbit[i].switchtype(true);
		iswire = true;
		break;
	case 2:
		for (int i = 0; i < 3; ++i) orbit[i].switchtype(false);
		iswire = false;
		break;
	}
	glutPostRedisplay();

}

void InitObjects()
{
	srand((unsigned)time(nullptr));


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

		glVertex3f(floor_size, -floor_size, -floor_size);
		glVertex3f(-floor_size, -floor_size, -floor_size);
		glVertex3f(-floor_size, -floor_size, floor_size);
		glVertex3f(floor_size, -floor_size, floor_size);

		glVertex3f(floor_size, -floor_size - 2, -floor_size);
		glVertex3f(-floor_size, -floor_size - 2, -floor_size);
		glVertex3f(-floor_size, -floor_size - 2, floor_size);
		glVertex3f(floor_size, -floor_size - 2, floor_size);

		glEnd();
	}
}

void DrawOrbitLine(int angle, Vec3f axis) {

	glPushMatrix();
	{
	
		glRotatef(angle, axis.x, axis.y,axis.z);

		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < 360; ++i) {
			glVertex3f(cos(i*PI / 180.0)*Orbit_Size, 0, sin(i*PI / 180.0) * Orbit_Size);
		}
		glEnd();
	
	}
	glPopMatrix();
	


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
