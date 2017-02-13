#include "Madurai.h"



CMadurai::CMadurai()
{
}

CMadurai::CMadurai(POINT pt)
{
	point.x = pt.x;
	point.y = pt.y;
}


CMadurai::~CMadurai()
{
}

void CMadurai::Draw()
{
		glColor4f(R, G, B, 1.0f);
		glPointSize(1);
		glBegin(GL_POINTS);

		float x = 1;
		if (work <= 1080) {
			for (int i = 0; i < work; ++i) {
				glVertex2f(point.x +
					(float)(radius + i / 360 + x)*cos((float)i*PI / 180.0),
					point.y +
					(float)(radius + i / 360 + x)*sin((float)i*PI / 180.0));
				x += 0.1;
			}
		}
		else {
			for (int i = 0; i < 1080; ++i) {
				glVertex2f(point.x +
					(float)(radius + i / 360 + x)*cos((float)i*PI / 180.0),
					point.y +
					(float)(radius + i / 360 + x)*sin((float)i*PI / 180.0));
				x += 0.1;
			}
			x = -109;
			for (int i = 0; i < (work-1080); ++i) {
				glVertex2f(point.x + 217 +
					(float)(radius + (1080 - i) / 360 + x)*cos((float)i*PI / 180.0),
					point.y -
					(float)(radius + (1080 - i) / 360 + x)*sin((float)i*PI / 180.0));
				x += 0.1;
			}
		}
			
		
		glEnd();

}

void CMadurai::Update(int w, int h)
{
	srand((unsigned)time(nullptr)|(LONG)this);

	R = rand() % 10 / 10.0;
	G = rand() % 10 / 10.0;
	B = rand() % 10 / 10.0;
	(++work)%=1080*2;
}

void CMadurai::IncreaseSpd()
{
	speed++;
	if (speed >= MX_Speed) {
		speed = MX_Speed;
	}
}

void CMadurai::DecreaseSpd()
{
	speed--;
	if (speed <= MN_Speed) {
		speed = MN_Speed;
	}
}
