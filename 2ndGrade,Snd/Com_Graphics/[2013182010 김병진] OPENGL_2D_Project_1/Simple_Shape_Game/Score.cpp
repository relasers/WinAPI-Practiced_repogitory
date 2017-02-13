#include "Score.h"



CScore::CScore()
{
}


CScore::~CScore()
{
}

GLvoid CScore::Draw()
{

	for (int i = 0; i < MaxScore; ++i) {
	
		glColor4f(1.0, 1.0, 1.0, 1.0f);

		if (i>=m_score) glBegin(GL_LINE_LOOP);
		else glBegin(GL_POLYGON);
		
			glVertex2d(m_cpt.x, m_cpt.y);

			glVertex2d(
				m_cpt.x + 50*cos(i*(360.0 / MaxScore)*PI / 180.0),
				m_cpt.y + 50*sin(i*(360.0 / MaxScore)*PI / 180.0));

			glVertex2d(
				m_cpt.x + 50 * cos((i + 1)*(360.0 / MaxScore)*PI / 180.0),
				m_cpt.y + 50 * sin((i + 1)*(360.0 / MaxScore)*PI / 180.0));

		glEnd();
	
	}


}

GLvoid CScore::Update()
{
}

GLvoid CScore::GainScore()
{
	m_score+= 1;
}
