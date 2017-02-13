#pragma once

#include<Windows.h>
#include<glut.h>
#include<chrono>
#include"Vec2D.h"

constexpr int Width = 20;
constexpr int Height = 20;
constexpr int MaxTick = 2;

constexpr int MX_Speed = 20;
constexpr int MN_Speed = 1;

constexpr int RandSize = 40;

constexpr double PI = 3.141592;
class CRactangle
{
private:
	Vec2f point;
	GLint width = Width+rand()% RandSize;
	GLint height = Height + rand() % RandSize;
	GLfloat R = 1.0f;
	GLfloat G = 1.0f;
	GLfloat B = 1.0f;

	int X_vec = 1;
	int Y_vec = 1;
	int speed = 10;

	int shape = 0;

	int tick = 0;

public:
	CRactangle();
	CRactangle(POINT pt);
	~CRactangle();
	void Draw();
	void Update(int w, int h, Vec2f rectpt);
	void SwapSize();
	void ChangeShape(int s);
	void IncreaseSpd();
	void DecreaseSpd();

	GLint GetX() const { return (GLint)point.x; }
	GLint GetY() const { return (GLint)point.y; }
	GLint GetW() const { return width; }
	GLint GetH() const { return height; }
};

