#pragma once

#include <cstdlib>
#include <chrono>
#include <glut.h>

enum Shape_Type
{
	Digon = 0,Triangle,Rectangle,Pentagon
};
constexpr int Grid = 3;
constexpr int Window_Width = 800;
constexpr int Window_Height = 600;
constexpr float ShapeVoid = 0.015; // 도형의 칸 여백

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void main(int argc, char *argv[])
{
	//초기화 함수들
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(Window_Width, Window_Height); // 윈도우의 크기 지정
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

	srand((unsigned)time(nullptr));

	int Shape = rand() % 4;

	for (int i = 0; i < Grid; ++i) {
		(++Shape) %= 4;
		(++Shape) %= 4;
		for (int j = 0; j < Grid; ++j)
		{			
			switch ((i + j) % 2) {
			case 0:
				glColor4f(0.5f, 0.5f, 0.5f, 1.0f); // 그리기 색을 'blue' 으로 지정
				break;
			case 1:
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // 그리기 색을 'red' 으로 지정
				break;

			}
			glRectf(2.0f / (float)Grid*j - 1.0f,
				2.0f / (float)Grid*i - 1.0f,
				2.0f / (float)Grid*(j + 1) - 1.0f,
				2.0f / (float)Grid*(i + 1) - 1.0f); // 사각형 그리기

			glColor4f(0.7f, 0.7f, 1.0f, 1.0f);	

				GLfloat p1[2];
				GLfloat p2[2];
				GLfloat p3[2];
				GLfloat p4[2];
				GLfloat p5[2];

			switch (Shape) {
			case Shape_Type::Digon:
				p1[0] = { (2.0f / (float)Grid*j - 1.0f) + ShapeVoid };
				p1[1] = { (2.0f / (float)Grid*i - 1.0f) + ShapeVoid };

				p2[0] = {(2.0f / (float)Grid*(j + 1) - 1.0f) - ShapeVoid };
				p2[1] = {(2.0f / (float)Grid*(i + 1) - 1.0f) - ShapeVoid };

				glBegin(GL_LINES);
					glVertex2f(p1[0], p1[1]);
					glVertex2f(p2[0], p2[1]);
				glEnd();
				Shape = Shape_Type::Triangle;
				break;
			case Shape_Type::Triangle:
				p1[0] = { (2.0f / (float)Grid*j - 1.0f) + ShapeVoid };
				p1[1] = { (2.0f / (float)Grid*i - 1.0f) + ShapeVoid };

				p2[0] = { (2.0f / (float)Grid*j - 1.0f) + ShapeVoid };
				p2[1] = { (2.0f / (float)Grid*(i+1) - 1.0f) - ShapeVoid };

				p3[0] = { (2.0f / (float)Grid*(j + 1) - 1.0f) - ShapeVoid };
				p3[1] = { (2.0f / (float)Grid*(i + 1) - 1.0f) - ShapeVoid };

				glBegin(GL_TRIANGLES);
					glVertex2f(p1[0], p1[1]);
					glVertex2f(p2[0], p2[1]);
					glVertex2f(p3[0], p3[1]);
				glEnd();
				Shape = Shape_Type::Rectangle;
				break;
			case Shape_Type::Rectangle:
				p1[0] = { (2.0f / (float)Grid*j - 1.0f) + ShapeVoid };
				p1[1] = { (2.0f / (float)Grid*i - 1.0f) + ShapeVoid };

				p2[0] = { (2.0f / (float)Grid*j - 1.0f) + ShapeVoid };
				p2[1] = { (2.0f / (float)Grid*(i + 1) - 1.0f) - ShapeVoid };

				p3[0] = { (2.0f / (float)Grid*(j + 1) - 1.0f) - ShapeVoid };
				p3[1] = { (2.0f / (float)Grid*(i + 1) - 1.0f) - ShapeVoid };
	
				p4[0] = { (2.0f / (float)Grid*(j + 1) - 1.0f) - ShapeVoid };
				p4[1] = { (2.0f / (float)Grid*i - 1.0f) + ShapeVoid };

				glBegin(GL_POLYGON);
					glVertex2f(p1[0], p1[1]);
					glVertex2f(p2[0], p2[1]);
					glVertex2f(p3[0], p3[1]);
					glVertex2f(p4[0], p4[1]);
				glEnd();
				Shape = Shape_Type::Pentagon;
				break;
			case Shape_Type::Pentagon:
			
				float angleIncrement = 360.0f / 5; 
				angleIncrement *= 3.14 / 180.0f;    // 도 -> 라디안
				glBegin(GL_TRIANGLE_FAN);
				float angle = 0.0f;
				for (int k = 0; k < 5; ++k) {
					glVertex3f(
						(2.0f / (float)Grid*j - 0.65f) + 0.3f * cos(angle),
						(2.0f / (float)Grid*i - 0.65f) + 0.3f * sin(angle),
						0.0f);
					angle += angleIncrement;
				}
				glEnd();
				Shape = Shape_Type::Digon;
				break;
			}
		}
		
	}

	glFlush(); // 화면에 출력하기
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	//glOrtho(-400.0, 400.0, -300.0, 300.0, -1.0, 1.0);
}
