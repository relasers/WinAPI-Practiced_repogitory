#pragma once
#include<iostream>
#include<gl/glut.h>
#include <list>
#include <Windows.h>
#include <chrono>
#include <cmath>
#include "Vector3D.h"
#include "Camera.h"
#include "Firstcamera.h"
#include "Player.h"
#include "CombatDrone.h"
#include "HexTechTower.h"
#include"Bitmap.h"
using namespace std;

constexpr int Window_Width = 800;
constexpr int Window_Height = 800;

constexpr float axis_size = 800.0;
constexpr float floor_size = 3200.0;
constexpr int floor_grid = 100;

constexpr int number_of_obstacle = 15;
constexpr int max_pt = 100;
constexpr float railradius = 32;
constexpr int min_height = 50;
constexpr int max_height = 2400;

constexpr float tension = 0.02;
constexpr float stair = 50;

enum W_mode{
	None,Rainy,Snowy
};

class Bullet{
private:
	Vec3f m_pt{};
	Vec3f m_dir{};
	float m_speed{64};
	bool isDead = false;
public:
	Bullet() = default;
	Bullet(Vec3f pt, Vec3f dir) {
		m_pt = pt;
		m_dir = dir;
	}
	void Update() {
		m_pt += m_dir*m_speed;
	};
	void Rander() {
	
		glPushMatrix();
		{
			glTranslatef(m_pt.x,m_pt.y,m_pt.z);
			glColor3f(1.0,1.0,1.0);
			glutSolidSphere(32,10,10);
		}
		glPopMatrix();

	}
	Vec3f GetPt() { return m_pt; }
	void SetDead() { isDead = true; }
	bool IsDead() { return isDead; }
};


class Whether {
private:
	Vec3f m_pt{};
	float m_speed{16};
	bool is_snow{ true };
public:
	Whether() {
		m_pt.x = rand() % (int)floor_size * 2 - floor_size;
		m_pt.y = 120;
		m_pt.z = rand() % (int)floor_size * 2 - floor_size;
	};
	Whether(bool snow) {
		m_pt.x = rand() % (int)floor_size * 2 - floor_size;
		m_pt.y = floor_size;
		m_pt.z = rand() % (int)floor_size * 2 - floor_size;

		is_snow = snow;
	};
	Whether(Vec3f pt) {
		m_pt = pt;
	};
	Whether(Vec3f pt,bool snow) {
		m_pt = pt;
		is_snow = snow;
	};


	void Update() {
		m_pt.y -= m_speed;
		if(!is_snow) m_pt.y -= m_speed*2;

	};
	void Rander() {

		glPushMatrix();
		{
			glTranslatef(m_pt.x, m_pt.y, m_pt.z);
			if(is_snow)
			for (int i = 0; i < 6; ++i) {
				glColor4f(1.0, 1.0, 1.0, 1.0);
				glRotatef(60, 1, 1, 1);
				glutSolidCone(10, 10, 20, 20);
			}
			if (!is_snow) {
				glColor4f(0.0, 0.0, 1.0, 1.0);
				
				
				glRotatef(90, 1, 0, 0);

				glScalef(1, 1, 20);
				glutSolidTorus(1, 5, 5, 5);
			}
		}
		glPopMatrix();


	};

	Vec3f GetPt() const { return m_pt; }
};

class Particle {
private:
	Vec3f m_pt;
	Vec3f m_direction;
	float m_speed;
	int m_lifetime{ 100 };
public:
	Particle(Vec3f pt) {
		m_pt = pt;
		Vec3f dir{ -floor_size + float(rand() % (int)floor_size * 2),-floor_size + float(rand() % (int)floor_size * 2),-floor_size + float(rand() % (int)floor_size * 2) };
		m_direction = dir - m_pt;
		Normalize(m_direction);
		m_speed = 1 + rand() % 10;
	}
	void Rander() {
		glPushMatrix();
		{
			glTranslatef(m_pt.x, m_pt.y, m_pt.z);
			glColor3f(rand() % 10 * 0.1f, rand() % 10 * 0.1f, rand() % 10 * 0.1f);
			glRotatef(rand() % 360, 1, 1, 1);
			glutWireCube(m_lifetime*0.6);
			glutSolidSphere(m_lifetime*0.3, 6, 6);
		}
		glPopMatrix();
	}
	void Update() {
		m_lifetime--;
		m_pt += m_direction*m_speed;
		m_speed = max(1, m_speed - 0.01);
	}

	int GetLife() { return m_lifetime; }
};

//////////////<기본 함수>//////////////////////////
GLvoid RanderScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void SpecialInput(int key, int x, int y);
void Mouse(int button, int state, int x, int y);
void MoveMouse(int x, int y);
void TimerFunction(int value);

void RanderCurvedFloor();
void RanderRail();

void MoveCart();

bool CheckCross(Vec3f p1_1, Vec3f p1_2, Vec3f p2_1, Vec3f p2_2);
void Init();
void DrawAxis();
void DrawFloor();
//////////////////////////////////////////////////

Vec3f ctrlpt[max_pt];
int num_pt = 0;

//
bool is_selected = false;
int pick_index = -1;


// cameras
CFirstcamera firstcamera;
CCamera thirdcamera;

//coaster
CPlayer head;
CCombatDrone container[3];

int headindex = 0;
float headstair = 0;

int containerindex[3]{};
float containerstair[3]{};

list<Bullet> bullet;


list<Whether> whether;
int whether_mode = W_mode::None;
int whether_tick{};

list<Particle> part;

// obstacles
list<CHexTechTower> obstacle;

float currheight = min_height;
bool orthomode = true;
bool is_firstview = false;



/////////////////////////////////////////////
float floor_points[floor_grid][floor_grid][3]{};

GLuint texture_object[3];
GLubyte * TexBits;
BITMAPINFO *m_bitInfo[3];





/////////////////////////////////////////////




