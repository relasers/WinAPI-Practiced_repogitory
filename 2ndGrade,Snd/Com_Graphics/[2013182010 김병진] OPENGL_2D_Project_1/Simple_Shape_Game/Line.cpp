#include "Line.h"



CLine::CLine()
{
}

CLine::CLine(int x,int lineNum,int Client_w, int Client_h)
{
	m_pt.x = x*(Client_w / (lineNum + 1));
	m_pt.y = Client_h;
	m_size = Client_w/(lineNum+1);
}


CLine::~CLine()
{
}

GLvoid CLine::draw()
{
	glColor4f(1.0, 1.0, 1.0, 1.0f);
	glBegin(GL_LINE_LOOP);
		glVertex2d(m_pt.x			, m_pt.y);
		glVertex2d(m_pt.x + m_size	, m_pt.y);
		glVertex2d(m_pt.x + m_size	, 0);
		glVertex2d(m_pt.x			, 0);
	glEnd();

	glBegin(GL_LINE_LOOP);
		glVertex2d(m_pt.x, 100);
		glVertex2d(m_pt.x + m_size, 100);
		glVertex2d(m_pt.x + m_size, 0);
		glVertex2d(m_pt.x, 0);
	glEnd();
}
