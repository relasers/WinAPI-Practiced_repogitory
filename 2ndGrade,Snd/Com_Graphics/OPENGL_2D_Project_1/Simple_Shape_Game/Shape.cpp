#include "Shape.h"



CShape::CShape()
{
}

CShape::CShape(POINT pt,int number_vertex)
{
	m_cpt.x = pt.x;
	m_cpt.y = pt.y;
	m_n_vertex = number_vertex;

	for (int i = 0; i < m_n_vertex; ++i) {
		vertex.push_front(Vec2i(50*cos(i*(360.0/ m_n_vertex)*PI / 180.0),
			50*sin(i*(360.0 / m_n_vertex)*PI / 180.0)));
	}
}


CShape::~CShape()
{
}

GLvoid CShape::Update()
{
	vertex.clear();
	for (int i = 0; i < m_n_vertex; ++i) {
		vertex.push_front(Vec2i(50*cos(i*(360.0 / m_n_vertex)*PI / 180.0),
			50*sin(i*(360.0 / m_n_vertex)*PI / 180.0)));
	}
}

GLvoid CShape::Draw()
{
	glMatrixMode(GL_MODELVIEW);
	glTranslated(m_cpt.x, m_cpt.y, 0);
	glScalef(m_size*x_reflet, m_size*y_reflet, 0);


	glColor4f(1.0, 1.0, 1.0, 1.0f);
	glBegin(GL_LINE_LOOP);
	for (auto &p : vertex)
	{
		glVertex2d(p.x, p.y);
	}
	glEnd();
	glLoadIdentity();

	////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////
}

GLvoid CShape::InputKeyBoard(int direction)
{
	int moveval = Window_Width / (Number_Line + 1);
	
	switch (direction) {
	case Direction::Left:
		m_cpt.x -= moveval;
		if (m_cpt.x - 50 < 0)
			m_cpt.x = moveval / 2;
		break;
	case Direction::Right:
		m_cpt.x += moveval;
		if (m_cpt.x + moveval / 2 > moveval * 5)
			m_cpt.x = moveval * 5 - moveval / 2;
		break;
	case Direction::Plus:
		m_size += 0.1;
		if (m_size > MaxSize)
			m_size = MaxSize;
		break;
	case Direction::Minus:
		m_size -= 0.1;
		if (m_size < 0.5)
			m_size = 0.5;
		break;
	}
	
}

GLvoid CShape::Reflect(int direction)
{
	if (direction == Direction::Left)x_reflet *= -1;
	if (direction == Direction::Plus)y_reflet *= -1;
}

GLvoid CShape::Reshape(int number_vertex)
{
	m_n_vertex = number_vertex;
}