void main(int argc, char *argv[])
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(Window_Width, Window_Height); // 윈도우의 크기 지정
	glutCreateWindow("[2013182010 김병진]Roller_Coaster"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(RanderScene); // 출력 함수의 지정
	glutKeyboardFunc(Keyboard); // 키보드 입력 콜백 함수
	glutMouseFunc(Mouse);
	glutMotionFunc(MoveMouse);
	glutTimerFunc(1, TimerFunction, 1);
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정

	Init();

	glutMainLoop();


}

GLvoid RanderScene(GLvoid)
{
	switch (whether_mode) {
	case W_mode::None:
		glClearColor(0.6f, 0.6f, 0.8f, 1.0f); // 바탕색 지정
		break;
	case W_mode::Rainy:
		glClearColor(0.0f, 0.0f, 0.5f, 1.0f); // 바탕색 지정
		break;
	case W_mode::Snowy:
		glClearColor(0.3f, 0.3f, 0.4f, 1.0f); // 바탕색 지정
		break;


	}
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기
														// 색상 지정하고 사각형 그리기
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);	glEnable(GL_COLOR_MATERIAL);	glShadeModel(GL_SMOOTH);	GLfloat AmbientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };


	switch (whether_mode) {
	case W_mode::None:
		break;
	case W_mode::Rainy:
		AmbientLight[0] = { 0.01f };
		AmbientLight[1] = { 0.01f };
		AmbientLight[2] = { 0.1f };
		break;
	case W_mode::Snowy:
		AmbientLight[0] = { 0.1f };
		AmbientLight[1] = { 0.3f };
		AmbientLight[2] = { 0.3f };
		break;


	}


	GLfloat DiffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat SpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat lightPos[] = { thirdcamera.GetEye().x, thirdcamera.GetEye().y, thirdcamera.GetEye().z, 1.0 };		glEnable(GL_LIGHTING);	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);	glEnable(GL_LIGHT0);	GLfloat spotAmbientLight[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat spotDiffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat spotSpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat spotlightPos[] = { head.Getpt().x, head.Getpt().y+240,  head.Getpt().z, 1.0 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, spotAmbientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, spotDiffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, spotSpecularLight);
	glLightfv(GL_LIGHT1, GL_POSITION, spotlightPos);
	GLfloat spot_dir[] = { 0, -1, 0 , 1.0f };
	GLfloat spot_cutoff[] = { 40.0f };
	GLfloat spot_exponent[] = { 3.0f };
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_dir);
	glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, spot_cutoff);
	glLightfv(GL_LIGHT1, GL_SPOT_EXPONENT, spot_exponent);
	glEnable(GL_LIGHT1);

	if (!orthomode) {
		if(!is_firstview)
			thirdcamera.Rander();
		if (is_firstview)
			firstcamera.Rander();
	}

	glPushMatrix();
	{
		glLineWidth(1.0);

		DrawAxis();
		//RanderCurvedFloor();
		DrawFloor();
		glColor4f(1.0, 0.0, 0.0, 1.0);
		glutWireCube(2048);
		glColor4f(1.0, 1.0, 1.0, 1.0);

		for (auto &p : obstacle) {
			p.Rander();
		}

		for (auto &p : whether) {
			p.Rander();
		}
		for (auto &p : part) p.Rander();

		glPointSize(6.0);
		glLineWidth(3.0);
		glColor3f(1.0, 0.0, 1.0);
		glBegin(GL_POINTS);
		for (int i = 0; i < num_pt; i++)
			glVertex3f(ctrlpt[i].x, ctrlpt[i].y, ctrlpt[i].z);
		glEnd();


		if (num_pt > 1) {
			Vec3f CtrlPt{};
			Vec3f NextPt{};
			Vec3f DirVector{};
		
			glColor3f(1., 0., 0.);
			glBegin(GL_LINES); 

			

			CtrlPt = ctrlpt[0];
			NextPt = ctrlpt[1];
			DirVector = NextPt - CtrlPt;
			Normalize(DirVector);
			DirVector.y = 0;
			float temp = DirVector.x;
			DirVector.x = DirVector.z;
			DirVector.z = -temp;


			glVertex3f(ctrlpt[0].x + DirVector.x*railradius, ctrlpt[0].y, ctrlpt[0].z + DirVector.z*railradius);
			glVertex3f(ctrlpt[1].x + DirVector.x*railradius, ctrlpt[1].y, ctrlpt[1].z + DirVector.z*railradius);
			glVertex3f(ctrlpt[0].x - DirVector.x*railradius, ctrlpt[0].y, ctrlpt[0].z - DirVector.z*railradius);
			glVertex3f(ctrlpt[1].x - DirVector.x*railradius, ctrlpt[1].y, ctrlpt[1].z - DirVector.z*railradius);
			CtrlPt = ctrlpt[num_pt - 2];
			NextPt = ctrlpt[num_pt - 1];
			DirVector = NextPt - CtrlPt;
			Normalize(DirVector);
			DirVector.y = 0;
			temp = DirVector.x;
			DirVector.x = DirVector.z;
			DirVector.z = -temp;

			glVertex3f(ctrlpt[num_pt - 2].x + DirVector.x*railradius, ctrlpt[num_pt - 2].y, ctrlpt[num_pt - 2].z + DirVector.z*railradius);
			glVertex3f(ctrlpt[num_pt - 1].x + DirVector.x*railradius, ctrlpt[num_pt - 1].y, ctrlpt[num_pt - 1].z + DirVector.z*railradius);
			glVertex3f(ctrlpt[num_pt - 2].x - DirVector.x*railradius, ctrlpt[num_pt - 2].y, ctrlpt[num_pt - 2].z - DirVector.z*railradius);
			glVertex3f(ctrlpt[num_pt - 1].x - DirVector.x*railradius, ctrlpt[num_pt - 1].y, ctrlpt[num_pt - 1].z - DirVector.z*railradius);

			glEnd();

			glPushMatrix();
			{
				glTranslatef(ctrlpt[num_pt - 2].x - (ctrlpt[num_pt - 2].x - ctrlpt[num_pt - 1].x)*0.5, 
					ctrlpt[num_pt - 2].y - (ctrlpt[num_pt - 2].y - ctrlpt[num_pt - 1].y)*0.5, 
					ctrlpt[num_pt - 2].z - (ctrlpt[num_pt - 2].z - ctrlpt[num_pt - 1].z)*0.5);
				float angle = atan2(ctrlpt[num_pt - 2].x - ctrlpt[num_pt - 1].x, ctrlpt[num_pt - 2].z - ctrlpt[num_pt - 1].z) / PI*180.0;
				float angle2 = atan2(ctrlpt[num_pt - 2].y - ctrlpt[num_pt - 1].y, ctrlpt[num_pt - 2].x - ctrlpt[num_pt - 1].x) / PI*180.0;
				float angle3 = atan2(ctrlpt[num_pt - 2].y - ctrlpt[num_pt - 1].y, ctrlpt[num_pt - 2].z - ctrlpt[num_pt - 1].z) / PI*180.0;
				float length = sqrt(
					fabs(ctrlpt[num_pt - 2].z - ctrlpt[num_pt - 1].z)*fabs(ctrlpt[num_pt - 2].z - ctrlpt[num_pt - 1].z) +
					fabs(ctrlpt[num_pt - 2].x - ctrlpt[num_pt - 1].x)*fabs(ctrlpt[num_pt - 2].x - ctrlpt[num_pt - 1].x)
					)*0.5;
				glRotatef(angle,0,1,0);
				if(fabs(ctrlpt[num_pt - 2].x - ctrlpt[num_pt - 1].x) <fabs(ctrlpt[num_pt - 2].z - ctrlpt[num_pt - 1].z) )
					glRotatef(angle3, 1, 0, 0);
				else
					glRotatef(angle2, 1, 0, 0);
				glScalef(1, 1, length);
				glutSolidTorus(1, 128, 10, 10);
			}
			glPopMatrix();
			
		
		}

		if (num_pt > 3)
		{
			RanderRail();
		}


		head.Rander();
		for (int i = 0; i < 3; ++i) {
			container[i].Rander();
		}

		for (auto &p : bullet) {
			p.Rander();
		}



		if (!orthomode) {
		

			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);
			glEnable(GL_TEXTURE_2D);

			glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

			switch (whether_mode) {
			case W_mode::None:
				glBindTexture(GL_TEXTURE_2D, texture_object[0]);
				break;
			case W_mode::Rainy:
				glBindTexture(GL_TEXTURE_2D, texture_object[1]);
				break;
			case W_mode::Snowy:
				glBindTexture(GL_TEXTURE_2D, texture_object[2]);
				break;
			}			
			
			glutSolidSphere(floor_size*4,50,50);

			glDisable(GL_TEXTURE_GEN_S);
			glDisable(GL_TEXTURE_GEN_T);
			glDisable(GL_TEXTURE_2D);
		
		}




	}
	glPopMatrix();

	glutSwapBuffers(); // 화면에 출력하기 (glflush효과가 있다.)
}

