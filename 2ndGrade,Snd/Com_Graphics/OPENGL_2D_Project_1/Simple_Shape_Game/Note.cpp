#include "Shape.h"



CNote::CNote()
{
}

CNote::CNote(POINT pt, int number_vertex,int speed)
{
	srand((unsigned)time(nullptr));
	m_cpt.x = pt.x;
	m_cpt.y = pt.y;
	m_speed = speed;
	
	m_size = (5.0+rand()%5)/10.0;
	m_angle = rand() % 360;
	m_n_vertex = number_vertex;

	int dice = rand() % 5;
	if (dice == 0) {
		isbase = true;
	}

	dice = rand() % 2;
	if (dice == 0) x_reflet *= -1;
	dice = rand() % 2;
	if (dice == 0) y_reflet *= -1;
	dice = rand() % 5;
	if (dice == 0) {
		m_xshearing = (float)(0.1 + rand() % 5) / 10.0;
		m_yshearing = (float)(0.1 + rand() % 5) / 10.0;
	}	

	for (int i = 0; i < m_n_vertex; ++i) {
		vertex.push_front(Vec2i(50*cos(i*(360.0 / m_n_vertex)*PI / 180.0),
			50*sin(i*(360.0 / m_n_vertex)*PI / 180.0)));
	}
}


CNote::~CNote()
{
}

GLvoid CNote::Update()
{

	m_cpt.y -= m_speed;

	vertex.clear();
	for (int i = 0; i < m_n_vertex; ++i) {
		vertex.push_front(Vec2i(50*cos(i*(360.0 / m_n_vertex)*PI / 180.0),
			50*sin(i*(360.0 / m_n_vertex)*PI / 180.0)));
	}

	
}

GLvoid CNote::Draw()
{
	glColor4f(1.0, 1.0, 1.0, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glTranslated(m_cpt.x, m_cpt.y, 0);
	glScalef(m_size*x_reflet, m_size*y_reflet, 0);
	glRotatef(m_angle, 0, 0, 1);

	GLfloat m[16] = {
		1.0f, m_xshearing, 0.0f, 0.0f,
		m_yshearing, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	glMultMatrixf(m);


	if (isbase) glColor4f(1.0, 0.7, 0.7, 1.0f);

	if (isGet == true) glBegin(GL_POLYGON);
	else glBegin(GL_LINE_LOOP);
	for (auto &p : vertex)
	{
		glVertex2d(p.x, p.y);
	}
	glEnd();
	glLoadIdentity();

}

GLvoid CNote::Reshape(int number_vertex)
{
	m_n_vertex = number_vertex;
}

GLvoid CNote::SpeedChange(int speed)
{
	m_speed = speed;
}

bool CNote::Check(Vec2i x,float size,int num_vertex)
{
	if (m_cpt.x == x.x && m_cpt.y < 50 && isGet == false) {

		if (m_n_vertex == num_vertex && m_size == size || isbase) {
			isGet = true;
			return true;
		}
	}
	return false;
}

bool CNote::IsOut()
{
	if (m_cpt.y+50 < 0) return true;
	return false;
}

