#include "Shape.h"

CShape::CShape()
{
}

CShape::CShape(POINT pt)
{
	point.x = pt.x;
	point.y = pt.y;
	Radius = Width + rand() % RandSize;

	Vec2f rand_dir{
	point.x - rand() % 100 + rand() % 200,
	point.y - rand() % 100 + rand() % 200,
	};

	dir = rand_dir - point;
	dir.Normalize();
}


CShape::~CShape()
{
}

void CShape::Draw()
{
		glColor4f(R, G, B, A);
		glBegin(GL_POLYGON);
		for (int i = 0; i < 360; ++i) {
			glVertex2i(point.x + Radius*cos(i*PI / 180.0),
				point.y + Radius*sin(i*PI / 180.0)); //v1
		}
		glEnd();

}

void CShape::Update(int w, int h)
{

	srand((LONG)point.x|(unsigned)time(nullptr));

	R = rand() % 10 / 10.0;
	G = rand() % 10 / 10.0;
	B = rand() % 10 / 10.0;

	point += dir*speed; // 거리계산 후 추적
	(++Radius) %= 20;
	if (IsDeadMan) A -= 0.1f;
}



void CShape::IncreaseSpd()
{
	speed++;
	if (speed >= MX_Speed) {
		speed = MX_Speed;
	}
}

void CShape::DecreaseSpd()
{
	speed--;
	if (speed <= MN_Speed) {
		speed = MN_Speed;
	}
}

void CShape::IsOutofField(RECT rect)
{
	if (!(PtInRect(&rect, point))) {
		IsDeadMan = true;
	}
}
