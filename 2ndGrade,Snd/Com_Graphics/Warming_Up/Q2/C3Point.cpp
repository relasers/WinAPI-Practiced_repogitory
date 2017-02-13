#include "C3Point.h"

using namespace std;

C3Point::C3Point()
{
}

C3Point::C3Point(double x, double y, double z)
{
	m_x = x;
	m_y = y;
	m_z = z;
	m_length = sqrt(
		((m_x)*(m_x))+
		((m_y)*(m_y)) +
		((m_z)*(m_z))
	);
}


C3Point::~C3Point()
{
}

void C3Point::InsertPoint(double x, double y, double z)
{
	m_x = x;
	m_y = y;
	m_z = z;
	m_length = sqrt(
		((m_x)*(m_x)) +
		((m_y)*(m_y)) +
		((m_z)*(m_z))
	);
}

ostream &operator<<(ostream &os, const C3Point& p)
{
	os << "( " << p.m_x << "," << p.m_y << "," << p.m_z << ") " << "Length ::" << p.m_length;
	return os;
}