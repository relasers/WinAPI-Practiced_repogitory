#include<iostream>
#include<gl/glut.h>
#include "Vec3D.h"=
using namespace std;

constexpr int Window_Width = 800;
constexpr int Window_Height = 800;

constexpr float axis_size = 120.0;
constexpr float floor_size = 120.0;


class Models {
private:
	Vec3f m_pt{};
	float m_size{ 50 };
	Vec3f m_alpha{ 0.3f, 0.5f,0.7f };

	GLenum m_source;
	GLenum m_destination;
	char *m_string;
	
public:
	void Rander() {

		glPushMatrix();
		{
			glEnable(GL_BLEND);
			glBlendFunc(m_source, m_destination);

			glTranslatef(m_pt.x,m_pt.y,m_pt.z);

			glTranslatef(m_size,0, m_size*2);
			glColor4f(1.0,0.0,0.0, m_alpha.x);
			glRotatef(270, 1, 0, 0);
			glutSolidCone(m_size,m_size*2,40,40);
			glRotatef(-270, 1, 0, 0);
			glTranslatef(-m_size, 0, -m_size*2);
			
			glTranslatef(0, m_size, 0);
			glColor4f(0.0, 1.0, 0.0, m_alpha.y);
			glutSolidTeapot(m_size);
			glTranslatef(0, -m_size, 0);


			glTranslatef(0, 0, -m_size*2);
			glColor4f(0.0,0.0,1.0, m_alpha.z);
			glutSolidSphere(m_size,40,40);

			glDisable(GL_BLEND);

			switch (m_source) {
			case GL_ZERO:
				m_string = "( GL_ZERO, ";
				break;
			case GL_ONE:
				m_string = "( GL_ONE, ";
				break;
			case GL_DST_COLOR:
				m_string = "( GL_DST_COLOR, ";
				break;
			case GL_ONE_MINUS_DST_COLOR:
				m_string = "( GL_ONE_MINUS_DST_COLOR, ";
				break;
			case GL_SRC_ALPHA:
				m_string = "( GL_SRC_ALPHA, ";
				break;
			case GL_ONE_MINUS_SRC_ALPHA:
				m_string = "( GL_ONE_MINUS_SRC_ALPHA, ";
				break;
			}

			glRasterPos2f(-m_size*2.3, -m_size*2); // 문자 출력할 위치 설정
			int len = (int)strlen(m_string);
			for (int i = 0; i < len; i++)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, m_string[i]);



			switch (m_destination) {
			case GL_ZERO:
				m_string = "GL_ZERO) ";
				break;
			case GL_ONE:
				m_string = "GL_ONE) ";
				break;
			case GL_DST_COLOR:
				m_string = "GL_DST_COLOR) ";
				break;
			case GL_ONE_MINUS_DST_COLOR:
				m_string = "GL_ONE_MINUS_DST_COLOR) ";
				break;
			case GL_SRC_ALPHA:
				m_string = "GL_SRC_ALPHA) ";
				break;
			case GL_ONE_MINUS_SRC_ALPHA:
				m_string = "GL_ONE_MINUS_SRC_ALPHA) ";
				break;
			}

			glRasterPos2f(-m_size*2.3, -m_size * 2.5); // 문자 출력할 위치 설정
			len = (int)strlen(m_string);
			for (int i = 0; i < len; i++)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, m_string[i]);


		}
		glPopMatrix();
	
	}
	void Update() {};
	void SetPt(Vec3f pt) { m_pt = pt; }
	void SetMode(GLenum source, GLenum destination) { m_source = source; m_destination = destination; }
	void CtrlAlpha(float alpha,Vec3f axis) { m_alpha += alpha*axis;
	if (m_alpha.x < 0) m_alpha.x = 0;
	if (m_alpha.x > 1) m_alpha.x = 1;

	if (m_alpha.y < 0) m_alpha.y = 0;
	if (m_alpha.y > 1) m_alpha.y = 1;

	if (m_alpha.y < 0) m_alpha.y = 0;
	if (m_alpha.y > 1) m_alpha.y = 1;



	};
};

//////////////<기본 함수>//////////////////////////
GLvoid RanderScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void SpecialInput(int key, int x, int y);
void Mouse(int button, int state, int x, int y);
void TimerFunction(int value);
void Init();
void DrawAxis();
void DrawFloor();
//////////////////////////////////////////////////


int x_index = 0;
int y_index = 0;

Models models[3][3];

void main(int argc, char *argv[])
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(Window_Width, Window_Height); // 윈도우의 크기 지정
	glutCreateWindow("Q38"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(RanderScene); // 출력 함수의 지정
	glutKeyboardFunc(Keyboard); // 키보드 입력 콜백 함수
	glutMouseFunc(Mouse);
	glutTimerFunc(1, TimerFunction, 1);
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정

	Init();

	glutMainLoop();


}

