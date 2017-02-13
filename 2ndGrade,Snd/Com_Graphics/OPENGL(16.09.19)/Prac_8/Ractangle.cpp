#include "Ractangle.h"



CRactangle::CRactangle()
{
}

CRactangle::CRactangle(POINT pt)
{
	point.x = pt.x;
	point.y = pt.y;
}


CRactangle::~CRactangle()
{
}

void CRactangle::Draw()
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
		glBegin(GL_POLYGON);
		for (int i = 0; i < 360; ++i) {
			glVertex2i(point.x + Width*cos(i*PI / 180.0),
				point.y + Width*sin(i*PI / 180.0)); //v1
		}
		glEnd();
		break;
	}

	}

}

void CRactangle::Update(int w, int h, Vec2f mousept)
{
	tick++;
	if (tick == MaxTick)
	{
		tick = 0;
		//SwapSize();
	}

	Vec2f length = mousept - point;
	length.Normalize();
	point += length*speed; // 거리계산 후 추적

}

void CRactangle::SwapSize()
{
	srand((unsigned)time(nullptr));

	int temp = width;
	width = height;
	height = temp;

	R = rand() % 10 / 10.0;
	G = rand() % 10 / 10.0;
	B = rand() % 10 / 10.0;
}

void CRactangle::ChangeShape(int s)
{
	shape = s;
}

void CRactangle::IncreaseSpd()
{
	speed++;
	if (speed >= MX_Speed) {
		speed = MX_Speed;
	}
}

void CRactangle::DecreaseSpd()
{
	speed--;
	if (speed <= MN_Speed) {
		speed = MN_Speed;
	}
}