void TimerFunction(int value)
{
	(++whether_tick) %= 10000;

	if (whether_tick % 1 == 0) {
	
		switch (whether_mode) {
		case W_mode::None:
			break;
		case W_mode::Rainy:
			whether.push_back(Whether(false));
			break;
		case W_mode::Snowy:
			whether.push_back(Whether(true));
			break;
		
		
		}
	
	}


	if(!orthomode)
	thirdcamera.Update();

	for (auto &p : obstacle) {
		p.Update();
	}
	if(num_pt > 2)
	MoveCart();
	head.Update();
	for (int i = 0; i < 3; ++i) {
		container[i].Update();
	}

	for (auto &p : bullet) {
		p.Update();

		for (auto &x : obstacle) {

			float dx = p.GetPt().x - x.GetPt().x;
			float dy = p.GetPt().y - x.GetPt().y;
			float dz = p.GetPt().z - x.GetPt().z;
			float hit = 300;

			if (dx*dx + dy*dy + dz*dz < hit*hit) {
				p.IsDead();
				part.push_back(Particle(p.GetPt()));
			}
				
		
		}

	}

	bullet.remove_if([](auto& data) -> bool {
		return (data.IsDead());
	});

	for (auto &p : whether) {
		p.Update();
	}
	whether.remove_if([](auto& data) -> bool {
		return (data.GetPt().y <= 0);
	});

	for (auto &p : part) p.Update();
	part.remove_if([](auto& data) -> bool {
		return (data.GetLife() <= 0);
	});

	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(1, TimerFunction, 1); // 타이머함수 재 설정
}

void Keyboard(unsigned char key, int x, int y)
{
	if(!orthomode)
		thirdcamera.KeyInput(key, x, y);

	if (key == 'q' || key == 'Q') {
		currheight = min(currheight+railradius,max_height);
		cout << currheight << endl;
	}

	if (key == 'a' || key == 'A') {
		currheight = max(min_height,currheight- railradius);
		cout << currheight << endl;
	}

	if (key == 'z' || key == 'Z') {
		orthomode = false;
		Reshape(Window_Width,Window_Height);
	}

	if(!orthomode)
	if (key == 'x' || key == 'X') {
		is_firstview = 1 - is_firstview;
	}
	if (key == 'c' || key == 'C') {
		bullet.push_back(Bullet(head.Getpt(),head.GetDir()));
	}
	if (key == 'r' || key == 'R') {
		whether_mode = W_mode::None;
	}
	if (key == 't' || key == 'T') {
		whether_mode = W_mode::Rainy;
	}
	if (key == 'y' || key == 'Y') {
		whether_mode = W_mode::Snowy;
	}
}

