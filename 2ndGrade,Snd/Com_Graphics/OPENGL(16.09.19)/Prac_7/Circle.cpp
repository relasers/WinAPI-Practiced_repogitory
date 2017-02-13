#include "Circle.h"



CCircle::CCircle()
{
}

CCircle::CCircle(POINT pt)
{
	point.x = pt.x;
	point.y = pt.y;
}


CCircle::~CCircle()
{
}

void CCircle::Draw()
{
	switch (shape) {
	case 0:
	{
		glColor4f(R, G, B, 1.0f);
		glBegin(GL_POLYGON);
		glVertex2i(point.x, point.y + height); //v1
		glVertex2i(point.x, point.y); //v2
		glVertex2i(point.x + width, point.y); //v3
		glVertex2i(point.x + width, point.y + height); //v4
		glEnd();
		break;
	}
	case 1:
	{
		glColor4f(R, G, B, 1.0f);
		glPointSize(5);
		glBegin(GL_POINTS);
		for (int i = 0; i < 360; i+=360/16) {
			glVertex2f(point.x + (float)width*cos((float)i*PI / 180.0),
				point.y + (float)width*sin((float)i*PI / 180.0)); //v1
		}
		glEnd();
		break;
	}

	}

}

void CCircle::Update(int w, int h)
{
	tick++;

	if (tick == MaxTick)
	{
		tick = 0;
		//SwapSize();
	}

	width += 1;

}

void CCircle::SwapSize()
{
	srand((unsigned)time(nullptr));

	int temp = width;
	width = height;
	height = temp;

	R = rand() % 10 / 10.0;
	G = rand() % 10 / 10.0;
	B = rand() % 10 / 10.0;
}

void CCircle::ChangeShape(int s)
{
	shape = s;
}

void CCircle::IncreaseSpd()
{
	speed++;
	if (speed >= MX_Speed) {
		speed = MX_Speed;
	}
}

void CCircle::DecreaseSpd()
{
	speed--;
	if (speed <= MN_Speed) {
		speed = MN_Speed;
	}
}

bool CCircle::IsOver(int w)
{
	if (width >= w) return true;
	return false;
}
