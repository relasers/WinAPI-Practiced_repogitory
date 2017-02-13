#pragma once

#include<iostream>
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
class CShape
{
private:
	Vec2f point;
	Vec2f dir;
	GLint Radius;

	GLfloat R = 1.0f;
	GLfloat G = 1.0f;
	GLfloat B = 1.0f;
	GLfloat A = 1.0f;

	int X_vec = 1;
	int Y_vec = 1;
	int speed = 1;

	bool IsDeadMan = true; // Á×¾î°¡´Â°¡
public:
	CShape();
	CShape(POINT pt);
	~CShape();
	void Draw();
	void Update(int w, int h);
	void IncreaseSpd();
	void DecreaseSpd();
	void IsOutofField(RECT rect);
	GLint GetX() const { return (GLint)point.x; }
	GLint GetY() const { return (GLint)point.y; }
	GLint GetRadius() const { return Radius; }
};