void Mouse(int button, int state, int x, int y)
{
	if (orthomode)
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (num_pt < max_pt) {
		
		
			ctrlpt[num_pt].x = (x * 8 - floor_size);
			ctrlpt[num_pt].y = currheight;
			ctrlpt[num_pt].z = (y * 8 - floor_size);

			for (auto &p : obstacle) {

				if (p.CollisionCheck(ctrlpt[num_pt])) return;

				if (num_pt - 1 != -1) {

					Vec3f target = ctrlpt[num_pt-1];
					Vec3f currpt = ctrlpt[num_pt];

					for (auto &p : obstacle) {
						Vec3f lt = p.GetPt();
						Vec3f lb = p.GetPt();
						Vec3f rt = p.GetPt();
						Vec3f rb = p.GetPt();

						lt += {-p.Getradius() * 2, 0, p.Getradius()*3};
						lb += {-p.Getradius() * 2, 0, -p.Getradius() * 3};
						rt += {p.Getradius() * 2, 0, p.Getradius() * 3};
						rb += {p.Getradius() * 2, 0, -p.Getradius() * 3};

						if (CheckCross(target, currpt, lt, lb)) return;
						if (CheckCross(target, currpt, lb, rb)) return;
						if (CheckCross(target, currpt, rb, rt)) return;
						if (CheckCross(target, currpt, rt, lt)) return;
					}
					



				}
			}

			num_pt++;
		
		
		}
		return;
	}
	if (orthomode)
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		for (int i = 2; i < num_pt; i++)
			if (fabs((x * 8 - floor_size) - ctrlpt[i].x) < 100  &&  fabs((y * 8 - floor_size) - ctrlpt[i].z) < 100)
			{
				pick_index = i;
				is_selected = true;
				glutPostRedisplay();
				return;
			} 
		is_selected = false;
	}

	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		is_selected = false;
	}

	glutPostRedisplay();
}

void MoveMouse(int x, int y)
{
	if (is_selected && pick_index != -1) {

		Vec3f savept = ctrlpt[pick_index];

		ctrlpt[pick_index].x = (x * 8 - floor_size);
		ctrlpt[pick_index].z = (y * 8 - floor_size);
////////////////////////////////////////////////////////////////////////////
		for (auto &p : obstacle) {

			if (p.CollisionCheck(ctrlpt[pick_index])) {
				ctrlpt[pick_index] = savept;
				return;
			}

			{
				Vec3f target = ctrlpt[pick_index - 1];
				Vec3f currpt = ctrlpt[pick_index];

				Vec3f lt = p.GetPt();
				Vec3f lb = p.GetPt();
				Vec3f rt = p.GetPt();
				Vec3f rb = p.GetPt();

				lt += {-p.Getradius() * 2, 0, p.Getradius() * 3};
				lb += {-p.Getradius() * 2, 0, -p.Getradius() * 3};
				rt += {p.Getradius() * 2, 0, p.Getradius() * 3};
				rb += {p.Getradius() * 2, 0, -p.Getradius() * 3};

				if (CheckCross(target, currpt, lt, lb) ||
					CheckCross(target, currpt, lb, rb) ||
					CheckCross(target, currpt, rb, rt) ||
					CheckCross(target, currpt, rt, lt)
					) {
					ctrlpt[pick_index] = savept;
					return;
				}
			}

			if(pick_index+1 < num_pt)
			{
				Vec3f target = ctrlpt[pick_index];
				Vec3f currpt = ctrlpt[pick_index+1];

				Vec3f lt = p.GetPt();
				Vec3f lb = p.GetPt();
				Vec3f rt = p.GetPt();
				Vec3f rb = p.GetPt();

				lt += {-p.Getradius() * 2, 0, p.Getradius() * 3};
				lb += {-p.Getradius() * 2, 0, -p.Getradius() * 3};
				rt += {p.Getradius() * 2, 0, p.Getradius() * 3};
				rb += {p.Getradius() * 2, 0, -p.Getradius() * 3};

				if (CheckCross(target, currpt, lt, lb) ||
					CheckCross(target, currpt, lb, rb) ||
					CheckCross(target, currpt, rb, rt) ||
					CheckCross(target, currpt, rt, lt)
					) {
					ctrlpt[pick_index] = savept;
					return;
				}
			}
		}
//////////////////////////////////////////////////////////////
	}
}



GLvoid Reshape(int w, int h)
{
	//////<뷰포트 변환 설정>////////
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);



	if (!orthomode) {
		/////<투영 행렬스택 재설정>//////

		glLoadIdentity();
		///////////<원근투영>////////////////////////
		gluPerspective(60.0f, w / h, 1.0, 16000.0); // fovy :: 최대 180(넘어가면 거꾸로 보여), 작을수록 크게 보임
												   //glTranslatef(0.0, 0.0, -300.0);
												   //glOrtho(-400.0, 400, -400.0, 400, -400.0, 400.0); // x축 최소,최대, y축 최소,최대, z축 최소 최대 // 직각투영


	}

	if (orthomode) {
		glLoadIdentity();
		glRotatef(-90,1,0,0);
		glOrtho(-floor_size, floor_size, -1, floor_size*3, -floor_size, floor_size);
	}


	glMatrixMode(GL_MODELVIEW);
}

