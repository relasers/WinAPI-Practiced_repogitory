#pragma once

#include<Windows.h>
#include<glut.h>
#include<chrono>
constexpr int Width = 20;
constexpr int Height = 40;
constexpr int MaxTick = 10;
class CRectangle
{
private:
	POINT point;
	GLint width = Width;
	GLint height = Height;
	GLfloat R = 1.0f;
	GLfloat G = 1.0f;
	GLfloat B = 1.0f;

	int tick = 0;
public:
	CRectangle();
	CRectangle(POINT pt);
	~CRectangle();
	void Draw();
	void Update();
	void SwapSize();
	GLint GetX() const { return (GLint)point.x; }
	GLint GetY() const { return (GLint)point.y; }
	GLint GetW() const { return width; }
	GLint GetH() const { return height; }
};

