#pragma once

#include<Windows.h>
#include<glut.h>
#include<chrono>
constexpr int Width = 20;
constexpr int Height = 40;
constexpr int MaxTick = 2;

constexpr int MX_Speed = 20;
constexpr int MN_Speed = 1;

constexpr double PI = 3.141592;
class CCircle
{
private:
	POINT point;
	GLint width = Width;
	GLint height = Height;
	GLfloat R = 1.0f;
	GLfloat G = 1.0f;
	GLfloat B = 1.0f;

	int X_vec = 1;
	int Y_vec = 1;
	int speed = 10;

	int shape = 1;

	int tick = 0;


public:
	CCircle();
	CCircle(POINT pt);
	~CCircle();
	void Draw();
	void Update(int w, int h);
	void SwapSize();
	void ChangeShape(int s);
	void IncreaseSpd();
	void DecreaseSpd();

	GLint GetX() const { return (GLint)point.x; }
	GLint GetY() const { return (GLint)point.y; }
	GLint GetW() const { return width; }
	GLint GetH() const { return height; }
	bool IsOver(int w);
};

