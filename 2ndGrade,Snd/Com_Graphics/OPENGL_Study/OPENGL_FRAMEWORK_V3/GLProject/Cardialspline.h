#pragma once
#include "Vector3D.h"
#include <cmath>
class CCardinalspline
{

public:

	static Vec3f CalcCardinal(float u, 
							float tension
		,Vec3f p0
		, Vec3f p1
		, Vec3f p2
		, Vec3f p3) 
	{
		float s = (1.f - tension) * 0.5f;
		
		Vec3f a = -s * p0		+ (2.f - s) * p1	+ ( s - 2.f) * p2	+ s*p3;
		Vec3f b = (2.f*s) * p0	+ (s - 3.f)* p1		+ (3.f - 2.f*s)*p2	- s*p3;
		Vec3f c = -s * p0							+ s * p2;
		Vec3f d =							p1;

		return a*pow(u, 3) + b * pow(u, 2) + c*u + d;
		
	}


};