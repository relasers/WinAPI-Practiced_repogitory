#pragma once


template<typename Ty>
struct Point2D {
	Ty x, y;
};

using Point2i = Point2D<int>;
using Point2f = Point2D<float>;

template<typename Ty>
struct Vector3D 
{

	union {
		Ty arr[3];
		struct { Ty x, y, z; };
	};

	Vector3D() : x(0), y(0), z(0) {}
	Vector3D(Ty X, Ty Y, Ty Z) : x(X), y(Y), z(Z) {}
	template<typename Ty1>
	Vector3D(Ty1 X, Ty1 Y, Ty1 Z) : x(static_cast<Ty>(X)), y(static_cast<Ty>(Y)), z(static_cast<Ty>(Z)) {}
	template<typename Ty1>
	Vector3D(const Vector3D<Ty1>& pt) : x(static_cast<Ty>(pt.x)), y(static_cast<Ty>(pt.y)), z(static_cast<Ty>(pt.z)) {}
	Vector3D& operator+=(const Vector3D& other) { x += other.x; y += other.y; z += other.z; return *this; }
	Vector3D& operator-=(const Vector3D& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
	Vector3D& operator*=(const float f)			{ x *= f; y *= f; z *= f; return *this; }
	Vector3D& operator=(const Ty(&other)[3])	{ x = other[0]; y = other[1]; z = other[2]; return *this; }
	Vector3D& operator=(const Vector3D& other)	{ x = other.x; y = other.y; z = other.z; return *this; }
	bool operator==(const Vector3D& other) const { return { Length(other - *this) < 0.00000001f }; }
	
	Ty& operator[](size_t sz) {
		assert(sz < 3 && "3차원 벡터는 0, 1, 2밖에 없습니다!");
		return arr[sz];
	}

};


template<typename Ty> using Vec3D = Vector3D<Ty>;
using Vec3f = Vector3D<float>;
using Vec3d = Vector3D<double>;
using Vec3i = Vector3D<int>;

// Vec3D + Vec3D
template<typename Ty> inline Vec3D<Ty>	operator+(const Vec3D<Ty>& a, const Vec3D<Ty>& b)	{ return Vec3D<Ty>(a.x + b.x, a.y + b.y, a.z + b.z); }
// Vec3D - Vec3D
template<typename Ty> inline Vec3D<Ty>	operator-(const Vec3D<Ty>& a, const Vec3D<Ty>& b)	{ return Vec3D<Ty>(a.x - b.x, a.y - b.y, a.z - b.z); }

// Array + Vec3D
template<typename Ty> inline Vec3D<Ty>	operator+(const Ty(&a)[3], const Vec3D<Ty>& b)		{ return Vec3D<Ty>(a[0] + b.x, a[1] + b.y, a[2] + b.z); }
// Array - Vec3D
template<typename Ty> inline Vec3D<Ty>	operator-(const Ty(&a)[3], const Vec3D<Ty>& b)		{ return Vec3D<Ty>(a[0] + b.x, a[1] + b.y, a[2] - b.z); }
// Vec3D + Array
template<typename Ty> inline Vec3D<Ty>	operator+(const Vec3D<Ty>& a, const Ty(&b)[3])		{ return Vec3D<Ty>(a.x + b[0], a.y + b[1], a.z + b[2]); }
// Vec3D - Array
template<typename Ty> inline Vec3D<Ty>	operator-(const Vec3D<Ty>& a, const Ty(&b)[3])		{ return Vec3D<Ty>(a.x - b[0], a.y - b[1], a.z - b[2]); }

// Dot : Vec3D * Vec3D
template<typename Ty> inline float		operator*(const Vec3D<Ty>& a, const Vec3D<Ty>& b)	{ return float(a.x * b.x + a.y * b.y + a.z * b.z); }
// float * Vec3D
template<typename Ty> inline Vec3D<Ty>	operator*(const float a, const Vec3D<Ty>& b)	 	{ return Vec3D<Ty>(a * b.x, a * b.y, a * b.z); }
// Vec3D * float
template<typename Ty> inline Vec3D<Ty>	operator*(const Vec3D<Ty>& a, const float b)	 	{ return Vec3D<Ty>(b * a.x, b * a.y, b * a.z); }

template<typename Ty> inline float Length(const Vec3D<Ty>& pd3dVec) { return(sqrt(pd3dVec.x * pd3dVec.x + pd3dVec.y * pd3dVec.y + pd3dVec.z * pd3dVec.z)); }

template<typename Ty> inline Vec3D<Ty>& Normalize(Vec3D<Ty>& pd3dVec) { float fLength = Length(pd3dVec); if (fLength != 0) { pd3dVec.x /= fLength; pd3dVec.y /= fLength; pd3dVec.z /= fLength; } return pd3dVec; }
template<typename Ty> inline Vec3D<Ty>  CalcNormalize(const Vec3D<Ty>& pd3dVec) { float fLength = Length(pd3dVec); if (fLength != 0) { return Vec3D<Ty>{pd3dVec.x / fLength, pd3dVec.y / fLength, pd3dVec.z / fLength}; } return Vec3D<Ty>(); }

template<typename Ty> inline Vec3D<Ty> Cross(const Vec3D<Ty>& a, const Vec3D<Ty>& b)		{ return { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x }; }