void Init()
{
	srand((unsigned)time(nullptr));
	for (int i = 0; i < number_of_obstacle; ++i) {
		obstacle.push_front(CHexTechTower({ -floor_size + rand() % (int)floor_size * 2 ,256 ,-floor_size + rand() % (int)floor_size * 2 }));
	}

	bool first = true;
	bool second = true;

	while (first) {
		first = false;
		ctrlpt[0] = { -floor_size + rand() % (int)floor_size * 2,(float)min_height,-floor_size + rand() % (int)floor_size * 2 };
		for (auto &p : obstacle) {
			if (p.CollisionCheck(ctrlpt[0])) first = true;
		}
	}

	while (second) {
		second = false;
		ctrlpt[1] = ctrlpt[0];

		if(ctrlpt[1].z + floor_size*0.3 < floor_size)
			ctrlpt[1].z += floor_size*0.3;
		else
			ctrlpt[1].z -= floor_size*0.3;

		for (auto &p : obstacle) {
			if (num_pt - 1 != -1) {

				Vec3f target = ctrlpt[0];
				Vec3f currpt = ctrlpt[1];

				for (auto &p : obstacle) {
					Vec3f lt = p.GetPt();
					Vec3f lb = p.GetPt();
					Vec3f rt = p.GetPt();
					Vec3f rb = p.GetPt();

					lt += {-p.Getradius() * 2, 0, p.Getradius() * 3};
					lb += {-p.Getradius() * 2, 0, -p.Getradius() * 3};
					rt += {p.Getradius() * 2, 0, p.Getradius() * 3};
					rb += {p.Getradius() * 2, 0, -p.Getradius() * 3};

					if (CheckCross(target, currpt, lt, lb)) second = true;
					if (CheckCross(target, currpt, lb, rb)) second = true;
					if (CheckCross(target, currpt, rb, rt)) second = true;
					if (CheckCross(target, currpt, rt, lt)) second = true;
				}
			}
		}
	}
	num_pt = 2;
	
	headindex = 0;
	headstair = 60;

	for (int i = 0; i < 3; ++i) {
		containerindex[i] = 0;
		containerstair[i] = 20 * i;
	}

/////////////////////////////////////////////////////////////////////

	for (int i = 0; i < floor_grid; ++i) {
		for (int j = 0; j < floor_grid; ++j) {
		
			floor_points[i][j][0] = -floor_size + i*(floor_size * 2 / floor_grid);
			floor_points[i][j][1] = 100;
			floor_points[i][j][2] = -floor_size + j*(floor_size * 2 / floor_grid);
		}
	}
	

	glGenTextures(3, texture_object);

	glBindTexture(GL_TEXTURE_2D, texture_object[0]);
	TexBits = LoadDIBitmap("Clear_sky.bmp", &m_bitInfo[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1024, 1024, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TexBits);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, texture_object[1]);
	TexBits = LoadDIBitmap("Metal_2.bmp", &m_bitInfo[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1024, 1024, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TexBits);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, texture_object[2]);
	TexBits = LoadDIBitmap("Cloudy.bmp", &m_bitInfo[2]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1024, 1024, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TexBits);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);



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
		glNormal3f(0, 1, 0);

		int grid = 400;
		for (int i = 0; i < grid; ++i) {
			for (int j = 0; j < grid; ++j) {
				glVertex3d(i*floor_size * 2 / grid - floor_size, 0,
					j*floor_size * 2 / grid - floor_size);
				glVertex3d(i*floor_size * 2 / grid - floor_size, 0,
					(j + 1)*floor_size * 2 / grid - floor_size);
				glVertex3d((i + 1)*floor_size * 2 / grid - floor_size, 0,
					(j + 1)*floor_size * 2 / grid - floor_size);
				glVertex3d((i + 1)*floor_size * 2 / grid - floor_size, 0,
					j*floor_size * 2 / grid - floor_size);
			}
		}


		glEnd();

	}
	glPopMatrix();
}

