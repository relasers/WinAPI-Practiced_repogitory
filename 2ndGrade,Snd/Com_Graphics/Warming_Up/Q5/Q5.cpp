#include <iostream>
#include <conio.h>
#include "Vec2D.h"

#define PI 3.141592f
#define RADIN PI / 180.0f
using namespace std;

int Q5InsertCommand();
void Q5Print();

Vec2f point[16];

int main() {
	/*
	point[0] = Vec2f(cosf(90.0f * RADIN), sin(90.0f * RADIN));

	point[1] = Vec2f(cos(120.0f*RADIN), sin(120.0f * RADIN));
	point[2] = Vec2f(cos(60.0f * RADIN), sin(60.0f * RADIN));

	point[3] = Vec2f(cos(135.0f * RADIN), sin(135.0f * RADIN));
	point[4] = Vec2f(cos(45.0f * RADIN), sin(45.0f * RADIN));

	point[5] = Vec2f(cos(150.0f * RADIN), sin(150.0f * RADIN));
	point[6] = Vec2f(cos(30.0f * RADIN), sin(30.0f * RADIN));

	point[7] = Vec2f(cos(180.0f * RADIN), sin(180.0f * RADIN));
	point[8] = Vec2f(cos(0), sin(0));

	point[9] = Vec2f(cos(210.0f * RADIN), sin(210.0f * RADIN));
	point[10] = Vec2f(cos(330.0f * RADIN), sin(330.0f * RADIN));

	point[11] = Vec2f(cos(225.0f * RADIN), sin(225.0f * RADIN));
	point[12] = Vec2f(cos(315.0f * RADIN), sin(315.0f * RADIN));

	point[13] = Vec2f(cos(240.0f * RADIN), sin(240.0f * RADIN));
	point[14] = Vec2f(cos(300.0f * RADIN), sin(300.0f * RADIN));

	point[15] = Vec2f(cos(270.0f * RADIN), sin(270.0f * RADIN));
	*/

	

	point[0] = Vec2f(cos(PI / 2.0f), sin(PI / 2.0f));

	point[1] = Vec2f(cos(PI - PI / 3.0f), sin(PI - PI / 3.0f));
	point[2] = Vec2f(cos(PI / 3.0f), sin(PI / 3.0f));

	point[3] = Vec2f(cos(PI - PI / 4.0f), sin(PI - PI / 4.0f));
	point[4] = Vec2f(cos(PI / 4.0f), sin(PI / 4.0f));

	point[5] = Vec2f(cos(PI - PI / 6.0f), sin(PI - PI / 6.0f));
	point[6] = Vec2f(cos(PI / 6.0f), sin(PI / 6.0f));

	point[7] = Vec2f(cos(PI), sin(PI));
	point[8] = Vec2f(cos(0), sin(0));

	point[9] = Vec2f(cos(PI + PI / 6.0f), sin(PI + PI / 6.0f));
	point[10] = Vec2f(cos(2.0f * PI - PI / 6.0f), sin(2.0f * PI - PI / 6.0f));

	point[11] = Vec2f(cos(PI + PI / 4.0f), sin(PI + PI / 4.0f));
	point[12] = Vec2f(cos(2.0f * PI - PI / 4.0f), sin(2.0f * PI - PI / 4.0f));

	point[13] = Vec2f(cos(PI + PI / 3.0f), sin(PI + PI / 3.0f));
	point[14] = Vec2f(cos(2.0f * PI - PI / 3.0f), sin(2.0f * PI - PI / 3.0f));

	point[15] = Vec2f(cos(PI + PI / 2.0f), sin(PI + PI / 2.0f));
	while (1) {
		Q5Print();
		if (Q5InsertCommand() == 0)
			break;
		system("cls");
	}

}

int Q5InsertCommand()
{
	switch (_getche()) {
	case 'C':
		for (int i = 0; i < 16; ++i) {
			Vec2f x = Vec2f(1,0);
			point[i] += x;
		}
		break;
	case 'c':
		for (int i = 0; i < 16; ++i) {
			Vec2f x = Vec2f(1, 0);
			point[i] -= x;
		}
		break;
	case 'X':
		for (int i = 0; i < 16; ++i) {
			Vec2f x = Vec2f(1, 0);
			point[i] += x;
		}
		break;
	case 'x':
		for (int i = 0; i < 16; ++i) {
			Vec2f x = Vec2f(1, 0);
			point[i] -= x;
		}
		break;
	case 'Y':
		for (int i = 0; i < 16; ++i) {
			Vec2f x = Vec2f(0, 1);
			point[i] += x;
		}
		break;
	case 'y':
		for (int i = 0; i < 16; ++i) {
			Vec2f x = Vec2f(0, 1);
			point[i] -= x;
		}
		break;
	case 'Q':
	case 'q':
		cout << endl;
		return 0;
	default:
		break;
	}
	return 1;
}

void Q5Print()
{
	/*
	for (int i = 0; i < 15; ++i) {
		cout << point[i];

		if (i != 0 && point[i].x >= point[i - 1].x) cout << endl;
	}
	
	*/

	for (int i = 0; i < 15; ++i) {
		//cout << "(" << point[i].x << " , " << point[i].y << ")";
		printf("( %0.2f , %0.2f )",point[i].x,point[i].y);
		if (i != 0 && point[i].y != point[i - 1].y) cout << endl;
	}

}
