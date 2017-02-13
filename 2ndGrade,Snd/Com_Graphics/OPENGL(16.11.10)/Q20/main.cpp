#include<iostream>
#include<gl/glut.h>
#include<ctime>
#include"Vec3D.h"

using namespace std;

enum Handle {
	Middle, Hand, Finger
};

constexpr int Window_Width = 800;
constexpr int Window_Height = 800;

constexpr float axis_size = 50.0;
constexpr float floor_size = 120.0;

constexpr int Rotate_Speed = 20;

constexpr int Camera_Speed = 5;

constexpr float PI = 3.141592;


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
		glColor3f(1.0, 0.0, 0.0);
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

class Camera {
private:
	Vec3i m_camera_angle{ 180,0,0 };
	Vec3i m_Up{ 0,1,0 };
	Vec3f m_Eye{};

	int m_camera_distance = -300;
public:
	void Rander() {
		glLoadIdentity(); // 카메라 적용전 초기화

						  //기하와 벡터 구의 방정식 참조

		gluLookAt(m_Eye.x, m_Eye.y, m_Eye.z,   // Eye
			0.0, 0.0, 0.0,    // At
			m_Up.x, m_Up.y, m_Up.z);   // Up
	}
	void Update() {
		m_Eye.x = m_camera_distance * -sinf(m_camera_angle.x*(PI / 180)) * cosf((m_camera_angle.y)*(PI / 180));
		m_Eye.y = m_camera_distance * -sinf((m_camera_angle.y)*(PI / 180));
		m_Eye.z = -m_camera_distance * cosf((m_camera_angle.x)*(PI / 180)) * cosf((m_camera_angle.y)*(PI / 180));

		if (90 < m_camera_angle.y && m_camera_angle.y < 270
			) {
			m_Up.y = -1;
		}
		else
		{
			m_Up.y = 1;
		}

	}
	void init() {
		m_camera_angle = { 0,0,0 };
	}
	void HandleDistance(int distance) {
		m_camera_distance += distance;
	}
	void HandleAngle(int angle, Vec3i axis) {
		m_camera_angle += axis*angle;

		if (m_camera_angle.x < 0) m_camera_angle.x += 360;
		if (m_camera_angle.y < 0) m_camera_angle.y += 360;
		if (m_camera_angle.z < 0) m_camera_angle.z += 360;

		m_camera_angle.x %= 360;
		m_camera_angle.y %= 360;
		m_camera_angle.z %= 360;
	}
};

