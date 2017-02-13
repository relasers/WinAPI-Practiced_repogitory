#pragma once

#include<iostream>
#include <cstdlib>
#include <chrono>
#include <glut.h>
#include <list>
#include "Ractangle.h"

using namespace std;

constexpr int Window_Width = 800;
constexpr int Window_Height = 600;
constexpr int Max_Ractangle = 20;

int main_tick = 0;

list <CRectangle> shapes;
list<CRectangle>::iterator itor = shapes.begin();

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void TimerFunction(int value);
void MenuFunc(int button);


void main(int argc, char *argv[])
{

	//초기화 함수들
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(Window_Width, Window_Height); // 윈도우의 크기 지정
	glutCreateWindow("Prac_5"); // 윈도우 생성 (윈도우 이름)
								////////////////<메뉴 구축>///////////////////////////////
	GLint SubMenu;
	GLint MainMenu;
	SubMenu = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("Rectangle", 1);
	glutAddMenuEntry("Circle", 2);
	MainMenu = glutCreateMenu(MenuFunc);
	glutAddSubMenu("Shape", SubMenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);	///////////////////////////////////////////////
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutKeyboardFunc(Keyboard); // 키보드 입력 콜백 함수
	glutTimerFunc(100, TimerFunction, 1);
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정
	glutMainLoop();


}
// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{


	glClearColor(0.0f, 1.0f, 1.0f, 1.0f); // 바탕색 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기
								  // 색상 지정하고 사각형 그리기

	for (itor = shapes.begin(); itor != shapes.end(); itor++)
	{
		itor->Draw();
	}

	glFlush(); // 화면에 출력하기
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, Window_Width, 0.0, Window_Height, -1.0, 1.0);

}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == '+')
	{
		for (itor = shapes.begin(); itor != shapes.end(); itor++)
		{
			itor->IncreaseSpd();
		}
	}
	if (key == '-')
	{
		for (itor = shapes.begin(); itor != shapes.end(); itor++)
		{
			itor->DecreaseSpd();
		}
	}
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		for (itor = shapes.begin(); itor != shapes.end(); itor++)
		{
			if (itor->CollisionCheck(x, Window_Height-y)) {
				for (itor = shapes.begin(); itor != shapes.end(); itor++)
				{
					itor->MoveOn();
				}
				break;
			}
		}
	}

}

void TimerFunction(int value)
{

	for (itor = shapes.begin(); itor != shapes.end(); itor++)
	{
		itor->Update(Window_Width, Window_Height);
	}

	if (main_tick % 20 == 0) {
		POINT temp{ rand() % Window_Width,rand() % Window_Height };
		if (shapes.size() <= Max_Ractangle) shapes.push_front(CRectangle(temp));
	}
	
	(++main_tick) %= 200;

	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(20, TimerFunction, 1); // 타이머함수 재 설정
}

void MenuFunc(int button)
{
	switch (button) {
	case 1:
		for (itor = shapes.begin(); itor != shapes.end(); itor++)
		{
			itor->ChangeShape(0);
		}
		break;
	case 2:
		for (itor = shapes.begin(); itor != shapes.end(); itor++)
		{
			itor->ChangeShape(1);
		}
		break;
	}
	glutPostRedisplay();
}