#pragma once
#include"stdafx.h"

class CNote
{
private:
	Vec2i m_cpt{};
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
	list <Vec2i> vertex;
public:
	CNote();
	CNote(POINT pt, int number_vertex,int speed);
	~CNote();

	GLvoid Update();
	GLvoid Draw();

	GLvoid Reshape(int number_vertex);
	GLvoid SpeedChange(int speed);
	bool Check(Vec2i x,float size, int num_vertex);
	bool IsOut();
};

