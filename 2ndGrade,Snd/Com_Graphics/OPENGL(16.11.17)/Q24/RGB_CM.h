#pragma once
#include "Vec3D.h"
#include "Ball.h"
#include "DropCube.h"
#include <list>

#define PI 3.141592

class CRGB_CM
{
private:

	list<CBall> m_ball;
	list<CDropCube>m_cube;

	int m_size = 50;
	int m_angle = 0;

	int m_face_angle = 0;
	int m_up_angle = 0;

	bool m_rander_up = true;
	bool m_rander_face = true;

	bool m_up_open = false;
	bool m_face_open = false;

	Vec3f Color[6][4] = {
		{{ 1.0f,1.0f,0.0f },{ 1.0f,1.0f,1.0f },{ 1.0f,0.0f,1.0f },{ 1.0f,0.0f,0.0f }},
		{ { 0.0f,1.0f,1.0f },{ 0.0f,1.0f,0.0f },{ 0.0f,0.0f,0.0f },{ 0.0f,0.0f,1.0f }},
		{ { 0.0f,1.0f,0.0f },{ 1.0f,1.0f,0.0f },{ 1.0f,0.0f,0.0f },{ 0.0f,0.0f,0.0f }},
		{ { 1.0f,1.0f,1.0f },{ 0.0f,1.0f,1.0f },{ 0.0f,0.0f,1.0f },{ 1.0f,0.0f,1.0f }},
		{ { 1.0f,0.0f,1.0f },{ 0.0f,0.0f,1.0f },{ 0.0f,0.0f,0.0f },{ 1.0f,0.0f,0.0f }},
		{ { 1.0f,1.0f,0.0f },{ 0.0f,1.0f,0.0f },{ 0.0f,1.0f,1.0f },{ 1.0f,1.0f,1.0f }}
	
	
	
	};
public:
	CRGB_CM();
	~CRGB_CM();

	void Rander();
	void Update(int camera_angle);

	void KeyInput(unsigned char key, int x, int y);

	void RanderModel();
	void RanderSurface(Vec3f color[4]);
	void ChangeColor(int x);
};

