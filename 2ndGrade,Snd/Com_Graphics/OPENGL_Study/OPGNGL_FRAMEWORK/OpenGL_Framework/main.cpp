#include<iostream>
#include <cstdlib>
#include <chrono>
#include <gl/glut.h>
#include <list>
#include <Windows.h>
#include "GLFramework.h"


using namespace std;


namespace {
	CGLFramework framework;
}; // 익명 네임 스페이스


constexpr int Window_Width = 800;
constexpr int Window_Height = 600;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void TimerFunction(int value);



// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	framework.drawScene();
}
GLvoid Reshape(int w, int h)
{
	framework.Reshape(w, h);
}

void Keyboard(unsigned char key, int x, int y)
{

}

void Mouse(int button, int state, int x, int y)
{

}

void TimerFunction(int value)
{
	framework.TimerFunction(value);
}


void main(int argc, char *argv[])
{
	//초기화 함수들

	framework.Initialize();
	framework.Run();
	
	//glutKeyboardFunc(Keyboard); // 키보드 입력 콜백 함수
	//glutMouseFunc(Mouse);
	

	
}
