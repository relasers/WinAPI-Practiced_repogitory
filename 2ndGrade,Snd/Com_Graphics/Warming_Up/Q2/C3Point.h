#pragma once

#include<iostream>
#include<cstdlib>
#include<cmath>
using namespace std;

class C3Point
{
private:
	double m_x;
	double m_y;
	double m_z;
	double m_length;
public:
	C3Point();
	C3Point(double x, double y, double z);
	~C3Point();
	void InsertPoint(double x, double y, double z);
	const int Delete() const { return 1; }
	const double GetX() const { return m_x; }
	const double GetY() const { return m_y; }
	const double GetZ() const { return m_z; }
	const double GetLength() const { return m_length; }
	friend ostream& operator<<(ostream& os, const C3Point& p);
};

