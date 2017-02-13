#include<iostream>
#include<gl/glut.h>
#include<Windows.h>
#include<chrono>
#include<cmath>

using namespace std;

constexpr int Window_Width = 800;
constexpr int Window_Height = 800;
enum RotateMode {
	None=0,Rot_X,Rot_Y,Rot_Z
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
GLvoid ModelRotate();
///////////////<전역>//////////////////////////
int angle = 0;
int frame = 0;
float shape_size = 10;
int alphasize = 0;

float w_x = 0;
float w_y = 0;
int mode = RotateMode::None;
bool ani_mode = false;
bool size_mode = false;
/////////////////////////////////////////////
class Vector3
{
public:
	float x, y, z;
};
void Cube(Vector3 pos, Vector3 size, float angle, Vector3 axis)
{
	glPushMatrix();
		//draw();
	glPopMatrix();
}




void main(int argc, char *argv[])
{
	//초기화 함수들
	InitObjects();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(Window_Width, Window_Height); // 윈도우의 크기 지정
	glutCreateWindow("[2013182010김병진]Q11"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutKeyboardFunc(Keyboard); // 키보드 입력 콜백 함수
	glutSpecialFunc(SpecialInput);
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
	
	glMatrixMode(GL_PROJECTION);
	/////////////<좌표계 그림>//////////////////
	glBegin(GL_LINES);
	glVertex2f(-1.0, 0.0);
	glVertex2f(1.0, 0.0);
	glVertex2f(0.0, -10.0);
	glVertex2f(0.0, 1.0);
	glEnd();
	//////////////////////////////////////////
	glLoadIdentity();
	
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();
	glTranslatef(w_x, w_y, 0);
		////////////////<사인>////////////////////
		glPushMatrix();
			glTranslatef(0, 0.5, 0);
			ModelRotate();

			glBegin(GL_LINE_STRIP);
				for (int i = -720; i < 720; i++)
				{
					glVertex3f(0.01*i/ shape_size, sin(3.1415927 / 180 * (i+ frame))/ shape_size, 0);
					
				}
			glEnd();
		glPopMatrix();
		/////////////////////////////////////////////
		//////////////////<코사인>///////////////////////////////
		glPushMatrix();
		glTranslatef(0, 0.2, 0);
		ModelRotate();
		glBegin(GL_LINE_STRIP);
		for (int i = -720; i < 720; i++)
		{
			glVertex3f(0.01*i / shape_size, cos(3.1415927 / 180 * (i + frame)) / shape_size, 0);

		}
		glEnd();

		glPopMatrix();
		////////////////////////////////////////////////
		////////////////////<스프링>//////////////////////
		glPushMatrix();
			float r = 1.0;
			float b = 0.0;
			glTranslatef(0, -0.2, 0);
			ModelRotate();
			glBegin(GL_LINE_STRIP);
			for (int i = -1080; i < 1080; ++i) {
				r -= 0.00046;
				b += 0.00046;
				glColor4f(r, 0, b, 1.0f);
				glVertex3f(cos(3.1415927 / 180 * (i + frame)) / shape_size + i*0.0005, sin(3.1415927 / 180 * (i + frame)) / shape_size, 0);
			}
			glEnd();
		glPopMatrix();
		///////////////////////////////////////////////
		glColor4f(1.0, 1.0, 1.0, 1.0f);
		////////////////<직사각형>////////////////////
		glPushMatrix();
			glTranslatef(0,-0.5,0);
			ModelRotate();
			
			glPushMatrix();
			for (int i = 0; i < 4; ++i) {
				glutWireCube(shape_size/100);
				glTranslatef(-0.2, 0, 0);
			}
			glPopMatrix();
			glPushMatrix();
			glTranslatef(0.2, 0, 0);
			for (int i = 0; i < 3; ++i) {
				glutWireCube(shape_size/100);
				glTranslatef(0.2, 0, 0);
			}
			glPopMatrix();
		glPopMatrix();
		/////////////////////////////////////////////

	glPopMatrix();

	glutSwapBuffers(); // 화면에 출력하기 (glflush효과가 있다.)
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, w, 0.0, h, -400.0, 400.0); // x축 최소,최대, y축 최소,최대, z축 최소 최대
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'x' || key == 'X') {
		angle = 0;
		mode = RotateMode::Rot_X;
	}	// x축 회전
	if (key == 'y' || key == 'Y') {
		angle = 0;
		mode = RotateMode::Rot_Y;
	}	// y축 회전
	if (key == 'z' || key == 'Z') {
		angle = 0;
		mode = RotateMode::Rot_Z;
	}	// z축 회전
	if (key == 'n' || key == 'N') {
		angle = 0;
		mode = RotateMode::None;
	}	// 회전 정지
	if (key == 'a') {
		ani_mode = 1 - ani_mode;
	}	// 애니메이션
	if (key == 's' || key == 'S') {
		size_mode = 1 - size_mode;
	}	// 이미지 확대 축소
	if (key == 'i' || key == 'I') {
		w_x = 0;
		w_y = 0;
	}	// 위치 리셋
	if (key == 'q' || key == 'Q') {
		exit(0);
	}	// 종료
}

void SpecialInput(int key, int x, int y)
{
	if (key == GLUT_KEY_UP) {
		w_y += 0.1;
	}
	if (key == GLUT_KEY_DOWN) {
		w_y -= 0.1;
	}
	if (key == GLUT_KEY_LEFT) {
		w_x -= 0.1;
	}
	if (key == GLUT_KEY_RIGHT) {
		w_x += 0.1;
	}
}

void Mouse(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		POINT temp{ x,Window_Height - y };
	}

}

void TimerFunction(int value)
{
	(++angle) %= 360;
	
	if (ani_mode)
	{
		(++frame) %= 360;
	}

	if (size_mode){
		(++alphasize) %= 360;
		shape_size = 10 + sin(alphasize*3.141592/180)*3;
	}

	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(1, TimerFunction, 1); // 타이머함수 재 설정
}

void InitObjects()
{
	srand((unsigned)time(nullptr));


}

GLvoid ModelRotate()
{
	switch (mode) {
	case RotateMode::None:
		break;
	case RotateMode::Rot_X:
		glRotatef(angle, 1.0, 0.0, 0.0);
		break;
	case RotateMode::Rot_Y:
		glRotatef(angle, 0.0, 1.0, 0.0);
		break;
	case RotateMode::Rot_Z:
		glRotatef(angle, 0.0, 0.0, 1.0);
		break;

	}
}
