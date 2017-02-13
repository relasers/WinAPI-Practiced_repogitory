#pragma once

#include<Windows.h>
#include<glut.h>
#include<chrono>

enum class Shape_Dir {
	Right, Down, Left, Top
};

constexpr int Width = 50;
constexpr int Height = 50;
constexpr int MaxTick = 2;

constexpr int MX_Speed = 20;
constexpr int MN_Speed = 1;

constexpr double PI = 3.141592;
class CRectangle
{
private:
	POINT StartPoint;
	POINT point;
	GLint width = Width;
	GLint height = Height;
	GLfloat R = 1.0f;
	GLfloat G = 1.0f;
	GLfloat B = 1.0f;

	int X_vec = 1;
	int Y_vec = 1;
	int speed = 20;

	int shape = 0;

	int tick = 0;
	
	bool ismove = false;
	bool isback = false;
	int dir = (int)Shape_Dir::Right;

public:
	CRectangle();
	CRectangle(POINT pt);
	~CRectangle();
	void Draw();
	void Update(int w, int h);
	void SwapSize();
	void ChangeShape(int s);
	bool CollisionCheck(int x,int y);
	void MoveOn();
	void IncreaseSpd();
	void DecreaseSpd();

	GLint GetX() const { return (GLint)point.x; }
	GLint GetY() const { return (GLint)point.y; }
	GLint GetW() const { return width; }
	GLint GetH() const { return height; }
};