void RanderCurvedFloor() {

	glMap2f(GL_MAP2_VERTEX_3,
		0.0, 1.0, 100, 100,
		0.0, 1.0, 10000, 100,
		&floor_points[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	// 그리드를 이용한 곡면 드로잉
	glMapGrid2f(10, 0.0, 1.0,
		10, 0.0, 1.0);

	// 선을 이용하여 그리드 연결
	glEvalMesh2(GL_LINE, 0, 10, 0, 10);
	glDisable(GL_MAP2_VERTEX_3);
	
}

void RanderRail()
{
	glColor3f(1, 0., 1.);
	glBegin(GL_LINE_STRIP);
	for (int i = 1; i < num_pt - 2; i++)
	{
		Vec3f CtrlPt{};
		Vec3f NextPt{};

		Vec3f DirVector{};


		for (int k = 0; k < stair; k++) {
			float t = k*tension;
			float u = (k + 1)*tension;
			CtrlPt.x = ctrlpt[i].x
				+ t*0.5*(-ctrlpt[i - 1].x + ctrlpt[i + 1].x)
				+ t*t*(ctrlpt[i - 1].x - 2.5*ctrlpt[i].x + 2 * ctrlpt[i + 1].x - 0.5*ctrlpt[i + 2].x)
				+ t*t*t*(-0.5*ctrlpt[i - 1].x + 1.5*ctrlpt[i].x - 1.5*ctrlpt[i + 1].x + 0.5*ctrlpt[i + 2].x);

			CtrlPt.y = ctrlpt[i].y
				+ t*0.5*(-ctrlpt[i - 1].y + ctrlpt[i + 1].y)
				+ t*t*(ctrlpt[i - 1].y - 2.5*ctrlpt[i].y + 2 * ctrlpt[i + 1].y - 0.5*ctrlpt[i + 2].y)
				+ t*t*t*(-0.5*ctrlpt[i - 1].y + 1.5*ctrlpt[i].y - 1.5*ctrlpt[i + 1].y + 0.5*ctrlpt[i + 2].y);

			CtrlPt.z = ctrlpt[i].z
				+ t*0.5*(-ctrlpt[i - 1].z + ctrlpt[i + 1].z)
				+ t*t*(ctrlpt[i - 1].z - 2.5*ctrlpt[i].z + 2 * ctrlpt[i + 1].z - 0.5*ctrlpt[i + 2].z)
				+ t*t*t*(-0.5*ctrlpt[i - 1].z + 1.5*ctrlpt[i].z - 1.5*ctrlpt[i + 1].z + 0.5*ctrlpt[i + 2].z);

			NextPt.x = ctrlpt[i].x
				+ u*0.5*(-ctrlpt[i - 1].x + ctrlpt[i + 1].x)
				+ u*u*(ctrlpt[i - 1].x - 2.5*ctrlpt[i].x + 2 * ctrlpt[i + 1].x - 0.5*ctrlpt[i + 2].x)
				+ u*u*u*(-0.5*ctrlpt[i - 1].x + 1.5*ctrlpt[i].x - 1.5*ctrlpt[i + 1].x + 0.5*ctrlpt[i + 2].x);

			NextPt.y = ctrlpt[i].y
				+ u*0.5*(-ctrlpt[i - 1].y + ctrlpt[i + 1].y)
				+ u*u*(ctrlpt[i - 1].y - 2.5*ctrlpt[i].y + 2 * ctrlpt[i + 1].y - 0.5*ctrlpt[i + 2].y)
				+ u*u*u*(-0.5*ctrlpt[i - 1].y + 1.5*ctrlpt[i].y - 1.5*ctrlpt[i + 1].y + 0.5*ctrlpt[i + 2].y);

			NextPt.z = ctrlpt[i].z
				+ u*0.5*(-ctrlpt[i - 1].z + ctrlpt[i + 1].z)
				+ u*u*(ctrlpt[i - 1].z - 2.5*ctrlpt[i].z + 2 * ctrlpt[i + 1].z - 0.5*ctrlpt[i + 2].z)
				+ u*u*u*(-0.5*ctrlpt[i - 1].z + 1.5*ctrlpt[i].z - 1.5*ctrlpt[i + 1].z + 0.5*ctrlpt[i + 2].z);

			DirVector = NextPt - CtrlPt;
			Normalize(DirVector);
			DirVector.y = 0;
			float temp = DirVector.x;
			DirVector.x = DirVector.z;
			DirVector.z = -temp;


			glVertex3f(CtrlPt.x + DirVector.x*railradius, max(min_height, CtrlPt.y), CtrlPt.z + DirVector.z*railradius);
		}
	}
	glEnd();
	///////////////////
	glBegin(GL_LINE_STRIP);
	for (int i = 1; i < num_pt - 2; i++)
	{
		Vec3f CtrlPt{};
		Vec3f NextPt{};

		Vec3f DirVector{};


		for (int k = 0; k < stair; k++) {
			float t = k*tension;
			float u = (k + 1)*tension;
			CtrlPt.x = ctrlpt[i].x
				+ t*0.5*(-ctrlpt[i - 1].x + ctrlpt[i + 1].x)
				+ t*t*(ctrlpt[i - 1].x - 2.5*ctrlpt[i].x + 2 * ctrlpt[i + 1].x - 0.5*ctrlpt[i + 2].x)
				+ t*t*t*(-0.5*ctrlpt[i - 1].x + 1.5*ctrlpt[i].x - 1.5*ctrlpt[i + 1].x + 0.5*ctrlpt[i + 2].x);

			CtrlPt.y = ctrlpt[i].y
				+ t*0.5*(-ctrlpt[i - 1].y + ctrlpt[i + 1].y)
				+ t*t*(ctrlpt[i - 1].y - 2.5*ctrlpt[i].y + 2 * ctrlpt[i + 1].y - 0.5*ctrlpt[i + 2].y)
				+ t*t*t*(-0.5*ctrlpt[i - 1].y + 1.5*ctrlpt[i].y - 1.5*ctrlpt[i + 1].y + 0.5*ctrlpt[i + 2].y);

			CtrlPt.z = ctrlpt[i].z
				+ t*0.5*(-ctrlpt[i - 1].z + ctrlpt[i + 1].z)
				+ t*t*(ctrlpt[i - 1].z - 2.5*ctrlpt[i].z + 2 * ctrlpt[i + 1].z - 0.5*ctrlpt[i + 2].z)
				+ t*t*t*(-0.5*ctrlpt[i - 1].z + 1.5*ctrlpt[i].z - 1.5*ctrlpt[i + 1].z + 0.5*ctrlpt[i + 2].z);

			NextPt.x = ctrlpt[i].x
				+ u*0.5*(-ctrlpt[i - 1].x + ctrlpt[i + 1].x)
				+ u*u*(ctrlpt[i - 1].x - 2.5*ctrlpt[i].x + 2 * ctrlpt[i + 1].x - 0.5*ctrlpt[i + 2].x)
				+ u*u*u*(-0.5*ctrlpt[i - 1].x + 1.5*ctrlpt[i].x - 1.5*ctrlpt[i + 1].x + 0.5*ctrlpt[i + 2].x);

			NextPt.y = ctrlpt[i].y
				+ u*0.5*(-ctrlpt[i - 1].y + ctrlpt[i + 1].y)
				+ u*u*(ctrlpt[i - 1].y - 2.5*ctrlpt[i].y + 2 * ctrlpt[i + 1].y - 0.5*ctrlpt[i + 2].y)
				+ u*u*u*(-0.5*ctrlpt[i - 1].y + 1.5*ctrlpt[i].y - 1.5*ctrlpt[i + 1].y + 0.5*ctrlpt[i + 2].y);

			NextPt.z = ctrlpt[i].z
				+ u*0.5*(-ctrlpt[i - 1].z + ctrlpt[i + 1].z)
				+ u*u*(ctrlpt[i - 1].z - 2.5*ctrlpt[i].z + 2 * ctrlpt[i + 1].z - 0.5*ctrlpt[i + 2].z)
				+ u*u*u*(-0.5*ctrlpt[i - 1].z + 1.5*ctrlpt[i].z - 1.5*ctrlpt[i + 1].z + 0.5*ctrlpt[i + 2].z);

			DirVector = NextPt - CtrlPt;
			Normalize(DirVector);
			DirVector.y = 0;
			float temp = DirVector.x;
			DirVector.x = DirVector.z;
			DirVector.z = -temp;


			glVertex3f(CtrlPt.x - DirVector.x*railradius, max(min_height, CtrlPt.y), CtrlPt.z - DirVector.z*railradius);
		}
	}
	glEnd();
	////////////////////
}

void MoveCart()
{

	{
		headindex %= num_pt - 1;
		float speed = 2;

		if (headstair > 100) {
			headindex++;
			headstair -= 100;
		}

		if (ctrlpt[headindex].y < ctrlpt[headindex + 1].y) {
			speed = 0.5;
		}
		else if (ctrlpt[headindex].y > ctrlpt[headindex + 1].y) {
			speed = 4;
		}

		headstair += speed;

		Vec3f Pt{};
		Vec3f Target{};

		float t = headstair*0.01;
		float u = t + 0.01;
		Pt = (1 - t)*ctrlpt[headindex] + t*ctrlpt[headindex + 1];
		Target = (1 - u)*ctrlpt[headindex] + u*ctrlpt[headindex + 1];

		if (num_pt > 3 && headindex != num_pt - 2 && headindex != 0) {

			Pt.x = ctrlpt[headindex].x
				+ t*0.5*(-ctrlpt[headindex - 1].x + ctrlpt[headindex + 1].x)
				+ t*t*(ctrlpt[headindex - 1].x - 2.5*ctrlpt[headindex].x + 2 * ctrlpt[headindex + 1].x - 0.5*ctrlpt[headindex + 2].x)
				+ t*t*t*(-0.5*ctrlpt[headindex - 1].x + 1.5*ctrlpt[headindex].x - 1.5*ctrlpt[headindex + 1].x + 0.5*ctrlpt[headindex + 2].x);

			Pt.y = ctrlpt[headindex].y
				+ t*0.5*(-ctrlpt[headindex - 1].y + ctrlpt[headindex + 1].y)
				+ t*t*(ctrlpt[headindex - 1].y - 2.5*ctrlpt[headindex].y + 2 * ctrlpt[headindex + 1].y - 0.5*ctrlpt[headindex + 2].y)
				+ t*t*t*(-0.5*ctrlpt[headindex - 1].y + 1.5*ctrlpt[headindex].y - 1.5*ctrlpt[headindex + 1].y + 0.5*ctrlpt[headindex + 2].y);

			Pt.z = ctrlpt[headindex].z
				+ t*0.5*(-ctrlpt[headindex - 1].z + ctrlpt[headindex + 1].z)
				+ t*t*(ctrlpt[headindex - 1].z - 2.5*ctrlpt[headindex].z + 2 * ctrlpt[headindex + 1].z - 0.5*ctrlpt[headindex + 2].z)
				+ t*t*t*(-0.5*ctrlpt[headindex - 1].z + 1.5*ctrlpt[headindex].z - 1.5*ctrlpt[headindex + 1].z + 0.5*ctrlpt[headindex + 2].z);

			Target.x = ctrlpt[headindex].x
				+ u*0.5*(-ctrlpt[headindex - 1].x + ctrlpt[headindex + 1].x)
				+ u*u*(ctrlpt[headindex - 1].x - 2.5*ctrlpt[headindex].x + 2 * ctrlpt[headindex + 1].x - 0.5*ctrlpt[headindex + 2].x)
				+ u*u*u*(-0.5*ctrlpt[headindex - 1].x + 1.5*ctrlpt[headindex].x - 1.5*ctrlpt[headindex + 1].x + 0.5*ctrlpt[headindex + 2].x);

			Target.y = ctrlpt[headindex].y
				+ u*0.5*(-ctrlpt[headindex - 1].y + ctrlpt[headindex + 1].y)
				+ u*u*(ctrlpt[headindex - 1].y - 2.5*ctrlpt[headindex].y + 2 * ctrlpt[headindex + 1].y - 0.5*ctrlpt[headindex + 2].y)
				+ u*u*u*(-0.5*ctrlpt[headindex - 1].y + 1.5*ctrlpt[headindex].y - 1.5*ctrlpt[headindex + 1].y + 0.5*ctrlpt[headindex + 2].y);

			Target.z = ctrlpt[headindex].z
				+ u*0.5*(-ctrlpt[headindex - 1].z + ctrlpt[headindex + 1].z)
				+ u*u*(ctrlpt[headindex - 1].z - 2.5*ctrlpt[headindex].z + 2 * ctrlpt[headindex + 1].z - 0.5*ctrlpt[headindex + 2].z)
				+ u*u*u*(-0.5*ctrlpt[headindex - 1].z + 1.5*ctrlpt[headindex].z - 1.5*ctrlpt[headindex + 1].z + 0.5*ctrlpt[headindex + 2].z);
		}

		Vec3f Dir = Target - Pt;
		Normalize(Dir);
		float angle = atan2(Dir.x, Dir.z) / PI*180.0;

		head.Setpt(Pt);
		head.SetDir(Dir);
		head.SetAngle(angle);

		///////////////////////////////////////////////

		Vec3f View = head.Getpt();
		View.y += 50;

		firstcamera.SetEye(View);
		firstcamera.SetAt(View +Dir*512);


	}
	
	for(int i =0;i<3;++i) {
		containerindex[i] %= num_pt - 1;
		float speed = 2;

		if (containerstair[i] > 100) {
			containerindex[i]++;
			containerstair[i] -= 100;
		}

		if (ctrlpt[containerindex[i]].y < ctrlpt[containerindex[i] + 1].y) {
			speed = 0.5;
		}
		else if (ctrlpt[containerindex[i]].y > ctrlpt[containerindex[i] + 1].y) {
			speed = 4;
		}

		containerstair[i] += speed;

		Vec3f Pt{};
		Vec3f Target{};

		float t = containerstair[i]*0.01;
		float u = t + 0.01;
		Pt = (1 - t)*ctrlpt[containerindex[i]] + t*ctrlpt[containerindex[i] + 1];
		Target = (1 - u)*ctrlpt[containerindex[i]] + u*ctrlpt[containerindex[i] + 1];

		if (num_pt > 3 && containerindex[i] != num_pt - 2 && containerindex[i] != 0) {

			Pt.x = ctrlpt[containerindex[i]].x
				+ t*0.5*(-ctrlpt[containerindex[i] - 1].x + ctrlpt[containerindex[i] + 1].x)
				+ t*t*(ctrlpt[containerindex[i] - 1].x - 2.5*ctrlpt[containerindex[i]].x + 2 * ctrlpt[containerindex[i] + 1].x - 0.5*ctrlpt[containerindex[i] + 2].x)
				+ t*t*t*(-0.5*ctrlpt[containerindex[i] - 1].x + 1.5*ctrlpt[containerindex[i]].x - 1.5*ctrlpt[containerindex[i] + 1].x + 0.5*ctrlpt[containerindex[i] + 2].x);

			Pt.y = ctrlpt[containerindex[i]].y
				+ t*0.5*(-ctrlpt[containerindex[i] - 1].y + ctrlpt[containerindex[i] + 1].y)
				+ t*t*(ctrlpt[containerindex[i] - 1].y - 2.5*ctrlpt[containerindex[i]].y + 2 * ctrlpt[containerindex[i] + 1].y - 0.5*ctrlpt[containerindex[i] + 2].y)
				+ t*t*t*(-0.5*ctrlpt[containerindex[i] - 1].y + 1.5*ctrlpt[containerindex[i]].y - 1.5*ctrlpt[containerindex[i] + 1].y + 0.5*ctrlpt[containerindex[i] + 2].y);

			Pt.z = ctrlpt[containerindex[i]].z
				+ t*0.5*(-ctrlpt[containerindex[i] - 1].z + ctrlpt[containerindex[i] + 1].z)
				+ t*t*(ctrlpt[containerindex[i] - 1].z - 2.5*ctrlpt[containerindex[i]].z + 2 * ctrlpt[containerindex[i] + 1].z - 0.5*ctrlpt[containerindex[i] + 2].z)
				+ t*t*t*(-0.5*ctrlpt[containerindex[i] - 1].z + 1.5*ctrlpt[containerindex[i]].z - 1.5*ctrlpt[containerindex[i] + 1].z + 0.5*ctrlpt[containerindex[i] + 2].z);

			Target.x = ctrlpt[containerindex[i]].x
				+ u*0.5*(-ctrlpt[containerindex[i] - 1].x + ctrlpt[containerindex[i] + 1].x)
				+ u*u*(ctrlpt[containerindex[i] - 1].x - 2.5*ctrlpt[containerindex[i]].x + 2 * ctrlpt[containerindex[i] + 1].x - 0.5*ctrlpt[containerindex[i] + 2].x)
				+ u*u*u*(-0.5*ctrlpt[containerindex[i] - 1].x + 1.5*ctrlpt[containerindex[i]].x - 1.5*ctrlpt[containerindex[i] + 1].x + 0.5*ctrlpt[containerindex[i] + 2].x);

			Target.y = ctrlpt[containerindex[i]].y
				+ u*0.5*(-ctrlpt[containerindex[i] - 1].y + ctrlpt[containerindex[i] + 1].y)
				+ u*u*(ctrlpt[containerindex[i] - 1].y - 2.5*ctrlpt[containerindex[i]].y + 2 * ctrlpt[containerindex[i] + 1].y - 0.5*ctrlpt[containerindex[i] + 2].y)
				+ u*u*u*(-0.5*ctrlpt[containerindex[i] - 1].y + 1.5*ctrlpt[containerindex[i]].y - 1.5*ctrlpt[containerindex[i] + 1].y + 0.5*ctrlpt[containerindex[i] + 2].y);

			Target.z = ctrlpt[containerindex[i]].z
				+ u*0.5*(-ctrlpt[containerindex[i] - 1].z + ctrlpt[containerindex[i] + 1].z)
				+ u*u*(ctrlpt[containerindex[i] - 1].z - 2.5*ctrlpt[containerindex[i]].z + 2 * ctrlpt[containerindex[i] + 1].z - 0.5*ctrlpt[containerindex[i] + 2].z)
				+ u*u*u*(-0.5*ctrlpt[containerindex[i] - 1].z + 1.5*ctrlpt[containerindex[i]].z - 1.5*ctrlpt[containerindex[i] + 1].z + 0.5*ctrlpt[containerindex[i] + 2].z);
		}

		Vec3f Dir = Target - Pt;
		Normalize(Dir);
		float angle = atan2(Dir.x, Dir.z) / PI*180.0;

		container[i].Setpt(Pt);
		container[i].SetAngle(angle);
	}


}

bool CheckCross(Vec3f p1_1, Vec3f p1_2, Vec3f p2_1, Vec3f p2_2) {

	double t;
	double s;
	double under = (p2_2.z - p2_1.z)*(p1_2.x - p1_1.x) - (p2_2.x - p2_1.x)*(p1_2.z - p1_1.z);
	if (under == 0) return false;

	double _t = (p2_2.x - p2_1.x)*(p1_1.z - p2_1.z) - (p2_2.z - p2_1.z)*(p1_1.x - p2_1.x);
	double _s = (p1_2.x - p1_1.x)*(p1_1.z - p2_1.z) - (p1_2.z - p1_1.z)*(p1_1.x - p2_1.x);

	t = _t / under;
	s = _s / under;

	if (t<0.0 || t>1.0 || s<0.0 || s>1.0) return false;
	if (_t == 0 && _s == 0) return false;

	float c_x = p1_1.x + t * (double)(p1_2.x - p1_1.x);
	float c_z = p1_1.z + t * (double)(p1_2.z - p1_1.z);
	return true;

}