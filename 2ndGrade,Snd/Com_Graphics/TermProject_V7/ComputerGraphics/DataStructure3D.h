#pragma once
template <typename T>
struct myRECT
{
	T x1;
	T y1;
	T x2;
	T y2;
};
using RECTd = myRECT<double>;
using RECTf = myRECT<float>;
using RECTi = myRECT<int>;

template <typename T>
struct myCOLORREF
{
	T red;
	T green;
	T blue;
	T alpha;
};
using myCOLORREFb = myCOLORREF<BYTE>;
using myCOLORREFi = myCOLORREF<int>;
using myCOLORREFf = myCOLORREF<float>;

template<typename Ty>
class CVertex2D
{
private:
	const float EffectiveEffer = 0.0001f;

public:
	Ty				x;
	Ty				y;
	myCOLORREFb		color{ 0, 0, 0, 255 };

	CVertex2D() : x(0), y(0) {}
	template<typename OTy>
	CVertex2D(OTy X, OTy Y) : x(static_cast<Ty>(X)), y(static_cast<Ty>(Y)) {}

	void SetColor(const myCOLORREFb clr, bool alpha = true)
	{
		color.red = clr.red; color.green = clr.green; color.blue = clr.blue; if (alpha) color.alpha = clr.alpha;
	}
	void SetColor(const BYTE r, const BYTE g, const BYTE b) { color.red = r; color.green = g; color.blue = b; }
	void SetAlpha(const BYTE a) { color.alpha = a; }

	CVertex2D& operator=(const CVertex2D& other) { x = other.x; y = other.y; SetColor(other.color); return *this; }

	bool operator==(const CVertex2D& other) const { return(fabs(x - other.x) < EffectiveEffer && fabs(y - other.y) < EffectiveEffer); }
};

using Vertex2d = CVertex2D<double>;
using Vertex2f = CVertex2D<float>;
using Vertex2i = CVertex2D<int>;


template<typename Ty>
class CVertex3D
{
private:
	const float EffectiveEffer = 0.0001f;

public:
	Ty				x;
	Ty				y;
	Ty				z;
	myCOLORREFb		color{ 0, 0, 0, 255 };

	CVertex3D() : x(0), y(0), z(0) {}
	template<typename OTy>
	CVertex3D(OTy X, OTy Y, OTy Z) : x(static_cast<Ty>(X)), y(static_cast<Ty>(Y)), z(static_cast<Ty>(Z)) {}

	void SetColor(const myCOLORREFb clr, bool alpha = true)
	{
		color.red = clr.red; color.green = clr.green; color.blue = clr.blue; if (alpha) color.alpha = clr.alpha;
	}
	void SetColor(const BYTE r, const BYTE g, const BYTE b) { color.red = r; color.green = g; color.blue = b; }
	void SetAlpha(const BYTE a) { color.alpha = a; }

	CVertex3D& operator=(const CVertex3D& other) { x = other.x; y = other.y; z = other.z; SetColor(other.color); return *this; }

	bool operator==(const CVertex3D& other) const { return(fabs(x - other.x) < EffectiveEffer && fabs(y - other.y) < EffectiveEffer && fabs(z - other.z) < EffectiveEffer); }
};

using Vertex3d = CVertex3D<double>;
using Vertex3f = CVertex3D<float>;
using Vertex3i = CVertex3D<int>;

template<typename Ty>
inline Vector3D<Ty> operator-(const CVertex3D<Ty> a, const CVertex3D<Ty> b) { return Vector3D<Ty>(a.x - b.x, a.y - b.y, a.z - b.z); }
template<typename Ty>
inline CVertex3D<Ty> operator-(const Vector3D<Ty> a, const CVertex3D<Ty> b) { return CVertex3D<Ty>(a.x - b.x, a.y - b.y, a.z - b.z); }
template<typename Ty>
inline CVertex3D<Ty> operator-(const CVertex3D<Ty> a, const Vector3D<Ty> b) { return CVertex3D<Ty>(a.x - b.x, a.y - b.y, a.z - b.z); }

template<typename Ty>
class CAngle3D
{
public:
	Ty yaw;   // y axis rotation anlge
	Ty pitch; // x axis rotation anlge
	Ty roll;  // z axis rotation anlge

	CAngle3D() : yaw(0), pitch(0), roll(0) {}
	// YAW : y axis rotation anlge
	// PITCH : x axis rotation anlge
	// ROLL : z axis rotation anlge
	template<typename OTy>
	CAngle3D(OTy YAW, OTy PITCH, OTy ROLL) : yaw(static_cast<Ty>(YAW)), pitch(static_cast<Ty>(PITCH)), roll(static_cast<Ty>(ROLL)) {}
	~CAngle3D() {}

	CAngle3D& operator=(const CAngle3D& other) { yaw = other.yaw; pitch = other.pitch; roll = other.roll; return *this; }
};

using Angle3d = CAngle3D<double>;
using Angle3f = CAngle3D<float>;
using Angle3i = CAngle3D<int>;

template<typename Ty>
class CScale3D
{
public:
	Ty x;
	Ty y;
	Ty z;

	CScale3D() : x(1), y(1), z(1) {}
	template<typename OTy>
	CScale3D(OTy X, OTy Y, OTy Z) : x(static_cast<Ty>(X)), y(static_cast<Ty>(Y)), z(static_cast<Ty>(Z)) {}
	~CScale3D() {}
	CScale3D& operator=(const CScale3D& other) { x = other.x; y = other.y; z = other.z; return *this; }
};

using Scale3d = CScale3D<double>;
using Scale3f = CScale3D<float>;
using Scale3i = CScale3D<int>;


class CCamera
{
public:
	Vec3f pos;
	Vec3f look;
	Vec3f up;

	CCamera() : pos(0, 0, 0), look(0, 0, 1), up(0, 1, 0) {}
	~CCamera() {}
};

using Scale3d = CScale3D<double>;
using Scale3f = CScale3D<float>;
using Scale3i = CScale3D<int>;

enum VertexPos {
	ForwardLeftTop = 0
	, BackLeftTop
	, ForwardRightTop
	, BackRightTop
	, ForwardLeftDown
	, BackLeftDown
	, ForwardRightDown
	, BackRightDown
};

enum CubePos {
	LTF = 0
	, LTB
	, RTF
	, RTB
	, LBF
	, LBB
	, RBF
	, RBB
};
template <typename Ty>
class CSurfaceFormular
{
public:
	enum Surface {
		Top
		, Bottom
		, Left
		, Right
		, Forward
		, Back
	};
public:
	Vector3D<Ty> Normal;
	Ty Distance;

	void SetFormular(Vector3D<Ty> a, Vector3D<Ty> b, Vector3D<Ty> c)
	{
		Normal = Normalize(Cross(b - a, b - c));
		Distance = -(Normal.x * a.x + Normal.y * a.y + Normal.z * a.z);
	}
	constexpr bool isCollide(const Vector3D<Ty> vtx) const { return 0 > (Normal.x * vtx.x + Normal.y * vtx.y + Normal.z * vtx.z + Distance); }
};

using SFormularf = CSurfaceFormular<float>;