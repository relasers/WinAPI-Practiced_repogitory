#include "Point3D.h"

CPoint3D::CPoint3D()
{
}

CPoint3D::CPoint3D(double x, double y, double z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

CPoint3D::~CPoint3D()
{
}

void CPoint3D::Input()
{
	cin >> m_x >> m_y >> m_z;
}

ostream &operator<<(ostream &os, const CPoint3D& p)
{
	os << "( " << p.m_x << "," << p.m_y << "," << p.m_z << ") ";
	return os;
}