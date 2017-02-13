
//-----------------------------------------------------------------------------
// File: Vec3d.h
//-----------------------------------------------------------------------------

// * -> 郴利
// / -> 寇利
#pragma once

#include <Windows.h>
#include <iostream>

using namespace std;

template<typename Ty>
class Vector3D;

template<typename Ty>
ostream & operator<<(ostream& os, const Vector3D<Ty>& p);

template<typename Ty>
class Vector3D {
private:
	const float EffectiveEffer = 0.1f;

public:
	Ty x;
	Ty y;
	Ty z;
	Vector3D() : x(0), y(0), z(0) {}
	template<typename OTy>
	Vector3D(OTy X, OTy Y, OTy Z) : x(static_cast<Ty>(X)), y(static_cast<Ty>(Y)), z(static_cast<Ty>(Z)) {}
	Vector3D& operator+=(const Vector3D& other) { x += other.x; y += other.y; z += other.z; return *this; }
	Vector3D& operator-=(const Vector3D& other) { x -= other.x; y -= other.y; z += other.z; return *this; }
	Vector3D& operator*=(const float f) { x *= f; y *= f; z *= f; return *this; }
	Vector3D& operator*=(const int i) { x *= i; y *= i; z *= i; return *this; }
	Vector3D& operator=(const Vector3D& other) { x = other.x; y = other.y; z = other.z; return *this; }

	operator Vector3D() const { return Vector3D{ static_cast<LONG>(x) ,static_cast<LONG>(y) ,static_cast<LONG>(z) }; }
	Vector3D Normalize() {
		float fLength = Length(); if (fLength != 0) {
			static_cast<float>(x) /= fLength; static_cast<float>(y) /= fLength; static_cast<float>(z) /= fLength;
		} return *this;
	}
	constexpr float Length() const { return(sqrt(x * x + y * y + z * z)); }

	Vector3D Divide(float f) {
		x /= f; y /= f; z /= f;
		return *this;
	}

	Vector3D Divide(int i) {
		x /= i; y /= i; z /= i;
		return *this;
	}

	bool operator==(const Vector3D& other) const { return(fabs(x - other.x) < EffectiveEffer && fabs(y - other.y) < EffectiveEffer && fabs(z - other.z) < EffectiveEffer); }

	template<typename Ty>
	friend ostream& operator<< (ostream & os, const Vector3D<Ty> & p);
};

template<typename Ty>
ostream &operator<<(ostream &os, const Vector3D<Ty>& p)
{
	os << "( " << p.x << "," << p.y << "," << p.z << ") ";
	return os;
}

using Vec3f = Vector3D<float>;
using Vec3i = Vector3D<int>;

template<typename Ty>
inline Vector3D<Ty> operator+(const Vector3D<Ty> a, const Vector3D<Ty> b) { return Vector3D<Ty>(a.x + b.x, a.y + b.y, a.z + b.z); }
template<typename Ty>
inline Vector3D<Ty> operator-(const Vector3D<Ty> a, const Vector3D<Ty> b) { return Vector3D<Ty>(a.x - b.x, a.y - b.y, a.z - b.z); }

template<typename Ty>
inline float operator*(const Vector3D<Ty> a, const Vector3D<Ty> b) { return (a.x * b.x + a.y * b.y + a.z * b.z); } // 郴利

template<typename Ty>
inline Vector3D<Ty> operator/(const Vector3D<Ty> a, const Vector3D<Ty> b) { return Vector3D<Ty>(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x); } // 寇利


template<typename Ty>
inline Vector3D<Ty> operator*(const float a, const Vector3D<Ty> b) { return Vector3D<Ty>(a * b.x, a * b.y, a * b.z); }
template<typename Ty>
inline Vector3D<Ty> operator*(const Vector3D<Ty> a, const float b) { return Vector3D<Ty>(b * a.x, b * a.y, b * a.z); }


#pragma once
