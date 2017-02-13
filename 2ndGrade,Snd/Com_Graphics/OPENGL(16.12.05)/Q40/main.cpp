#include<iostream>
#include<gl/glut.h>
#include <Windows.h>
#include<ctime>
#include<list>
#include"Vec3D.h"
#include "Camera.h"
#include "Bitmap.h"
/*
 I
JKL  :: 카메라를 조작합니다
+, - :: 카메라의 거리를 늘리고 줄입니다

*/

GLuint texture_object[6];
GLubyte * TexBits;
BITMAPINFO *m_bitInfo[6];

using namespace std;

constexpr int Window_Width = 800;
constexpr int Window_Height = 800;

constexpr float axis_size = 50.0;
constexpr float floor_size = 400.0;

constexpr int Rotate_Speed = 10;

class Bound_Box {
public:
	int m_left{};
	int m_right{};
	int m_top{};
	int m_bottom{};
	int m_near{};
	int m_far{};
public:
	void Rander() {
		glPushMatrix();
		glColor3f(1.0,0.0,0.0);
		glScalef(m_right - m_left, 10, m_far - m_near);
		glutWireCube(1);

		glPopMatrix();
	}
	void SetBB(Vec3f pt, Vec3i size) {
		m_left = pt.x - size.x;
		m_right = pt.x + size.x;

		m_top = pt.y - size.y;
		m_bottom = pt.y + size.y;

		m_near = pt.z - size.z;
		m_far = pt.z + size.z;

	}
	bool CollisionCheck(Bound_Box bb2) {
		if (m_left > bb2.m_right) return false;
		if (m_right < bb2.m_left) return false;
		if (m_far < bb2.m_near) return false;
		if (m_near > bb2.m_far) return false;
		return true;
	}

};

class Pyramid {
private:
	Vec3f m_pt;
	float m_size{ 15 };
	int m_angle{};

	bool m_normalizemode = true;
public:
	void Rander() {
		glPushMatrix();
		{
			glTranslatef(m_pt.x,m_pt.y,m_pt.z);
			
			glColor3f(0.0f,0.5f,0.0f);
			glBegin(GL_TRIANGLE_FAN);

			{
				Vec3f a = { 0.0f,m_size * 2,0.0f };
				Vec3f b = { -m_size,0.0f,-m_size };
				Vec3f c = { m_size, 0.0f,-m_size };

				Vec3f d = b - a;
				Vec3f e = c - a;
				Vec3f f = Normalize(Cross(d, e));
				if(m_normalizemode)glNormal3f(f.x, f.y, f.z);
				glVertex3f(0.0, m_size * 2, 0.0);
				glVertex3f(-m_size, 0.0, -m_size);
				glVertex3f(m_size, 0.0, -m_size);
			}

			{
				Vec3f a = { 0.0, m_size * 2, 0.0 };
				Vec3f b = { m_size, 0.0, m_size };
				Vec3f c = { -m_size, 0.0, m_size };

				Vec3f d = b - a;
				Vec3f e = c - a;
				Vec3f f = Normalize(Cross(d, e));
				if (m_normalizemode)glNormal3f(f.x, f.y, f.z);
				glVertex3f(0.0, m_size * 2, 0.0);
				glVertex3f(m_size, 0.0, m_size);
				glVertex3f(-m_size, 0.0, m_size);
			}

			{
				Vec3f a = { 0.0, m_size * 2, 0.0 };
				Vec3f b = { -m_size, 0.0, -m_size };
				Vec3f c = { -m_size, 0.0, m_size };

				Vec3f d = b - a;
				Vec3f e = c - a;
				Vec3f f = Normalize(Cross(d, e));
				if (m_normalizemode)glNormal3f(f.x, f.y, f.z);
				glVertex3f(0.0, m_size * 2, 0.0);
				glVertex3f(-m_size, 0.0, -m_size);
				glVertex3f(-m_size, 0.0, m_size);
			}

			{
				Vec3f a = { 0.0, m_size * 2, 0.0 };
				Vec3f b = { m_size, 0.0, m_size };
				Vec3f c = { m_size, 0.0, -m_size };

				Vec3f d = b - a;
				Vec3f e = c - a;
				Vec3f f = Normalize(Cross(d, e));
				if (m_normalizemode)glNormal3f(f.x, f.y, f.z);
				glVertex3f(0.0, m_size * 2, 0.0);
				glVertex3f(m_size, 0.0, m_size);
				glVertex3f(m_size, 0.0, -m_size);
			}
			glEnd();

			

			

			glTranslatef(0,m_size*2,0);
			glRotatef(m_angle,0,1,0);

			glTranslatef(m_size*2,0,0);
			glColor3f(0.2f, 0.5f, 0.0f);
			glutSolidSphere(m_size*0.5,20,20);
			
			glRotatef(m_angle, 0, 1, 0);
			glTranslatef(m_size,0,0);
			glColor3f(0.4f, 0.5f, 0.0f);
			glutSolidSphere(m_size*0.25, 20, 20);
		}
		glPopMatrix();
	}
	void Update() {
		(++m_angle) %= 360;
	}

