#pragma once
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <glut.h>

#define Width 800
#define Height 600

struct Point {
	GLint x;
	GLint y;
};
//
static Point rect[10];
static int count = 0;
//


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void TimerFunction(int value);

void DrawRect(Point);