class Gate {
private:
	float m_size{ 15 };
	float m_gatesize{ 15 };
	int alphasize{};
	int angle{};
	Vec3f m_pt{ 0.0f,m_size / 2,0.0f };
	Bound_Box bb{};
public:
	void Rander() {

		glPushMatrix();
		{

			glTranslatef(m_pt.x, m_pt.y, m_pt.z);

			glColor3f(0.2, 0.2, 0.1);

			glPushMatrix();
			{

				glTranslatef(-m_gatesize, m_size, 0);
				glScalef(1, 3, 1);
				glutSolidCube(m_size);
				glTranslatef(m_gatesize * 2, 0, 0);
				glutSolidCube(m_size);
			}
			glPopMatrix();

			glTranslatef(0, m_size * 2, 0);
			glScalef(1 + m_gatesize / 8, 1, 1);
			glutSolidCube(m_size);
		}
		glPopMatrix();


	}
	void Update() {
		(++alphasize) %= 180;
		bb.SetBB(m_pt, { m_size*1.5f,0.0f,m_size / 2 });
		m_gatesize = max(m_size / 2, m_size / 2 + sin((float)alphasize*PI / 180.0)*m_size / 2);
	}
	Bound_Box GetBB() { return bb; }
};
class SquareTree {
private:
	float m_size{ 15 };
	int angle{};
	Vec3f m_pt{ -floor_size / 2,0.0f,-floor_size / 2 };
	Bound_Box bb;
public:
	void Rander() {
		glPushMatrix();
		{
			glTranslatef(m_pt.x, m_pt.y, m_pt.z);



			glPushMatrix();
			{
				glTranslatef(0, m_size*1.5, 0);

				glScalef(1, 3, 1);
				glColor3f(0.5, 0.5, 0.5);
				glutSolidCube(m_size);
			}
			glPopMatrix();

			glColor3f(0.0, 0.7, 0.1);
			glTranslatef(0, m_size * 3, 0);
			glRotatef(angle, 0, 1, 0);
			glScalef(m_size / 2, 1, m_size / 2);
			glutSolidCube(m_size / 2);

		}
		glPopMatrix();
	}
	void Update() {
		(++angle) %= 360;
		bb.SetBB(m_pt, { m_size / 2,0.0f,m_size / 2 });
	}
	Bound_Box GetBB() { return bb; }
};
class RoundTree {
private:
	float m_size{ 10 };
	float m_leafsize{ 10 };
	int angle{};
	Vec3f m_pt{ floor_size / 2,0.0f,-floor_size / 2 };
	Bound_Box bb;
public:
	void Rander() {
		glPushMatrix();
		{
			glTranslatef(m_pt.x, m_pt.y, m_pt.z);



			glPushMatrix();
			{
				glTranslatef(0, m_size*1.5, 0);

				glScalef(1, 3, 1);
				glColor3f(0.5, 0.5, 0.5);
				glutSolidCube(m_size);
			}
			glPopMatrix();

			glColor3f(0.0, 0.7, 0.1);
			glTranslatef(0, m_size * 3, 0);
			glRotatef(angle, 0, 1, 0);
			glutWireSphere(m_leafsize, 10, 10);

		}
		glPopMatrix();
	}
	void Update() {
		(++angle) %= 180;
		bb.SetBB(m_pt, { m_size / 2,0.0f,m_size / 2 });
		m_leafsize = max(m_size, m_size + sin((float)angle*PI / 180.0)*m_size);

	}
	Bound_Box GetBB() { return bb; }
};
class Elevator {
private:
	float m_size{ 15 };
	int angle{};
	Vec3f m_pt{ floor_size / 2,0.0f,floor_size / 2 };
	Bound_Box bb;
public:
	void Rander() {
		glPushMatrix();
		{
			glTranslatef(m_pt.x, m_pt.y, m_pt.z);
			glPushMatrix();
			{
				glTranslatef(0, m_size*1.5, 0);

				glScalef(1, 3, 1);
				glColor3f(0.9, 0.1, 0.5);
				glutSolidCube(m_size);
			}
			glPopMatrix();

			glTranslatef(0, m_size * 2 + sin(angle*PI / 180)*m_size, 0);
			glRotatef(90, 1, 0, 0);
			glColor3f(0.9, 0.1, 0.9);
			glutWireTorus(m_size / 3, m_size, 10, 10);

		}
		glPopMatrix();
	}
	void Update() {
		(++angle) %= 360;
		bb.SetBB(m_pt, { m_size / 2,0.0f,m_size / 2 });
	}
	Bound_Box GetBB() { return bb; }
};
class ConeBuilding {
private:
	float m_size{ 25 };
	float m_topsize{};
	float m_bottomsize{};

	int angle{};
	Vec3f m_pt{ -floor_size / 2,0.0f,floor_size / 2 };
	Bound_Box bb;
public:
	void Rander() {
		glPushMatrix();
		{
			glTranslatef(m_pt.x, m_pt.y, m_pt.z);
			glColor3f(0.2, 0.7, 1.0);
			glPushMatrix();
			{
				glRotatef(270, 1, 0, 0);
				glutWireCone(m_bottomsize, m_bottomsize, 10, 10);
			}
			glPopMatrix();

			glTranslatef(0, m_bottomsize + m_topsize, 0);
			glRotatef(90, 1, 0, 0);
			glutWireCone(m_topsize, m_topsize, 10, 10);
		}
		glPopMatrix();
	}
	void Update() {
		(++angle) %= 180;
		bb.SetBB(m_pt, { m_size,0.0f,m_size });
		m_bottomsize = sin(angle*PI / 180)*m_size;
		m_topsize = m_size - m_bottomsize;
	}
	Bound_Box GetBB() { return bb; }
};
class Ball {
private:
	Bound_Box bb{};
	Vec3f m_pt{ 0,0,-100 };
	Vec3f m_angle{};
	int m_radius = 5;

public:

	void Update() {
		bb.SetBB(m_pt, { m_radius,0,m_radius });
	}


	void Rander() {


		glPushMatrix();
		{
			glTranslatef(m_pt.x, m_radius, m_pt.z);

			bb.Rander();

			glRotatef(m_angle.x, 0, 0, 1);
			glRotatef(m_angle.y, 0, 1, 0);
			glRotatef(m_angle.z, 1, 0, 0);
			glutWireSphere(m_radius, 120, 120);
			//glutWireTeapot(m_radius);

		}
		glPopMatrix();



	}

	void Move(int direction, float x, Vec3f axis) {
		m_angle -= axis*x*direction;
		m_pt.x += axis.x*x*direction  * PI * m_radius / 360;
		m_pt.y += axis.y*x*direction  * PI * m_radius / 360;
		m_pt.z += axis.z*x*direction  * PI * m_radius / 360;

		m_pt.x = min(floor_size, m_pt.x + m_radius);
		m_pt.y = min(floor_size, m_pt.y + m_radius);
		m_pt.z = min(floor_size, m_pt.z + m_radius);
		m_pt.x = max(-floor_size + m_radius, m_pt.x - m_radius);
		m_pt.y = max(-floor_size + m_radius, m_pt.y - m_radius);
		m_pt.z = max(-floor_size + m_radius, m_pt.z - m_radius);
	}

	void init() {
		m_pt = { 0,0,-100 };
		m_angle = { 0,0,0 };
	}

	void SetPt(Vec3f pt) {
		m_pt = pt;
	}
	//////////////////////////////////////////
	Vec3f GetPt() { return m_pt; }
	int GetSize() { return m_radius; }
	Bound_Box GetBB() { return bb; }
};
class Crane {
private:
	Vec3f m_pt{ 0.0f,0.0f,-floor_size / 2 };
	Bound_Box bb{};
	Vec3f m_mid_angle{ 30,100,20 };
	Vec3f m_hand_angle{};
	Vec3f m_finger_angle{};

	int dir = 1;
	int speed = 1;
	int base_angle{};
	int m_wheel_angle{};

	int m_size = 15;
	float m_wheelsize = 5;
public:
	void Rander() {

		glPushMatrix();
		glTranslatef(m_pt.x, m_pt.y, m_pt.z);
		glTranslatef(0, m_wheelsize*2.5, 0);
		glRotatef(base_angle, 0, 1, 0);
		glColor3f(1.0, 0, 0);

		bb.Rander();

		////<몸체>////
		glPushMatrix();
		{
			glScalef(1, 0.5, 1);
			DrawCube(m_size, 1, true); // base
		}
		glPopMatrix();
		////<바퀴>////
		glPushMatrix();
		{
			glColor3f(0.5, 0.8, 0.8);
			glTranslatef(m_size / 2, -m_wheelsize, -m_size / 2);
			DrawWheel();
			glTranslatef(0, 0, m_size);
			DrawWheel();
			glTranslatef(-m_size, 0, 0);
			DrawWheel();
			glTranslatef(0, 0, -m_size);
			DrawWheel();
		}
		glPopMatrix();





		glTranslatef(0, m_size / 2, 0);

		glRotatef(m_mid_angle.x, 1, 0, 0);
		glRotatef(m_mid_angle.y, 0, 1, 0);



		glColor3f(0.0, 1.0, 0);
		DrawCube(m_size / 2, 1, true); // arm

		glTranslatef(m_size / 2, 0, 0);

		glRotatef(m_hand_angle.x, 1, 0, 0);
		glRotatef(m_hand_angle.z, 0, 0, 1);

		glColor3f(0.0, 0.0, 1.0);
		DrawCube(m_size / 4, 6, false); // hand

		glTranslatef(m_size*1.5, 0, 0);

		glRotatef(m_finger_angle.x, 1, 0, 0);
		glRotatef(m_finger_angle.z, 0, 0, 1);

		glColor3f(0.0, 0.5, 1.0);
		DrawCube(m_size / 5, 4, false); // hand

		glPopMatrix();
	}

