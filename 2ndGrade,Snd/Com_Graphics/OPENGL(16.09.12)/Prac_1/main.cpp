#include <glut.h>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void main(int argc, char *argv[])
{
	//초기화 함수들
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("Example2"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정
	glutMainLoop();
}
// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기
								  // 색상 지정하고 사각형 그리기
	
	glColor4f(0.0f, 1.0f, 0.5f, 1.0f); // 그리기 색을 'green' 으로 지정
	glRectf(-1.0f, 1.0f, -0.7f, 0.7f); // 사각형 그리기
	
	glColor4f(1.0f, 1.0f, 0.2f, 1.0f); // 그리기 색을 'green' 으로 지정
	glRectf(0.7f, 1.0f, 1.0f, 0.7f);

	glColor4f(0.7f, 1.0f, 1.0f, 1.0f); // 그리기 색을 'green' 으로 지정
	glRectf(-0.3f, 0.3f, 0.3f, -0.3f);

	glColor4f(0.0f, 1.0f, 1.0f, 1.0f); // 그리기 색을 'green' 으로 지정
	glRectf(-1.0f, -1.0f, -0.7f, -0.7f);

	glColor4f(0.0f, 0.5f, 0.6f, 1.0f); // 그리기 색을 'green' 으로 지정
	glRectf(0.7f, -1.0f, 1.0f, -0.7f);

	glFlush(); // 화면에 출력하기
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}
