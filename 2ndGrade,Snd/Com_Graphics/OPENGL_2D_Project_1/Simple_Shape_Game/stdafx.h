#pragma once
#include<iostream>
#include <cstdlib>
#include <chrono>
#include <gl/glut.h>
#include <list>
#include <chrono>
#include <cmath>
#include <Windows.h>
#include"Vec2D.h"
#include"Line.h"
#include"Shape.h"
#include"Note.h"
#include"Score.h"

typedef enum{
	Left,Right,Plus,Minus
}Direction;

typedef enum {
};

constexpr int Window_Width = 600;
constexpr int Window_Height = 700;
constexpr int Number_Line = 5;
constexpr int MaxScore = 10;
constexpr int MaxSize = 1;
constexpr float PI = 3.141592;