	void Update(Ball ball,RoundTree tree, SquareTree tree2) {
		bb.SetBB(m_pt, { m_size,0,m_size / 2 });
		m_wheel_angle -= dir*speed;


		if (!bb.CollisionCheck(ball.GetBB()))
			m_pt.x += dir*speed;
		if (bb.CollisionCheck(ball.GetBB()))
			m_pt.x -= dir*speed*1.1;
		if (bb.CollisionCheck(tree.GetBB())) {
			m_pt.x -= dir*speed*2;
			dir *= -1;
		}
		if (bb.CollisionCheck(tree2.GetBB())) {
			m_pt.x -= dir*speed*2;
			dir *= -1;
		}
			

		if (m_pt.x - m_size < -floor_size)
		{
			dir *= -1;
			m_pt.x = -floor_size + m_size;
		}
		if (m_pt.x + m_size > floor_size)
		{
			dir *= -1;
			m_pt.x = floor_size - m_size;
		}
	}

	void DrawCube(float size, int length, bool isbase) {

		glPushMatrix();

		if (isbase)glTranslatef(-size / 2, 0, 0);
		//if(!isbase)glTranslatef(size/2, 0, 0);
		glutSolidCube(size);
		for (int i = 0; i < length; ++i)
		{
			glTranslatef(size, 0, 0);
			glutSolidCube(size);
		}
		glPopMatrix();

	}

	void DrawWheel() {
		glPushMatrix();
		{
			glRotatef(m_wheel_angle, 0, 0, 1);
			glutWireTorus(m_wheelsize / 2, m_wheelsize, 10, 10);
		}
		glPopMatrix();
	}

	void RotateBase(int x) {
		base_angle += x;
	}

	void Handle(int dir, Vec3f axis, int handle) {

		switch (handle) {
		case Handle::Middle:
			m_mid_angle += axis*dir;
			break;
		case Handle::Hand:
			m_hand_angle += axis*dir;
			break;
		case Handle::Finger:
			m_finger_angle += axis*dir;
			break;
		}
	}

	void Init() {
		Vec3f m_mid_angle = { 0,0,0 };
		Vec3f m_hand_angle = { 0,0,0 };
	}