	void Setpos(Vec3f pt) {
		m_pt = pt;
	}
	void SwitchNormalizeMode() {
		m_normalizemode = 1 - m_normalizemode;
	}


};

class Artifect {
private:
	Vec3f m_pt{};
	float m_size{ 100 };
	int m_angle{};
public:
	void Update() {
		(++m_angle) %= 360;
	}
	void Rander() {
		glPushMatrix();
		{
			glEnable(GL_BLEND);
			glDisable(GL_CULL_FACE);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glTranslatef(m_pt.x,m_pt.y,m_pt.z);
			glRotatef(m_angle,0,1,0);
			
			glColor4f(0.5,0.5,0.5,1.0);
			glutSolidCube(m_size*0.5);
			glRotatef(-m_angle, 0, 1, 0);

			glRotatef(45, 1,1, 1);
			glColor4f(1.0, 1.0, 0.5, 0.4);
			glRotatef(-m_angle, 1, 1, 0);
			glutSolidCube(m_size);
			

			glEnable(GL_CULL_FACE);
			glDisable(GL_BLEND);
		}
		glPopMatrix();


	}
	void Setpos(Vec3f pt) {
		m_pt = pt;
	}


};

class Ferris_Wheel {
private:
	Vec3f m_pt{};
	float m_size{ 100 };
	int m_angle{};
public:
	void Update() {
		(++m_angle) %= 360;
	}
	void Rander() {
		glPushMatrix();
		{

			glTranslatef(m_pt.x, m_pt.y, m_pt.z);
			
			glPushMatrix();
			{
				glTranslatef(0,-m_pt.y,0);

				glTranslatef(0,0,-m_size);
				glScalef(2,1,1);
				glutSolidCube(m_size*0.2);
				glTranslatef(0, 0, 2*m_size);
				glutSolidCube(m_size*0.2);
			}
			glPopMatrix();
			
			glTranslatef(0,m_size*0.2,0);


			

			glPushMatrix();
			{
				glRotatef(m_angle,0,0,1);

				glutSolidTorus(4, m_size, 50, 50);
				glPushMatrix();
				{
				for (int i = 0; i < 4; ++i) {
						glRotatef(45, 0, 0, 1);
						glPushMatrix();
						glScalef(m_size*2.5, 10, 5);
						glutSolidCube(1);
						glPopMatrix();
					}
				}
				glPopMatrix();

			glPushMatrix();
			{

				for (int i = 0; i < 8; ++i) {
					glRotatef(45, 0, 0, 1);
					glPushMatrix();
					{	
						glTranslatef(m_size,0,0);
						glPushMatrix();
						glRotatef(-45*(i+1)-m_angle, 0, 0, 1);
						glutSolidCube(m_size*0.5);
						glPopMatrix();
					}
					glPopMatrix();
				}

			}
			glPopMatrix();

			}
			glPopMatrix();


		}
		glPopMatrix();


	}
	void Setpos(Vec3f pt) {
		m_pt = pt;
	}



};

class Triangle {
private:
	Vec3f m_pt{};
	float m_size{ 128 };
	int m_angle{};
	int m_maxdepth{0};
	int m_tick{};
public:
	void Update() {
		m_tick++;
		if (m_tick > 50) {
			(++m_maxdepth) %= 5;
			m_tick = 0;
		}
		(++m_angle) %= 360;
	
	};

	void Rander() {

		glPushMatrix();
		{
			glTranslatef(m_pt.x,m_pt.y,m_pt.z);
			glRotatef(m_angle,0,1,0);

			glPushMatrix();
			{
				glTranslatef(0, 0, m_size);
				glRotatef(-45,1,0,0);
				RanderSurface();
				glRotatef(45, 1, 0, 0);
				glTranslatef(0, 0, -m_size * 2);
				glRotatef(45, 1, 0, 0);
				RanderSurface();
			}
			glPopMatrix();
			
			glRotatef(90,0,1,0);
			glPushMatrix();
			{
				glTranslatef(0, 0, m_size);
				glRotatef(-45, 1, 0, 0);
				RanderSurface();
				glRotatef(45, 1, 0, 0);
				glTranslatef(0, 0, -m_size * 2);
				glRotatef(45, 1, 0, 0);
				RanderSurface();
			}
			glPopMatrix();
			

			
		}
		glPopMatrix();
		



	}

