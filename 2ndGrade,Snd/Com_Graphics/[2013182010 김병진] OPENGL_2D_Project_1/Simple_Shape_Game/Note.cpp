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
	dice = rand() % 3;
	if (dice == 0) {
		m_xshearing = rand()%12/10;
		m_yshearing = rand() % 12 / 10;
	}	
	
	for (int i = 0; i < m_n_vertex; ++i) {
		Vec2f temp;
		temp.x = 50 * cos(i*(360.0 / m_n_vertex)*PI / 180.0);
		temp.y = 50 * sin(i*(360.0 / m_n_vertex)*PI / 180.0);
		temp.ReShape(m_cpt.x, m_cpt.y, m_size, m_angle, m_xshearing, m_yshearing, x_reflet, y_reflet);

		vertex.push_front(Vec2f(temp.x, temp.y));
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
		Vec2f temp;
		temp.x = 50 * cos(i*(360.0 / m_n_vertex)*PI / 180.0);
		temp.y = 50 * sin(i*(360.0 / m_n_vertex)*PI / 180.0);
		temp.ReShape(m_cpt.x, m_cpt.y, m_size, m_angle, m_xshearing, m_yshearing, x_reflet, y_reflet);

		vertex.push_front(Vec2f(temp.x, temp.y));
	}

	
}

GLvoid CNote::Draw()
{
	glColor4f(1.0, 1.0, 1.0, 1.0f);

	if (isbase) glColor4f(1.0, 0.7, 0.7, 1.0f);

	if (isGet == true) glBegin(GL_POLYGON);
	else glBegin(GL_LINE_LOOP);
	for (auto &p : vertex)
	{
		glVertex2i(p.x, p.y);
	}
	glEnd();

	glBegin(GL_POLYGON);
	glColor4f(0.0, 0.0, 1.0, 1.0f);
	for (auto &p : c_vertex)
	{
		glVertex2i(p.x, p.y);
	}
	glEnd();


}

GLvoid CNote::Clipping(Vec2f x, float size)
{
	float Min_x = x.x - 50 * size;
	float Max_x = x.x + 50 * size;
	float Min_y = x.y - 50 * size;
	float Max_y = x.y + 50 * size;
	Vec2f temp_3;
	Vec2f temp_4;

	c_vertex.clear();
	Vec2f temp[6];
	int i = 0;
	for (auto p : vertex) {
		
		if (Min_x <= p.x && p.x <= Max_x &&
			Min_y <= p.y && p.y <= Max_y
			) {
			c_vertex.push_front(Vec2f(p.x, p.y));
		}
		temp[i].x = p.x;
		temp[i].y = p.y;
		++i;
	}


	for (int i = 0;i<m_n_vertex;++i) {
		Vec2f temp_1 = { temp[i].x, temp[i].y};
		Vec2f temp_2;
		if (i < m_n_vertex - 1) {
			temp_2.x = temp[i + 1].x;
			temp_2.y = temp[i + 1].y;
		} 
		else {
			temp_2.x = temp[0].x;
			temp_2.y = temp[0].y;
		}
		if (Min_x <= temp[i].x && temp[i].x <= Max_x &&
			Min_y <= temp[i].y && temp[i].y <= Max_y
			) {
			c_vertex.push_front(Vec2f(temp[i].x, temp[i].y));
		}

		temp_3 = Vec2f( (float)(x.x-50),Max_y );
		temp_4 = Vec2f((float)(x.x + 50), Max_y);

		CheckCross(temp_1, temp_2, temp_3, temp_4); // lt~rt

		temp_3 = Vec2f(Max_x, (float)(50+50*m_size));
		temp_4 = Vec2f(Max_x, (float)0);

		CheckCross(temp_1, temp_2, temp_3, temp_4);// rt~rb

		temp_3 = Vec2f((float)(x.x - 50), Min_y);
		temp_4 = Vec2f((float)(x.x + 50), Min_y);

		CheckCross(temp_1, temp_2, temp_3, temp_4);// rb~lb

		temp_3 = Vec2f(Min_x, (float)(50 + 50 * m_size));
		temp_4 = Vec2f(Min_x, (float)0);

		CheckCross(temp_1, temp_2, temp_3, temp_4);// lb~lt
	}
	list <Vec2f> l_vertex;
	list <Vec2f> r_vertex;

	for (auto p : c_vertex) {

		if (p.x <= x.x){
			l_vertex.push_front(Vec2f(p.x, p.y));
		}
		else {
			r_vertex.push_front(Vec2f(p.x, p.y));
		}
	}
	/*
	if (c_vertex.size() == 0) {
		l_vertex.push_front(Vec2f(lt.x, lt.y));
		l_vertex.push_front(Vec2f(lb.x, lb.y));
		r_vertex.push_front(Vec2f(rt.x, rt.y));
		r_vertex.push_front(Vec2f(rb.x, rb.y));
	}
	*/
	

		c_vertex.clear();
		l_vertex.sort(compare_low_y);
		r_vertex.sort(compare_hgh_y);

		for (auto p : l_vertex) {
			c_vertex.push_front(Vec2f(p.x, p.y));
		}
		for (auto p : r_vertex) {
			c_vertex.push_front(Vec2f(p.x, p.y));
		}
	

}

bool CNote::CheckCross(Vec2f p1_1, Vec2f p1_2, Vec2f p2_1, Vec2f p2_2)
{
	double t;
	double s;
	double under = (p2_2.y - p2_1.y)*(p1_2.x - p1_1.x) - (p2_2.x - p2_1.x)*(p1_2.y - p1_1.y);
	if (under == 0) return false;

	double _t = (p2_2.x - p2_1.x)*(p1_1.y - p2_1.y) - (p2_2.y - p2_1.y)*(p1_1.x - p2_1.x);
	double _s = (p1_2.x - p1_1.x)*(p1_1.y - p2_1.y) - (p1_2.y - p1_1.y)*(p1_1.x - p2_1.x);

	t = _t / under;
	s = _s / under;

	if (t<0.0 || t>1.0 || s<0.0 || s>1.0) return false;
	if (_t == 0 && _s == 0) return false;

	float c_x = p1_1.x + t * (double)(p1_2.x - p1_1.x);
	float c_y = p1_1.y + t * (double)(p1_2.y - p1_1.y);
	c_vertex.push_front(Vec2f(c_x, c_y));
	return true;
}

GLvoid CNote::Reshape(int number_vertex)
{
	m_n_vertex = number_vertex;
}

GLvoid CNote::SpeedChange(int speed)
{
	m_speed = speed;
}

bool CNote::Check(Vec2f x,float size,int num_vertex)
{
	Clipping(x,size);
	if (m_cpt.x == x.x && m_cpt.y < 70 && isGet == false) {

		if (m_n_vertex == num_vertex && 
			(fabs(m_size - size) < EffectiveEffer )
			|| isbase) {
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


bool compare_x(Vec2f a, Vec2f b)
{
	return a.x < b.x;
}

bool compare_low_y(Vec2f a, Vec2f b)
{
	return a.y < b.y;
}

bool compare_hgh_y(Vec2f a, Vec2f b)
{
	return a.y > b.y;
}




