#pragma once

#include<Windows.h>
#include<glut.h>
#include<chrono>
constexpr int Radius = 1;
constexpr int MaxTick = 2;

constexpr int MX_Speed = 20;
constexpr int MN_Speed = 1;

constexpr double PI = 3.141592;
class CMadurai
{
private:
	POINT point;
	GLint radius = Radius;
	GLint work = 1;


	GLfloat R = 1.0f;
	GLfloat G = 1.0f;
	GLfloat B = 1.0f;

	int X_vec = 1;
	int Y_vec = 1;
	int speed = 10;

public:
	CMadurai();
	CMadurai(POINT pt);
	~CMadurai();
	void Draw();
	void Update(int w, int h);
	void IncreaseSpd();
	void DecreaseSpd();

	GLint GetX() const { return (GLint)point.x; }
	GLint GetY() const { return (GLint)point.y; }
	GLfloat GetRadius() const { return radius; }
};

