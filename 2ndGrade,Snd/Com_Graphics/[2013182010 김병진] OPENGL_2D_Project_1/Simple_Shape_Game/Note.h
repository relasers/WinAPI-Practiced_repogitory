#pragma once
#include"stdafx.h"

class CNote
{
private:
	Vec2f m_cpt{};
	int m_n_vertex;
	int m_speed = 1;
	float m_angle = 0;
	float m_size = 1.0;
	float m_xshearing = 0;
	float m_yshearing = 0;
	int x_reflet = 1;
	int y_reflet = 1;

	bool isbase = false;
	bool isGet = false;
	list <Vec2f> vertex;
	list <Vec2f> c_vertex;
public:
	CNote();
	CNote(POINT pt, int number_vertex,int speed);
	~CNote();

	GLvoid Update();
	GLvoid Draw();
	
	GLvoid Clipping(Vec2f x,float size);
	bool CheckCross(Vec2f p1_1,Vec2f p1_2, Vec2f p2_1, Vec2f p2_2);


	GLvoid Reshape(int number_vertex);
	GLvoid SpeedChange(int speed);
	bool Check(Vec2f x,float size, int num_vertex);
	bool IsOut();
};

bool compare_x(Vec2f a, Vec2f b);

bool compare_low_y(Vec2f a, Vec2f b);
bool compare_hgh_y(Vec2f a, Vec2f b);