GLvoid RanderScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기
												// 색상 지정하고 사각형 그리기
	




	GLfloat AmbientLight[] = { 0.7f, 0.7f,0.7f, 1.0f };
	GLfloat DiffuseLight[] = { 1.0f, 1.0f,1.0f, 1.0f };
	GLfloat SpecularLight[] = { 1.0f, 1.0f,1.0f, 1.0f };
	GLfloat lightPos[] = {0,0,0.0f, 1.0f };
	GLfloat LightModel_Ambiant[] = { 0.0f,0.0f,0.0f,1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModel_Ambiant);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 0.0);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);
	GLfloat Ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat Specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Specref);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 128);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기
														// 색상 지정하고 사각형 그리기
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);


	glEnable(GL_LIGHT0);


	//glFrontFace(GL_CW);

	glPushMatrix();
	{
		DrawAxis();
		glColor4f(1.0, 1.0, 1.0, 1.0);

		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				models[i][j].Rander();
			}
		}
		
		glPushMatrix();		{			glTranslatef(Window_Width / 6 * (x_index + 1) + Window_Width / 6 * (x_index),				Window_Height / 6 * (y_index  + 1) + Window_Height / 6 * (y_index),				0);						glBegin(GL_LINE_STRIP);			glVertex3f(-Window_Width / 6, -Window_Height / 6,0.0);			glVertex3f(-Window_Width / 6, Window_Height / 6, 0.0);			glVertex3f(Window_Width / 6, Window_Height / 6, 0.0);			glVertex3f(Window_Width / 6, -Window_Height / 6, 0.0);			glVertex3f(-Window_Width / 6, -Window_Height / 6, 0.0);			glEnd();		}		glPopMatrix();
				glPointSize(5.0);
		glColor3f(0.0, 0.0, 1.0);




	}
	glPopMatrix();

	glutSwapBuffers(); // 화면에 출력하기 (glflush효과가 있다.)
}

void TimerFunction(int value)
{
	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(1, TimerFunction, 1); // 타이머함수 재 설정
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'a' || key == 'A') {
		x_index = max(0, x_index-1);
	}
	if (key == 'd' || key == 'D') {
		x_index = min(2, x_index+1);
	}
	if (key == 'w' || key == 'W') {
		y_index = min(2, y_index+1);
	}
	if (key == 's' || key == 'S') {
		y_index = max(0, y_index-1);
	}
	if (key == 'i' || key == 'I') {
		models[y_index][x_index].CtrlAlpha(-0.1, {1,0,0});
	}
	if (key == 'o' || key == 'O') {
		models[y_index][x_index].CtrlAlpha(0.1, { 1,0,0 });
	}
	if (key == 'j' || key == 'J') {
		models[y_index][x_index].CtrlAlpha(-0.1, { 0,1,0 });
	}
	if (key == 'k' || key == 'K') {
		models[y_index][x_index].CtrlAlpha(0.1, { 0,1,0 });
	}
	if (key == 'n' || key == 'N') {
		models[y_index][x_index].CtrlAlpha(-0.1, { 0,0,1 });
	}
	if (key == 'm' || key == 'M') {
		models[y_index][x_index].CtrlAlpha(0.1, { 0,0,1 });
	}

}

void Mouse(int button, int state, int x, int y)
{

}

GLvoid Reshape(int w, int h)
{
	//////<뷰포트 변환 설정>////////
	glViewport(0, 0, w, h);


	/////<투영 행렬스택 재설정>//////
	//glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	///////////<원근투영>////////////////////////
	//gluPerspective(60.0f, w / h, 1.0, 1000.0); // fovy :: 최대 180(넘어가면 거꾸로 보여), 작을수록 크게 보임
	//glMatrixMode(GL_MODELVIEW);

	glOrtho(0.0, Window_Width, 0.0, Window_Height, -800, 800);
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
	glPushMatrix();
	{
		glColor4f(0.2, 0.5, 0.2, 0.7f);
		glTranslated(0,-floor_size,0);
		glScalef(2, 0.01, 2);

		{
			glutSolidCube(floor_size);
		}
	}
	glPopMatrix();
}

void Init() {

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			Vec3f pt = { Window_Width / 6 * (j + 1) + Window_Width / 6 * (j),Window_Height / 6 * (i + 1) + Window_Height / 6 * (i),0 };
			models[i][j].SetPt(pt);
		}
	}

	models[0][0].SetMode(GL_ONE, GL_ZERO);
	models[0][1].SetMode(GL_ZERO, GL_ONE);
	models[0][2].SetMode(GL_ONE, GL_ONE);

	models[1][0].SetMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	models[1][1].SetMode(GL_SRC_ALPHA, GL_ONE);
	models[1][2].SetMode(GL_ZERO, GL_SRC_COLOR);

	models[2][0].SetMode(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
	models[2][1].SetMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
	models[2][2].SetMode(GL_ONE, GL_ONE);


}