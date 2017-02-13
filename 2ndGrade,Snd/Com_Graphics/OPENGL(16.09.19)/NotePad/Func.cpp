#include "Func.h"
/*
기능 : 윈도우 출력
설명 : 윈도우 배경색 출력
*/
GLvoid drawScene(GLvoid)
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < count; ++i)
	{
		DrawRect(rect[i]);
	}
	

	glFlush();	//glutSwapBuffer();
}

/*
기능 : 윈도우 재 출력
설명 : 업데이트 된 화면을 다시 그린다.
*/
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	//glOrtho(0, 0, Width, Height, -1.0, 1.0);
	

	glOrtho(0.0, Width, 0.0, Height, -1.0, 1.0);
}


void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (count < 10) {
			rect[count].x = x;
			rect[count].y = Height - y;
		count++;
		}
	}
}

/*
기능 : 사각형 출력
설명 : 마우스가 찍은 점을 입력 받은 리스트를 받아서 사각형으로 바꾸어 출력한다.
*/
void DrawRect(Point rt) {

	
	Point v1 = { 20 , 0 }, v2 = { 0 , 20 }, v3 = { 20, 20 };

	v1 = { rt.x + v1.x, rt.y + v1.y };
	v2 = { rt.x + v1.x, rt.y + v1.y };
	v3 = { rt.x + v1.x, rt.y + v1.y };

	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
		glVertex2i(rt.x, rt.y);
		glVertex2i(v1.x, v1.y);
		glVertex2i(v3.x, v3.y);
		glVertex2i(v2.x, v2.y);
	glEnd();
	
	
	/*
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
		glVertex2i(rt.x, rt.y + 20); //v1
		glVertex2i(rt.x, rt.y); //v2
		glVertex2i(rt.x + 20, rt.y); //v3
		glVertex2i(rt.x + 20, rt.y + 20); //v4
	glEnd();
	*/
	
}


void TimerFunction(int value)
{

	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(100, TimerFunction, 1); // 타이머함수 재 설정
}