	void RanderSurface() {

		Vec3f vertex1 = { m_size,0.0,0.0 };
		Vec3f vertex2 = { -m_size,0.0,0.0 };
		Vec3f vertex3 = { 0.0,m_size*1.42,0.0 };

		Vec3f d = vertex2 - vertex1;
		Vec3f e = vertex3 - vertex1;
		Vec3f f = Normalize(Cross(d, e));
		glNormal3f(f.x, f.y, f.z);
		glDisable(GL_CULL_FACE);
		RanderTriangle(vertex1, vertex2, vertex3, 0);
		glEnable(GL_CULL_FACE);
	}

	void RanderTriangle(Vec3f vertex1, Vec3f vertex2, Vec3f vertex3, int current_depth)
	{
		Vec3f next_vertex1;
		Vec3f next_vertex2;
		Vec3f next_vertex3;

		if (current_depth > m_maxdepth)
			return;

		
		if (current_depth == m_maxdepth) {
			glBegin(GL_TRIANGLES);
			glVertex3f(vertex1.x, vertex1.y, vertex1.z);
			glVertex3f(vertex2.x, vertex2.y, vertex2.z);
			glVertex3f(vertex3.x, vertex3.y, vertex3.z);
			glEnd();
		}
		
	
	


		next_vertex1.x = (vertex1.x + vertex2.x) * 0.5;
		next_vertex1.y = (vertex1.y + vertex2.y) * 0.5;
		next_vertex1.z = (vertex1.z + vertex2.z) * 0.5;
												 
		next_vertex3.x = (vertex2.x + vertex3.x) * 0.5;
		next_vertex3.y = (vertex2.y + vertex3.y) * 0.5;
		next_vertex3.z = (vertex2.z + vertex3.z) * 0.5;
												 
		next_vertex2.x = (vertex1.x + vertex3.x) * 0.5;
		next_vertex2.y = (vertex1.y + vertex3.y) * 0.5;
		next_vertex2.z = (vertex1.z + vertex3.z) * 0.5;

		RanderTriangle(next_vertex1, vertex1, next_vertex2, current_depth + 1);
		RanderTriangle(next_vertex1, vertex2, next_vertex3, current_depth + 1);
		RanderTriangle(next_vertex3, vertex3, next_vertex2, current_depth + 1);
	}
	
	void Setpos(Vec3f pt) {
		m_pt = pt;
	}

};

class Seasaw {
private:
	Vec3f m_pt{};
	float m_size{ 128 };
	int m_angle{};
	int m_maxdepth{ 0 };
	int m_tick{};
	bool is_snowman{true};
public:
	void Update() {
		m_tick++;
		if (m_tick > 50) {
			(++m_maxdepth) %= 5;
			m_tick = 0;
		}
		if (m_angle == 90)
			is_snowman = 1 - is_snowman;

		(++m_angle) %= 360;

	};

	void Rander() {

		glPushMatrix();
		{
			glTranslatef(m_pt.x, m_pt.y, m_pt.z);
			float angle = sin(m_angle*PI / 180.0)*m_size*0.5;
			float angle2 = cos(m_angle*PI / 180.0)*m_size*0.5;

			glTranslatef(-150,0,0);
			RandSeasaw(angle,1-is_snowman);
			glTranslatef(300, 0, 0);
			RandSeasaw(-angle,is_snowman);
		}
		glPopMatrix();
	}

	void RandSeasaw(float angle, bool snowman) {
		glPushMatrix();
		{
			glutSolidSphere(10, 10, 10);
			glRotatef(angle*0.5, 0, 0, 1);
			glPushMatrix();
			{	glRotatef(10, 1, 0, 0);
			glTranslatef(0, -50, 0);
			glRotatef(90, 1, 0, 0);

			glScalef(1, 1, 75);
			glutSolidTorus(1, 5, 20, 20);
			}
			glPopMatrix();

			glPushMatrix();
			{	glRotatef(-10, 1, 0, 0);
			glTranslatef(0, -50, 0);
			glRotatef(90, 1, 0, 0);

			glScalef(1, 1, 75);
			glutSolidTorus(1, 5, 20, 20);
			}
			glPopMatrix();


			glTranslatef(0, -250, 0);


			RandBase(snowman);
		
		
		
		}
		glPopMatrix();
	
	
	}
	