	Vec3f GetPt() { return m_pt; }
	int GetSize() { return m_size; }
	Bound_Box GetBB() { return bb; }
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


void DrawAxis();
void DrawFloor();

void DrawTriangle(Vec3f Position, Vec3f Size, int angle, Vec3f axis);
void DrawRactangle(Vec3f Position, Vec3f Size, int angle, Vec3f axis);

bool BallCollisionCheck(Ball ball);
///////////////////////////////////////////
////////////////////////////////////////////
Ball ball;
Crane crane;
Camera camera;

Gate gate;
SquareTree squaretree;
RoundTree roundtree;
Elevator elevator;
ConeBuilding cone;




void main(int argc, char *argv[])
{
	//초기화 함수들
	InitObjects();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(Window_Width, Window_Height); // 윈도우의 크기 지정
	glutCreateWindow("[2013182010김병진]Q20"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutKeyboardFunc(Keyboard); // 키보드 입력 콜백 함수
	glutTimerFunc(1, TimerFunction, 1);
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정
	glutMainLoop();


}
// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기
														// 색상 지정하고 사각형 그리기
	glEnable(GL_DEPTH_TEST);

	glColor4f(1.0, 1.0, 1.0, 1.0f);



	camera.Rander();


	glPushMatrix();
	{




		DrawAxis();

		//////////////////<바닥>////////////////////
		DrawFloor();

		glColor4f(1.0, 1.0, 1.0, 1.0);
		glutWireCube(floor_size * 2);

		gate.Rander();
		squaretree.Rander();
		roundtree.Rander();
		elevator.Rander();
		cone.Rander();
		crane.Rander();
		ball.Rander();
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
	gluPerspective(60.0f, w / h, 1.0, 1000.0); // fovy :: 최대 180(넘어가면 거꾸로 보여), 작을수록 크게 보임
											   //glTranslatef(0.0, 0.0, -300.0);

											   //glOrtho(-400.0, 400, -400.0, 400, -400.0, 400.0); // x축 최소,최대, y축 최소,최대, z축 최소 최대 // 직각투영




	glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y)
{
	{
		if (key == 'd' || key == 'D') {
			Ball temp;
			temp.SetPt(ball.GetPt());
			temp.Move(-1, Rotate_Speed, { 1,0,0 });
			temp.Update();
			if (BallCollisionCheck(temp))
				ball.Move(-1, Rotate_Speed, { 1,0,0 });
		}
		if (key == 'a' || key == 'A') {
			Ball temp;
			temp.SetPt(ball.GetPt());
			temp.Move(1, Rotate_Speed, { 1,0,0 });
			temp.Update();
			if (BallCollisionCheck(temp))
				ball.Move(1, Rotate_Speed, { 1,0,0 });
		}
		if (key == 'q' || key == 'Q') {
			Ball temp;
			temp.SetPt(ball.GetPt());
			temp.Move(-1, Rotate_Speed, { 0,1,0 });
			temp.Update();
			if (BallCollisionCheck(temp))
				ball.Move(-1, Rotate_Speed, { 0,1,0 });
		}
		if (key == 'e' || key == 'E') {
			Ball temp;
			temp.SetPt(ball.GetPt());
			temp.Move(1, Rotate_Speed, { 0,1,0 });
			temp.Update();
			if (BallCollisionCheck(temp))
				ball.Move(1, Rotate_Speed, { 0,1,0 });
		}
		if (key == 's' || key == 'S') {
			Ball temp;
			temp.SetPt(ball.GetPt());
			temp.Move(-1, Rotate_Speed, { 0,0,1 });
			temp.Update();
			if (BallCollisionCheck(temp))
				ball.Move(-1, Rotate_Speed, { 0,0,1 });
		}
		if (key == 'w' || key == 'W') {
			Ball temp;
			temp.SetPt(ball.GetPt());
			temp.Move(1, Rotate_Speed, { 0,0,1 });
			temp.Update();
			if (BallCollisionCheck(temp))
				ball.Move(1, Rotate_Speed, { 0,0,1 });
		}

		if (key == 'l' || key == 'L') {
			camera.HandleAngle(Camera_Speed, { 1,0,0 });
		}
		if (key == 'j' || key == 'J') {
			camera.HandleAngle(-Camera_Speed, { 1,0,0 });
		}
		if (key == 'i' || key == 'I') {
			camera.HandleAngle(Camera_Speed, { 0,1,0 });
		}
		if (key == 'k' || key == 'K') {
			camera.HandleAngle(-Camera_Speed, { 0,1,0 });
		}
		if (key == 'u' || key == 'U') {
			camera.HandleAngle(Camera_Speed, { 0,0,1 });
		}
		if (key == 'o' || key == 'O') {
			camera.HandleAngle(-Camera_Speed, { 0,0,1 });
		}




		if (key == '+') {
			camera.HandleDistance(10);
		}
		if (key == '-') {
			camera.HandleDistance(-10);
		}
		if (key == 'r' || key == 'R') {
			camera.init();
			ball.init();
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
	camera.Update();

	gate.Update();
	squaretree.Update();
	roundtree.Update();
	elevator.Update();
	cone.Update();
	ball.Update();
	crane.Update(ball,roundtree,squaretree);

	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(1, TimerFunction, 1); // 타이머함수 재 설정
}

void InitObjects()
{
	srand((unsigned)time(nullptr));
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
		glScalef(2, 0.01, 2);

		{
			glutSolidCube(floor_size);

		}
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

bool BallCollisionCheck(Ball ball) {
	if (ball.GetBB().CollisionCheck(crane.GetBB())) return false;
	if (ball.GetBB().CollisionCheck(squaretree.GetBB())) return false;
	if (ball.GetBB().CollisionCheck(roundtree.GetBB())) return false;
	if (ball.GetBB().CollisionCheck(gate.GetBB())) return false;
	if (ball.GetBB().CollisionCheck(elevator.GetBB())) return false;
	if (ball.GetBB().CollisionCheck(cone.GetBB())) return false;
	return true;
}
