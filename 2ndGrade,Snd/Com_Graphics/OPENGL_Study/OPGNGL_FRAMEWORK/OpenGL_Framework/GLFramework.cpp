#include "GLFramework.h"



GLvoid CGLFramework::Initialize(GLvoid)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(m_ptWindowPos.x, m_ptWindowPos.y); // 윈도우의 위치지정
	glutInitWindowSize(m_ptWindowSize.x, m_ptWindowSize.y); // 윈도우의 크기 지정
	glutCreateWindow(m_szTile); // 윈도우 생성 (윈도우 이름)
	
	glutTimerFunc(m_iFPS, ::TimerFunction, 1);

	glutDisplayFunc(::drawScene); // 출력 함수의 지정
	glutReshapeFunc(::Reshape); // 다시 그리기 함수의 지정
}

GLvoid CGLFramework::drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutSwapBuffers();
	glFlush(); // 화면에 출력하기
}

GLvoid CGLFramework::Reshape(int w, int h)
{
	m_ptWindowSize = Point2i{ w,h };

	glViewport(0, 0, w, h);
	glOrtho(0.0, w, 0.0, h, -1.0, 1.0);
}

GLvoid CGLFramework::TimerFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(m_iFPS,::TimerFunction,1); //::TimerFunction -> 전역이라 명시한다.
}

GLvoid CGLFramework::Run()
{
	glutMainLoop();
}