	void RandBase(bool snowman) {
	
		glPushMatrix();
		{
			glTranslatef(0,m_size,0);

			glPushMatrix();
			glScalef(m_size,10,m_size*0.5);
			glutSolidCube(1);
			glPopMatrix();

			if (snowman) {
				glColor3f(1.0, 1.0, 1.0);
				glTranslatef(0,20,0);
				glutSolidSphere(20,10,10);
				glTranslatef(0,20,0);
				glutSolidSphere(15, 10, 10);
			}
			
		}
		glPopMatrix();
	
	}

	void Setpos(Vec3f pt) {
		m_pt = pt;
	}



};
class Snow {
private:
	Vec3f m_pt{ };
public:
	Snow() {
		m_pt.x = rand() % (int)floor_size * 2 - floor_size;
		m_pt.y = floor_size;
		m_pt.z = rand() % (int)floor_size * 2 - floor_size;
	};
	Snow(Vec3f pt) {
		m_pt = pt;
	};
	void Update() {
		m_pt.y -= 1;
	
	};
	void Rander() {
	
		glPushMatrix();
		{
			glTranslatef(m_pt.x,m_pt.y,m_pt.z);
			for (int i = 0; i < 6; ++i) {
				glColor4f(1.0, 1.0, 1.0, 1.0);
				glRotatef(60,1,1,1);
				glutSolidCone(1,2,20,20);
			}
		}
		glPopMatrix();
	
	
	};

	Vec3f GetPt() const { return m_pt; }
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
//////////////////////////////////////////////////
void InitObjects();
void RanderSurface();

void DrawAxis();
void DrawFloor();

void DrawTriangle(Vec3f Position, Vec3f Size, int angle, Vec3f axis);
void DrawRactangle(Vec3f Position, Vec3f Size, int angle, Vec3f axis);
///////////////////////////////////////////
////////////////////////////////////////////
CCamera camera;

//Gate gate;
Artifect artifect;
Ferris_Wheel wheel;
Triangle triangle;
Seasaw seasaw;
list <Snow> snow;
float ambiant = 0.5;
float specular = 0.5;
float diffuse = 0.5;

bool light_0;
bool is_normal = true;
int lightangle = 0;
int snowtick = 0;

void main(int argc, char *argv[])
{
	//초기화 함수들
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(Window_Width, Window_Height); // 윈도우의 크기 지정
	glutCreateWindow("[2013182010김병진]Q31"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutKeyboardFunc(Keyboard); // 키보드 입력 콜백 함수
	glutTimerFunc(1, TimerFunction, 1);
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정

	InitObjects();

	glutMainLoop();


}
// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	GLfloat AmbientLight[] = { ambiant, ambiant, ambiant, 1.0f };
	GLfloat DiffuseLight[] = { diffuse, diffuse, diffuse, 1.0f };
	GLfloat SpecularLight[] = { specular, specular, specular, 1.0f };
	GLfloat lightPos[] = { cos(lightangle*PI/180.0f)*floor_size*0.75, floor_size/2, sin(lightangle*PI / 180.0f)*floor_size*0.75, 1.0f };
	GLfloat LightModel_Ambiant[] = {0.1,0.1,0.1,1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModel_Ambiant);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 0.0);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);
	GLfloat Ambient[] = { 0.5f, 0.5f, 1.0f, 1.0f };
	GLfloat Specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Specref);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 128);
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기
														// 색상 지정하고 사각형 그리기
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);

	if (is_normal)
		glEnable(GL_NORMALIZE);	else
		glDisable(GL_NORMALIZE);

	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	if (light_0)
		glEnable(GL_LIGHT0);
	else
		glDisable(GL_LIGHT0);


	glColor4f(1.0, 1.0, 1.0, 1.0f);



	camera.Rander();
	

	glPushMatrix();
	{
		glColor3f(1.0,0.0,0.0);
		
		glPushMatrix();
		{
			glTranslatef(cos(lightangle*PI/180.0f)*floor_size/2,floor_size/2, sin(lightangle*PI / 180.0f)*floor_size / 2);
			glutSolidCone(1,2,10,10);
		}
		glPopMatrix();

		

		DrawAxis();

		//////////////////<바닥>////////////////////
		DrawFloor();

		glColor4f(1.0, 1.0, 1.0, 1.0);
		glutWireCube(floor_size * 2);

		//pyramid[0].Rander();
		//pyramid[1].Rander();
		artifect.Rander();
		wheel.Rander();
		triangle.Rander();
		seasaw.Rander();
		for (auto &p : snow) {
			p.Rander();
		}


		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, texture_object[0]);

		glPushMatrix();
		{
			glTranslated(0, 0, floor_size);
			RanderSurface();
		}
		glPopMatrix();



		glDisable(GL_TEXTURE_2D);

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
	gluPerspective(60.0f, w / h, 1.0, 10000.0); // fovy :: 최대 180(넘어가면 거꾸로 보여), 작을수록 크게 보임
											   //glTranslatef(0.0, 0.0, -300.0);

											   //glOrtho(-400.0, 400, -400.0, 400, -400.0, 400.0); // x축 최소,최대, y축 최소,최대, z축 최소 최대 // 직각투영




	glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y)
{
	{

		if (key == 'l' || key == 'L') {
			camera.HandlePosition(Camera_Speed, { 1,0,0 });
		}
		if (key == 'j' || key == 'J') {
			camera.HandlePosition(-Camera_Speed, { 1,0,0 });
		}
		if (key == 'i' || key == 'I') {
			camera.HandlePosition(Camera_Speed, { 0,1,0 });
		}
		if (key == 'k' || key == 'K') {
			camera.HandlePosition(-Camera_Speed, { 0,1,0 });
		}


		if (key == '1') {
			light_0 = 1 - light_0;
		}

		if (key == 'a') {;
			ambiant = max(0, ambiant - 0.1);
		}
		if (key == 'A') {
			ambiant = min(1, ambiant + 0.1);
		}
		if (key == 's') {
			specular = max(0, specular - 0.1);
		}
		if (key == 'S') {
			specular = min(1, specular + 0.1);
		}
		if (key == 'd') {
			diffuse = max(0, diffuse - 0.1);
		}
		if (key == 'D') {
			diffuse = min(1, diffuse + 0.1);
		}
		if (key == 'z' || key == 'Z') {
			is_normal = 1 - is_normal;
		}

		if (key == '+') {
			camera.HandleDistance(10);
		}
		if (key == '-') {
			camera.HandleDistance(-10);
		}
		if (key == 'r' || key == 'R') {
			camera.ResetPos();
		}
		if (key == 'm' || key == 'M') {
			snow.push_front(Snow());
		}
	}



	if (key == 'p' || key == 'P') {
		exit(0);
	}	// 종료
}

