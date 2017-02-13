#pragma once

#include<iostream>

using namespace std;
class CPoint3D
{
private:
	double m_x;
	double m_y;
	double m_z;
public:
	CPoint3D();
	CPoint3D(double x, double y, double z);
	~CPoint3D();
	void Input();
	const double GetX() const { return m_x; }
	const double GetY() const { return m_y; }
	const double GetZ() const { return m_z; }
	friend ostream& operator<<(ostream& os, const CPoint3D& p);
};

