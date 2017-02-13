#include "Ractangle.h"



CRectangle::CRectangle()
{
}

CRectangle::CRectangle(POINT pt)
{
	point.x = pt.x;
	point.y = pt.y;
	StartPoint.x = pt.x;
	StartPoint.y = pt.y;
}


CRectangle::~CRectangle()
{
}

void CRectangle::Draw()
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

void CRectangle::Update(int w, int h)
{
	tick++;

	if (tick == MaxTick)
	{
		tick = 0;
		SwapSize();
	}
	if (ismove) {
		

		switch (dir) {
		case (int)Shape_Dir::Right:
			point.x+= speed;
			if (isback) {
				if (point.x >= StartPoint.x) {
					point.x = StartPoint.x;
					ismove = false;
					isback = false;
				}
			}

			if (point.x+width >= w) {
				point.x = w-width;
				dir = (int)Shape_Dir::Down;
			}
			break;
		case (int)Shape_Dir::Down:
			point.y-= speed;
			if (point.y <= 0) {
				point.y = 0;
				dir = (int)Shape_Dir::Left;
			}
			break;
		case (int)Shape_Dir::Left:
			point.x-= speed;
			if (point.x <= 0)
			{
				point.x = 0;
				dir = (int)Shape_Dir::Top;
			}
			break;
		case (int)Shape_Dir::Top:
			point.y+= speed;
			if (point.y >= StartPoint.y) {
				point.y = StartPoint.y;
				isback = true;
				dir = (int)Shape_Dir::Right;
			}
			break;



		}



	}
	
	




}

void CRectangle::SwapSize()
{
	srand((unsigned)time(nullptr));

	int temp = width;
	width = height;
	height = temp;

	R = rand() % 10 / 10.0;
	G = rand() % 10 / 10.0;
	B = rand() % 10 / 10.0;
}

void CRectangle::ChangeShape(int s)
{
	shape = s;
}

bool CRectangle::CollisionCheck(int x, int y)
{
	RECT temp_rect = { point.x,point.y,
	point.x + Width,point.y + height };
	POINT temp_pt = { x,y };
	if (PtInRect(&temp_rect,temp_pt)) {
		return true;
	}
	return false;
}

void CRectangle::MoveOn()
{
	if (ismove == false) {
		dir = (int)Shape_Dir::Right;
		ismove = true;
		isback = false;
	}
}

void CRectangle::IncreaseSpd()
{
	speed++;
	if (speed >= MX_Speed) {
		speed = MX_Speed;
	}
}

void CRectangle::DecreaseSpd()
{
	speed--;
	if (speed <= MN_Speed) {
		speed = MN_Speed;
	}
}
