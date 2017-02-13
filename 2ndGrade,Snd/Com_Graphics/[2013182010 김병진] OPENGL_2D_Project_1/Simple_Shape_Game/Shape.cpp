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
		Vec2f temp;
		temp.x = 50 * cos((i+m_angle)*(360.0 / m_n_vertex)*PI / 180.0);
		temp.y = 50 * sin((i + m_angle)*(360.0 / m_n_vertex)*PI / 180.0);
		temp.ReShape(m_cpt.x, m_cpt.y, m_size, 0, 0, 0, x_reflet, y_reflet);

		vertex.push_front(Vec2f(temp.x, temp.y));
	}
}


CShape::~CShape()
{
}

GLvoid CShape::Update()
{
	vertex.clear();
	for (int i = 0; i < m_n_vertex; ++i) {
		Vec2f temp;
		temp.x = 50 * cos(((i)*(360.0 / m_n_vertex)+m_angle)*PI / 180.0);
		temp.y = 50 * sin(((i)*(360.0 / m_n_vertex) + m_angle)*PI / 180.0);
		temp.ReShape(m_cpt.x, m_cpt.y, m_size, 0, 0, 0, x_reflet, y_reflet);

		vertex.push_front(Vec2f(temp.x, temp.y));
	}

}
GLvoid CShape::Draw()
{


	glColor4f(1.0, 1.0, 1.0, 1.0f);

	glBegin(GL_LINE_LOOP);
	for (auto &p : vertex)
	{
		glVertex2f(p.x, p.y);
	}
	glEnd();
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

GLvoid CShape::Rotate()
{
	(++m_angle) %= 360;
}