void Mouse(int button, int state, int x, int y)
{

}

void TimerFunction(int value)
{
	snowtick++;
	camera.Update();

	artifect.Update();
	wheel.Update();
	triangle.Update();
	seasaw.Update();
	if (snowtick % 2 == 0) {
		snow.push_front(Snow());
	}

	for (auto &p : snow) {
		p.Update();
	}

	snow.remove_if([](auto& data) -> bool {
		return (data.GetPt().y <= 0);
	});

	(++lightangle) %= 360;

	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(1, TimerFunction, 1); // 타이머함수 재 설정
}

void InitObjects()
{
	srand((unsigned)time(nullptr));
	wheel.Setpos({ floor_size / 2, 100, 0 });
	artifect.Setpos({ -floor_size / 2, 100, 0 });
	triangle.Setpos({0, 0,  -floor_size / 2 });
	seasaw.Setpos({ 0, floor_size/2 ,  floor_size / 2 });

	glGenTextures(6, texture_object);
	glBindTexture(GL_TEXTURE_2D, texture_object[0]);
	TexBits = LoadDIBitmap("Metal_1.bmp", &m_bitInfo[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1024, 1024, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TexBits);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_REPLACE);
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
		glColor4f(0.2, 0.5, 0.2, 1.0f);
		glBegin(GL_QUADS);
		if(is_normal)glNormal3f(0,1,0);

		int grid = 200;
		for (int i = 0; i < grid; ++i) {
			for (int j = 0; j < grid; ++j) {
				glVertex3d(i*floor_size*2 / grid - floor_size, 0,
					j*floor_size * 2 / grid - floor_size);
				glVertex3d(i*floor_size * 2 / grid - floor_size, 0,
					(j+1)*floor_size * 2 / grid - floor_size);
				glVertex3d((i+1)*floor_size * 2 / grid - floor_size, 0,
					(j+1)*floor_size * 2 / grid - floor_size);
				glVertex3d((i+1)*floor_size * 2 / grid - floor_size, 0,
					j*floor_size * 2 / grid - floor_size);
			}
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

void RanderSurface()
{

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-floor_size, floor_size, 0.0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(floor_size, floor_size, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(floor_size, -floor_size, 0.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-floor_size, -floor_size, 0.0);
	glEnd();


}
