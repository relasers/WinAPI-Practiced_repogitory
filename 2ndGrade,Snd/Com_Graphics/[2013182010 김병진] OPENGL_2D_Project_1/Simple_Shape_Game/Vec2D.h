#pragma once

#include <Windows.h>
#include <iostream>

using namespace std;

template<typename Ty>
class Vector2D;

template<typename Ty>
ostream & operator<<(ostream& os, const Vector2D<Ty>& p);

template<typename Ty>
class Vector2D {
private:
	const float EffectiveEffer = 0.0001f;

public:
	Ty x;
	Ty y;
	Vector2D() : x(0), y(0) {}
	template<typename OTy>
	Vector2D(OTy X, OTy Y) : x(static_cast<Ty>(X)), y(static_cast<Ty>(Y)) {}
	Vector2D& operator+=(const Vector2D& other) { x += other.x; y += other.y; return *this; }
	Vector2D& operator-=(const Vector2D& other) { x -= other.x; y -= other.y; return *this; }
	Vector2D& operator*=(const float f) { x *= f; y *= f; return *this; }
	Vector2D& operator*=(const int i) { x *= i; y *= i; return *this; }
	Vector2D& operator=(const POINT& other) { x = other.x; y = other.y; return *this; }
	Vector2D& operator=(const Vector2D& other) { x = other.x; y = other.y; return *this; }

	operator POINT() const { return POINT{ static_cast<LONG>(x) ,static_cast<LONG>(y) }; }
	Vector2D Normalize() { float fLength = Length(); if (fLength != 0) { static_cast<float>(x) /= fLength; static_cast<float>(y) /= fLength; } return *this; }
	constexpr float Length() const { return(sqrt(x * x + y * y)); }

	void ReShape(float m_x,float m_y ,float m_size,int m_angle,float m_xshearing,float m_yshearing,int x_reflet,int y_reflet) {
	
		x *= m_size*x_reflet;
		y *= m_size*y_reflet;
		//////////밀림///////////////////////////////
		float temp_x = x + y*m_xshearing;
		float temp_y = y + x * m_yshearing;
		x = temp_x;
		y = temp_y;
		/////////회전///////////////
		temp_x = x*cos(m_angle*PI / 180.0) - y*sin(m_angle*PI / 180.0);
		temp_y = x*sin(m_angle*PI / 180.0) + y*cos(m_angle*PI / 180.0);
		x = temp_x;
		y = temp_y;
		///////////////이동///////////////////////////////
		x += m_x;
		y += m_y;
	}


	bool operator==(const Vector2D& other) const { return(fabs(x - other.x) < EffectiveEffer && fabs(y - other.y) < EffectiveEffer); }

	template<typename Ty>
	friend ostream& operator<< (ostream & os, const Vector2D<Ty> & p);
};

template<typename Ty>
ostream &operator<<(ostream &os, const Vector2D<Ty>& p)
{
	os << "( " << p.x << " , " << p.y << ") ";
	return os;
}

using Vec2f = Vector2D<float>;
using Vec2i = Vector2D<int>;

template<typename Ty>
inline Vector2D<Ty> operator+(const Vector2D<Ty> a, const Vector2D<Ty> b) { return Vector2D<Ty>(a.x + b.x, a.y + b.y); }
template<typename Ty>
inline Vector2D<Ty> operator-(const Vector2D<Ty> a, const Vector2D<Ty> b) { return Vector2D<Ty>(a.x - b.x, a.y - b.y); }

template<typename Ty>
inline Vector2D<Ty> operator+(const POINT a, const Vector2D<Ty> b) { return Vector2D<Ty>(a.x + b.x, a.y + b.y); }
template<typename Ty>
inline Vector2D<Ty> operator+(const Vector2D<Ty> a, const POINT b) { return Vector2D<Ty>(a.x + b.x, a.y + b.y); }
template<typename Ty>
inline Vector2D<Ty> operator-(const POINT a, const Vector2D<Ty> b) { return Vector2D<Ty>(a.x - b.x, a.y - b.y); }
template<typename Ty>
inline Vector2D<Ty> operator-(const Vector2D<Ty> a, const POINT b) { return Vector2D<Ty>(a.x - b.x, a.y - b.y); }

template<typename Ty>
inline float operator*(const Vector2D<Ty> a, const Vector2D<Ty> b) { return (a.x * b.x + a.y * b.y); }
template<typename Ty>
inline Vector2D<Ty> operator*(const float a, const Vector2D<Ty> b) { return Vector2D<Ty>(a * b.x, a * b.y); }
template<typename Ty>
inline Vector2D<Ty> operator*(const Vector2D<Ty> a, const float b) { return Vector2D<Ty>(b * a.x, b * a.y); }
#pragma once
